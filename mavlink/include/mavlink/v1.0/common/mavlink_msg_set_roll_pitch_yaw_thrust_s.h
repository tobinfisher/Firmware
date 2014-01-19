// MESSAGE SET_ROLL_PITCH_YAW_THRUST_S PACKING

#define MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S 142

typedef struct __mavlink_set_roll_pitch_yaw_thrust_s_t
{
 float yaw; ///< Desired yaw angle in radians
 int8_t roll; ///< Desired roll angle in radians -127 .. 127 for +/- Pi/8 radians
 int8_t pitch; ///< Desired pitch angle in radians -127 .. 127 for +/- Pi/8 radians
 uint8_t thrust; ///< Collective thrust, normalized to 0 .. 256
} mavlink_set_roll_pitch_yaw_thrust_s_t;

#define MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN 7
#define MAVLINK_MSG_ID_142_LEN 7

#define MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_CRC 122
#define MAVLINK_MSG_ID_142_CRC 122



#define MAVLINK_MESSAGE_INFO_SET_ROLL_PITCH_YAW_THRUST_S { \
	"SET_ROLL_PITCH_YAW_THRUST_S", \
	4, \
	{  { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_roll_pitch_yaw_thrust_s_t, yaw) }, \
         { "roll", NULL, MAVLINK_TYPE_INT8_T, 0, 4, offsetof(mavlink_set_roll_pitch_yaw_thrust_s_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_INT8_T, 0, 5, offsetof(mavlink_set_roll_pitch_yaw_thrust_s_t, pitch) }, \
         { "thrust", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_set_roll_pitch_yaw_thrust_s_t, thrust) }, \
         } \
}


/**
 * @brief Pack a set_roll_pitch_yaw_thrust_s message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll Desired roll angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param pitch Desired pitch angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param yaw Desired yaw angle in radians
 * @param thrust Collective thrust, normalized to 0 .. 256
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_roll_pitch_yaw_thrust_s_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int8_t roll, int8_t pitch, float yaw, uint8_t thrust)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN];
	_mav_put_float(buf, 0, yaw);
	_mav_put_int8_t(buf, 4, roll);
	_mav_put_int8_t(buf, 5, pitch);
	_mav_put_uint8_t(buf, 6, thrust);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#else
	mavlink_set_roll_pitch_yaw_thrust_s_t packet;
	packet.yaw = yaw;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.thrust = thrust;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif
}

/**
 * @brief Pack a set_roll_pitch_yaw_thrust_s message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll Desired roll angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param pitch Desired pitch angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param yaw Desired yaw angle in radians
 * @param thrust Collective thrust, normalized to 0 .. 256
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_roll_pitch_yaw_thrust_s_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int8_t roll,int8_t pitch,float yaw,uint8_t thrust)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN];
	_mav_put_float(buf, 0, yaw);
	_mav_put_int8_t(buf, 4, roll);
	_mav_put_int8_t(buf, 5, pitch);
	_mav_put_uint8_t(buf, 6, thrust);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#else
	mavlink_set_roll_pitch_yaw_thrust_s_t packet;
	packet.yaw = yaw;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.thrust = thrust;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif
}

/**
 * @brief Encode a set_roll_pitch_yaw_thrust_s struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_roll_pitch_yaw_thrust_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_roll_pitch_yaw_thrust_s_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_roll_pitch_yaw_thrust_s_t* set_roll_pitch_yaw_thrust_s)
{
	return mavlink_msg_set_roll_pitch_yaw_thrust_s_pack(system_id, component_id, msg, set_roll_pitch_yaw_thrust_s->roll, set_roll_pitch_yaw_thrust_s->pitch, set_roll_pitch_yaw_thrust_s->yaw, set_roll_pitch_yaw_thrust_s->thrust);
}

/**
 * @brief Encode a set_roll_pitch_yaw_thrust_s struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_roll_pitch_yaw_thrust_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_roll_pitch_yaw_thrust_s_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_roll_pitch_yaw_thrust_s_t* set_roll_pitch_yaw_thrust_s)
{
	return mavlink_msg_set_roll_pitch_yaw_thrust_s_pack_chan(system_id, component_id, chan, msg, set_roll_pitch_yaw_thrust_s->roll, set_roll_pitch_yaw_thrust_s->pitch, set_roll_pitch_yaw_thrust_s->yaw, set_roll_pitch_yaw_thrust_s->thrust);
}

/**
 * @brief Send a set_roll_pitch_yaw_thrust_s message
 * @param chan MAVLink channel to send the message
 *
 * @param roll Desired roll angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param pitch Desired pitch angle in radians -127 .. 127 for +/- Pi/8 radians
 * @param yaw Desired yaw angle in radians
 * @param thrust Collective thrust, normalized to 0 .. 256
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_roll_pitch_yaw_thrust_s_send(mavlink_channel_t chan, int8_t roll, int8_t pitch, float yaw, uint8_t thrust)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN];
	_mav_put_float(buf, 0, yaw);
	_mav_put_int8_t(buf, 4, roll);
	_mav_put_int8_t(buf, 5, pitch);
	_mav_put_uint8_t(buf, 6, thrust);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S, buf, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S, buf, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif
#else
	mavlink_set_roll_pitch_yaw_thrust_s_t packet;
	packet.yaw = yaw;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.thrust = thrust;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S, (const char *)&packet, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S, (const char *)&packet, MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif
#endif
}

#endif

// MESSAGE SET_ROLL_PITCH_YAW_THRUST_S UNPACKING


/**
 * @brief Get field roll from set_roll_pitch_yaw_thrust_s message
 *
 * @return Desired roll angle in radians -127 .. 127 for +/- Pi/8 radians
 */
static inline int8_t mavlink_msg_set_roll_pitch_yaw_thrust_s_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  4);
}

/**
 * @brief Get field pitch from set_roll_pitch_yaw_thrust_s message
 *
 * @return Desired pitch angle in radians -127 .. 127 for +/- Pi/8 radians
 */
static inline int8_t mavlink_msg_set_roll_pitch_yaw_thrust_s_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  5);
}

/**
 * @brief Get field yaw from set_roll_pitch_yaw_thrust_s message
 *
 * @return Desired yaw angle in radians
 */
static inline float mavlink_msg_set_roll_pitch_yaw_thrust_s_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field thrust from set_roll_pitch_yaw_thrust_s message
 *
 * @return Collective thrust, normalized to 0 .. 256
 */
static inline uint8_t mavlink_msg_set_roll_pitch_yaw_thrust_s_get_thrust(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Decode a set_roll_pitch_yaw_thrust_s message into a struct
 *
 * @param msg The message to decode
 * @param set_roll_pitch_yaw_thrust_s C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_roll_pitch_yaw_thrust_s_decode(const mavlink_message_t* msg, mavlink_set_roll_pitch_yaw_thrust_s_t* set_roll_pitch_yaw_thrust_s)
{
#if MAVLINK_NEED_BYTE_SWAP
	set_roll_pitch_yaw_thrust_s->yaw = mavlink_msg_set_roll_pitch_yaw_thrust_s_get_yaw(msg);
	set_roll_pitch_yaw_thrust_s->roll = mavlink_msg_set_roll_pitch_yaw_thrust_s_get_roll(msg);
	set_roll_pitch_yaw_thrust_s->pitch = mavlink_msg_set_roll_pitch_yaw_thrust_s_get_pitch(msg);
	set_roll_pitch_yaw_thrust_s->thrust = mavlink_msg_set_roll_pitch_yaw_thrust_s_get_thrust(msg);
#else
	memcpy(set_roll_pitch_yaw_thrust_s, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST_S_LEN);
#endif
}
