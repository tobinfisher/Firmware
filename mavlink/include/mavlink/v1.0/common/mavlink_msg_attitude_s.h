// MESSAGE ATTITUDE_S PACKING

#define MAVLINK_MSG_ID_ATTITUDE_S 204

typedef struct __mavlink_attitude_s_t
{
 float roll; ///< Roll angle (rad, -pi..+pi)
 float pitch; ///< Pitch angle (rad, -pi..+pi)
 float yaw; ///< Yaw angle (rad, -pi..+pi)
} mavlink_attitude_s_t;

#define MAVLINK_MSG_ID_ATTITUDE_S_LEN 12
#define MAVLINK_MSG_ID_204_LEN 12

#define MAVLINK_MSG_ID_ATTITUDE_S_CRC 254
#define MAVLINK_MSG_ID_204_CRC 254



#define MAVLINK_MESSAGE_INFO_ATTITUDE_S { \
	"ATTITUDE_S", \
	3, \
	{  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_attitude_s_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_attitude_s_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_attitude_s_t, yaw) }, \
         } \
}


/**
 * @brief Pack a attitude_s message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_s_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_S_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#else
	mavlink_attitude_s_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ATTITUDE_S_LEN, MAVLINK_MSG_ID_ATTITUDE_S_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif
}

/**
 * @brief Pack a attitude_s message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_s_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float roll,float pitch,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_S_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#else
	mavlink_attitude_s_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ATTITUDE_S_LEN, MAVLINK_MSG_ID_ATTITUDE_S_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif
}

/**
 * @brief Encode a attitude_s struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param attitude_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_s_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_attitude_s_t* attitude_s)
{
	return mavlink_msg_attitude_s_pack(system_id, component_id, msg, attitude_s->roll, attitude_s->pitch, attitude_s->yaw);
}

/**
 * @brief Encode a attitude_s struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param attitude_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_s_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_attitude_s_t* attitude_s)
{
	return mavlink_msg_attitude_s_pack_chan(system_id, component_id, chan, msg, attitude_s->roll, attitude_s->pitch, attitude_s->yaw);
}

/**
 * @brief Send a attitude_s message
 * @param chan MAVLink channel to send the message
 *
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_attitude_s_send(mavlink_channel_t chan, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ATTITUDE_S_LEN];
	_mav_put_float(buf, 0, roll);
	_mav_put_float(buf, 4, pitch);
	_mav_put_float(buf, 8, yaw);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_S, buf, MAVLINK_MSG_ID_ATTITUDE_S_LEN, MAVLINK_MSG_ID_ATTITUDE_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_S, buf, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif
#else
	mavlink_attitude_s_t packet;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_S, (const char *)&packet, MAVLINK_MSG_ID_ATTITUDE_S_LEN, MAVLINK_MSG_ID_ATTITUDE_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ATTITUDE_S, (const char *)&packet, MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif
#endif
}

#endif

// MESSAGE ATTITUDE_S UNPACKING


/**
 * @brief Get field roll from attitude_s message
 *
 * @return Roll angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_attitude_s_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from attitude_s message
 *
 * @return Pitch angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_attitude_s_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw from attitude_s message
 *
 * @return Yaw angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_attitude_s_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a attitude_s message into a struct
 *
 * @param msg The message to decode
 * @param attitude_s C-struct to decode the message contents into
 */
static inline void mavlink_msg_attitude_s_decode(const mavlink_message_t* msg, mavlink_attitude_s_t* attitude_s)
{
#if MAVLINK_NEED_BYTE_SWAP
	attitude_s->roll = mavlink_msg_attitude_s_get_roll(msg);
	attitude_s->pitch = mavlink_msg_attitude_s_get_pitch(msg);
	attitude_s->yaw = mavlink_msg_attitude_s_get_yaw(msg);
#else
	memcpy(attitude_s, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ATTITUDE_S_LEN);
#endif
}
