// MESSAGE CONTROL_TILT PACKING

#define MAVLINK_MSG_ID_CONTROL_TILT 150

typedef struct __mavlink_control_tilt_t
{
 int8_t x; ///< X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 int8_t y; ///< Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
} mavlink_control_tilt_t;

#define MAVLINK_MSG_ID_CONTROL_TILT_LEN 2
#define MAVLINK_MSG_ID_150_LEN 2

#define MAVLINK_MSG_ID_CONTROL_TILT_CRC 240
#define MAVLINK_MSG_ID_150_CRC 240



#define MAVLINK_MESSAGE_INFO_CONTROL_TILT { \
	"CONTROL_TILT", \
	2, \
	{  { "x", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_control_tilt_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_control_tilt_t, y) }, \
         } \
}


/**
 * @brief Pack a control_tilt message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int8_t x, int8_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#else
	mavlink_control_tilt_t packet;
	packet.x = x;
	packet.y = y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_LEN, MAVLINK_MSG_ID_CONTROL_TILT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif
}

/**
 * @brief Pack a control_tilt message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int8_t x,int8_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#else
	mavlink_control_tilt_t packet;
	packet.x = x;
	packet.y = y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_LEN, MAVLINK_MSG_ID_CONTROL_TILT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif
}

/**
 * @brief Encode a control_tilt struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_control_tilt_t* control_tilt)
{
	return mavlink_msg_control_tilt_pack(system_id, component_id, msg, control_tilt->x, control_tilt->y);
}

/**
 * @brief Encode a control_tilt struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_control_tilt_t* control_tilt)
{
	return mavlink_msg_control_tilt_pack_chan(system_id, component_id, chan, msg, control_tilt->x, control_tilt->y);
}

/**
 * @brief Send a control_tilt message
 * @param chan MAVLink channel to send the message
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_control_tilt_send(mavlink_channel_t chan, int8_t x, int8_t y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT, buf, MAVLINK_MSG_ID_CONTROL_TILT_LEN, MAVLINK_MSG_ID_CONTROL_TILT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT, buf, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif
#else
	mavlink_control_tilt_t packet;
	packet.x = x;
	packet.y = y;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_LEN, MAVLINK_MSG_ID_CONTROL_TILT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif
#endif
}

#endif

// MESSAGE CONTROL_TILT UNPACKING


/**
 * @brief Get field x from control_tilt message
 *
 * @return X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Get field y from control_tilt message
 *
 * @return Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Decode a control_tilt message into a struct
 *
 * @param msg The message to decode
 * @param control_tilt C-struct to decode the message contents into
 */
static inline void mavlink_msg_control_tilt_decode(const mavlink_message_t* msg, mavlink_control_tilt_t* control_tilt)
{
#if MAVLINK_NEED_BYTE_SWAP
	control_tilt->x = mavlink_msg_control_tilt_get_x(msg);
	control_tilt->y = mavlink_msg_control_tilt_get_y(msg);
#else
	memcpy(control_tilt, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CONTROL_TILT_LEN);
#endif
}
