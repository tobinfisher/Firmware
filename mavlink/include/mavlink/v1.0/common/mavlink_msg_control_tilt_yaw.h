// MESSAGE CONTROL_TILT_YAW PACKING

#define MAVLINK_MSG_ID_CONTROL_TILT_YAW 151

typedef struct __mavlink_control_tilt_yaw_t
{
 int8_t x; ///< X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 int8_t y; ///< Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 int8_t r; ///< R-axis, normalized to the range [-128,128]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to a twisting of the joystick, with counter-clockwise being 128 and clockwise being -128, and the yaw of a vehicle.
} mavlink_control_tilt_yaw_t;

#define MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN 3
#define MAVLINK_MSG_ID_151_LEN 3

#define MAVLINK_MSG_ID_CONTROL_TILT_YAW_CRC 196
#define MAVLINK_MSG_ID_151_CRC 196



#define MAVLINK_MESSAGE_INFO_CONTROL_TILT_YAW { \
	"CONTROL_TILT_YAW", \
	3, \
	{  { "x", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_control_tilt_yaw_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_control_tilt_yaw_t, y) }, \
         { "r", NULL, MAVLINK_TYPE_INT8_T, 0, 2, offsetof(mavlink_control_tilt_yaw_t, r) }, \
         } \
}


/**
 * @brief Pack a control_tilt_yaw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param r R-axis, normalized to the range [-128,128]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to a twisting of the joystick, with counter-clockwise being 128 and clockwise being -128, and the yaw of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_yaw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int8_t x, int8_t y, int8_t r)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_int8_t(buf, 2, r);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#else
	mavlink_control_tilt_yaw_t packet;
	packet.x = x;
	packet.y = y;
	packet.r = r;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT_YAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN, MAVLINK_MSG_ID_CONTROL_TILT_YAW_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif
}

/**
 * @brief Pack a control_tilt_yaw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param r R-axis, normalized to the range [-128,128]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to a twisting of the joystick, with counter-clockwise being 128 and clockwise being -128, and the yaw of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_yaw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int8_t x,int8_t y,int8_t r)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_int8_t(buf, 2, r);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#else
	mavlink_control_tilt_yaw_t packet;
	packet.x = x;
	packet.y = y;
	packet.r = r;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT_YAW;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN, MAVLINK_MSG_ID_CONTROL_TILT_YAW_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif
}

/**
 * @brief Encode a control_tilt_yaw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt_yaw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_yaw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_control_tilt_yaw_t* control_tilt_yaw)
{
	return mavlink_msg_control_tilt_yaw_pack(system_id, component_id, msg, control_tilt_yaw->x, control_tilt_yaw->y, control_tilt_yaw->r);
}

/**
 * @brief Encode a control_tilt_yaw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt_yaw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_yaw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_control_tilt_yaw_t* control_tilt_yaw)
{
	return mavlink_msg_control_tilt_yaw_pack_chan(system_id, component_id, chan, msg, control_tilt_yaw->x, control_tilt_yaw->y, control_tilt_yaw->r);
}

/**
 * @brief Send a control_tilt_yaw message
 * @param chan MAVLink channel to send the message
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param r R-axis, normalized to the range [-128,128]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to a twisting of the joystick, with counter-clockwise being 128 and clockwise being -128, and the yaw of a vehicle.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_control_tilt_yaw_send(mavlink_channel_t chan, int8_t x, int8_t y, int8_t r)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_int8_t(buf, 2, r);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW, buf, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN, MAVLINK_MSG_ID_CONTROL_TILT_YAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW, buf, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif
#else
	mavlink_control_tilt_yaw_t packet;
	packet.x = x;
	packet.y = y;
	packet.r = r;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN, MAVLINK_MSG_ID_CONTROL_TILT_YAW_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_YAW, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif
#endif
}

#endif

// MESSAGE CONTROL_TILT_YAW UNPACKING


/**
 * @brief Get field x from control_tilt_yaw message
 *
 * @return X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_yaw_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Get field y from control_tilt_yaw message
 *
 * @return Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_yaw_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Get field r from control_tilt_yaw message
 *
 * @return R-axis, normalized to the range [-128,128]. A value of INT16_MAX indicates that this axis is invalid. Generally corresponds to a twisting of the joystick, with counter-clockwise being 128 and clockwise being -128, and the yaw of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_yaw_get_r(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  2);
}

/**
 * @brief Decode a control_tilt_yaw message into a struct
 *
 * @param msg The message to decode
 * @param control_tilt_yaw C-struct to decode the message contents into
 */
static inline void mavlink_msg_control_tilt_yaw_decode(const mavlink_message_t* msg, mavlink_control_tilt_yaw_t* control_tilt_yaw)
{
#if MAVLINK_NEED_BYTE_SWAP
	control_tilt_yaw->x = mavlink_msg_control_tilt_yaw_get_x(msg);
	control_tilt_yaw->y = mavlink_msg_control_tilt_yaw_get_y(msg);
	control_tilt_yaw->r = mavlink_msg_control_tilt_yaw_get_r(msg);
#else
	memcpy(control_tilt_yaw, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CONTROL_TILT_YAW_LEN);
#endif
}
