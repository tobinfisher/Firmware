/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author: Tobias Naegeli <naegelit@student.ethz.ch>
 *           Lorenz Meier <lm@inf.ethz.ch>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*
 * @file attitude_estimator_ekf_main.c
 *
 * Madgwick Filter for Attitude Estimation.
 */

#include <nuttx/config.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <poll.h>
#include <fcntl.h>
#include <float.h>
#include <nuttx/sched.h>
#include <sys/prctl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <mathlib/mathlib.h>
#include <uORB/uORB.h>
#include <uORB/topics/debug_key_value.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_control_mode.h>
#include <uORB/topics/parameter_update.h>
#include <drivers/drv_hrt.h>

#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "codegen/attitudeKalmanfilter_initialize.h"
#include "codegen/attitudeKalmanfilter.h"
#include "attitude_estimator_madgwick_params.h"
#include "madgwick.h"
#ifdef __cplusplus
}
#endif

extern "C" __EXPORT int attitude_estimator_madgwick_main(int argc, char *argv[]);

static bool thread_should_exit = false;		/**< Deamon exit flag */
static bool thread_running = false;		/**< Deamon status flag */
static int attitude_estimator_ekf_task;				/**< Handle of deamon task / thread */

/**
 * Mainloop of attitude_estimator_ekf.
 */
int attitude_estimator_madgwick_thread_main(int argc, char *argv[]);

/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: attitude_estimator_madgwick {start|stop|status} [-p <additional params>]\n\n");
	exit(1);
}

/**
 * The attitude_estimator_ekf app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int attitude_estimator_madgwick_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (thread_running) {
			printf("attitude_estimator_madgwick already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		attitude_estimator_ekf_task = task_spawn_cmd("attitude_estimator_madgwick",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 5,
					      12400,
					      attitude_estimator_madgwick_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
			printf("\tattitude_estimator_madgwick app is running\n");

		} else {
			printf("\tattitude_estimator_madgwick app not started\n");
		}

		exit(0);
	}

	usage("unrecognized command");
	exit(1);
}

/*
 * [Rot_matrix,x_aposteriori,P_aposteriori] = attitudeKalmanfilter(dt,z_k,x_aposteriori_k,P_aposteriori_k,knownConst)
 */

/*
 * EKF Attitude Estimator main function.
 *
 * Estimates the attitude recursively once started.
 *
 * @param argc number of commandline arguments (plus command name)
 * @param argv strings containing the arguments
 */
int attitude_estimator_madgwick_thread_main(int argc, char *argv[])
{

const unsigned int loop_interval_alarm = 6500;	// loop interval in microseconds
float z_k[9];
	float dt = 0.005f;
/* state vector x has the following entries: */

	/* output euler angles */
	float euler[3] = {0.0f, 0.0f, 0.0f};

	float Rot_matrix[9] = {1.f,  0,  0,
			      0,  1.f,  0,
			      0,  0,  1.f
			     };		/**< init: identity matrix */

	// print text
	printf("Madgwick Filter Attitude Estimator initialized..\n\n");

   fflush(stdout);
    
	int overloadcounter = 19;

	/* Initialize filter */
	//madgwick_initialize();

	/* store start time to guard against too slow update rates */
	uint64_t last_run = hrt_absolute_time();

	struct sensor_combined_s raw;
	memset(&raw, 0, sizeof(raw));
	struct vehicle_attitude_s att;
	memset(&att, 0, sizeof(att));
	struct vehicle_control_mode_s control_mode;
	memset(&control_mode, 0, sizeof(control_mode));

	uint64_t last_data = 0;
	uint64_t last_measurement = 0;

	/* subscribe to raw data */
	int sub_raw = orb_subscribe(ORB_ID(sensor_combined));
	/* rate-limit raw data updates to 333 Hz (sensors app publishes at 200, so this is just paranoid) */
	orb_set_interval(sub_raw, 3);

	/* subscribe to param changes */
	int sub_params = orb_subscribe(ORB_ID(parameter_update));

	/* subscribe to control mode*/
	int sub_control_mode = orb_subscribe(ORB_ID(vehicle_control_mode));

	/* advertise attitude */
	orb_advert_t pub_att = orb_advertise(ORB_ID(vehicle_attitude), &att);


	int loopcounter = 0;
	int printcounter = 0;

	thread_running = true;

	/* advertise debug value */
	// struct debug_key_value_s dbg = { .key = "", .value = 0.0f };
	// orb_advert_t pub_dbg = -1;

	float sensor_update_hz[3] = {0.0f, 0.0f, 0.0f};
	// XXX write this out to perf regs

	/* keep track of sensor updates */
	uint32_t sensor_last_count[3] = {0, 0, 0};
	uint64_t sensor_last_timestamp[3] = {0, 0, 0};

	struct attitude_estimator_madgwick_params madgwick_params;

	struct attitude_estimator_madgwick_param_handles madgwick_param_handles;

	/* initialize parameter handles */
	parameters_init(&madgwick_param_handles);

	uint64_t start_time = hrt_absolute_time();
	bool initialized = false;

	float gyro_offsets[3] = { 0.0f, 0.0f, 0.0f };
	unsigned offset_count = 0;

	/* register the perf counter */
	perf_counter_t madgwick_loop_perf = perf_alloc(PC_ELAPSED, "attitude_estimator_madgwick");

	/* Main loop*/
	while (!thread_should_exit) {

		struct pollfd fds[2];
		fds[0].fd = sub_raw;
		fds[0].events = POLLIN;
		fds[1].fd = sub_params;
		fds[1].events = POLLIN;
		int ret = poll(fds, 2, 1000);

		if (ret < 0) {
			/* XXX this is seriously bad - should be an emergency */
            printf("[ATT_EST_MADG ERROR] RET < 0");
		} else if (ret == 0) {
			

		} else {

			/* only update parameters if they changed */
			if (fds[1].revents & POLLIN) {
				/* read from param to clear updated flag */
				struct parameter_update_s update;
				orb_copy(ORB_ID(parameter_update), sub_params, &update);

				/* update parameters */
				parameters_update(&madgwick_param_handles, &madgwick_params);
                
			}

			/* only run filter if sensor values changed */
			if (fds[0].revents & POLLIN) {

				/* get latest measurements */
				orb_copy(ORB_ID(sensor_combined), sub_raw, &raw);

				if (!initialized) {

					gyro_offsets[0] += raw.gyro_rad_s[0];
					gyro_offsets[1] += raw.gyro_rad_s[1];
					gyro_offsets[2] += raw.gyro_rad_s[2];
					offset_count++;

					if (hrt_absolute_time() - start_time > 3000000LL) {
						initialized = true;
						AttitudeInit(raw.accelerometer_m_s2[0],raw.accelerometer_m_s2[1],raw.accelerometer_m_s2[2]);
						gyro_offsets[0] /= offset_count;
						gyro_offsets[1] /= offset_count;
						gyro_offsets[2] /= offset_count;
					}

				} else {

					perf_begin(madgwick_loop_perf);

					/* Calculate data time difference in seconds */
					dt = (raw.timestamp - last_measurement) / 1000000.0f;
					last_measurement = raw.timestamp;
					uint8_t update_vect[3] = {0, 0, 0};

					/* Fill in gyro measurements */
					if (sensor_last_count[0] != raw.gyro_counter) {
						update_vect[0] = 1;
						sensor_last_count[0] = raw.gyro_counter;
						sensor_update_hz[0] = 1e6f / (raw.timestamp - sensor_last_timestamp[0]);
						sensor_last_timestamp[0] = raw.timestamp;
					}

					z_k[0] =  raw.gyro_rad_s[0] - gyro_offsets[0];
					z_k[1] =  raw.gyro_rad_s[1] - gyro_offsets[1];
					z_k[2] =  raw.gyro_rad_s[2] - gyro_offsets[2];

					/* update accelerometer measurements */
					if (sensor_last_count[1] != raw.accelerometer_counter) {
						update_vect[1] = 1;
						sensor_last_count[1] = raw.accelerometer_counter;
						sensor_update_hz[1] = 1e6f / (raw.timestamp - sensor_last_timestamp[1]);
						sensor_last_timestamp[1] = raw.timestamp;
					}

					z_k[3] = raw.accelerometer_m_s2[0];
					z_k[4] = raw.accelerometer_m_s2[1];
					z_k[5] = raw.accelerometer_m_s2[2];

					/* update magnetometer measurements */
					if (sensor_last_count[2] != raw.magnetometer_counter) {
						update_vect[2] = 1;
						sensor_last_count[2] = raw.magnetometer_counter;
						sensor_update_hz[2] = 1e6f / (raw.timestamp - sensor_last_timestamp[2]);
						sensor_last_timestamp[2] = raw.timestamp;
					}

					z_k[6] = raw.magnetometer_ga[0];
					z_k[7] = raw.magnetometer_ga[1];
					z_k[8] = raw.magnetometer_ga[2];

					uint64_t now = hrt_absolute_time();
					unsigned int time_elapsed = now - last_run;
					last_run = now;

					if (time_elapsed > loop_interval_alarm) {
						//TODO: add warning, cpu overload here
						// if (overloadcounter == 20) {
						// 	printf("CPU OVERLOAD DETECTED IN ATTITUDE ESTIMATOR EKF (%lu > %lu)\n", time_elapsed, loop_interval_alarm);
						// 	overloadcounter = 0;
						// }

						overloadcounter++;
					}

					static bool const_initialized = false;
                    

					/* initialize with good values once we have a reasonable dt estimate */
					if (!const_initialized && dt < 0.05f && dt > 0.001f) {

						dt = 0.005f;
						parameters_update(&madgwick_param_handles, &madgwick_params);



						const_initialized = true;
					}
                    

					/* do not execute the filter if not initialized */
					if (!const_initialized) {
						continue;
					}

                    
					uint64_t timing_start = hrt_absolute_time();

					//attitudeKalmanfilter(update_vect, dt, z_k, x_aposteriori_k, P_aposteriori_k, ekf_params.q, ekf_params.r,
					//		     euler, Rot_matrix, x_aposteriori, P_aposteriori);
					using namespace math;

					Quaternion q = Quaternion(AttitudeUpdate(dt,madgwick_params.beta,madgwick_params.zeta, z_k[3], z_k[4], z_k[5], z_k[0], z_k[1], z_k[2], z_k[6], z_k[7], z_k[8]));
					Dcm C = Dcm(q);
					// euler update
					EulerAngles _euler = EulerAngles(C);


					/* swap values for next iteration, check for fatal inputs */
					if (isfinite(euler[0]) && isfinite(euler[1]) && isfinite(euler[2])) {
						//memcpy(P_aposteriori_k, P_aposteriori, sizeof(P_aposteriori_k));
						//memcpy(x_aposteriori_k, x_aposteriori, sizeof(x_aposteriori_k));

					} else {
						/* due to inputs or numerical failure the output is invalid, skip it */
						continue;
					}

					if (last_data > 0 && raw.timestamp - last_data > 12000)
						printf("[attitude estimator madgwick] sensor data missed! (%llu)\n", raw.timestamp - last_data);

					last_data = raw.timestamp;

					/* send out */
					att.timestamp = raw.timestamp;

					// XXX Apply the same transformation to the rotation matrix
					att.roll = _euler.getPhi();// - ekf_params.roll_off;
					att.pitch = _euler.getTheta();// - ekf_params.pitch_off;
					att.yaw = _euler.getPsi();// - ekf_params.yaw_off;

					float gyro_biases[3];
					getBiases(gyro_biases);
					att.rollspeed = raw.gyro_rad_s[0] - gyro_offsets[0]- gyro_biases[0];
					att.pitchspeed = raw.gyro_rad_s[1]- gyro_offsets[1] - gyro_biases[1];
					att.yawspeed = raw.gyro_rad_s[2]- gyro_offsets[2] - gyro_biases[2];
					//att.rollacc = x_aposteriori[3];
					//att.pitchacc = x_aposteriori[4];
					//att.yawacc = x_aposteriori[5];

					//att.yawspeed =z_k[2] ;
					/* copy offsets */
					//memcpy(&att.rate_offsets, (gyro_biases), sizeof(att.rate_offsets));

					/* copy rotation matrix */
					for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
								att.R[i][j] = C(i, j);

					for (int i = 0; i < 4; i++) att.q[i] = q(i);

					att.R_valid = true;
                    
                    printf("5\n");

					if (isfinite(att.roll) && isfinite(att.pitch) && isfinite(att.yaw)) {
						// Broadcast
						orb_publish(ORB_ID(vehicle_attitude), pub_att, &att);

					} else {
						warnx("NaN in roll/pitch/yaw estimate!");
					}

					perf_end(madgwick_loop_perf);
				}
			}
		}

		loopcounter++;
	}

	thread_running = false;

	return 0;
}
