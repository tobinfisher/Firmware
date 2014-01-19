// MESSAGE CONTROL_TILT_THRUST PACKING

#define MAVLINK_MSG_ID_CONTROL_TILT_THRUST 152

typedef struct __mavlink_control_tilt_thrust_t
{
 int8_t x; ///< X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 int8_t y; ///< Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 uint8_t z; ///< Z-axis, normalized to the range [0,256]. Generally corresponds to a separate slider movement with maximum being 256 and minimum being 0 on a joystick and the thrust of a vehicle.
} mavlink_control_tilt_thrust_t;

#define MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN 3
#define MAVLINK_MSG_ID_152_LEN 3

#define MAVLINK_MSG_ID_CONTROL_TILT_THRUST_CRC 248
#define MAVLINK_MSG_ID_152_CRC 248



#define MAVLINK_MESSAGE_INFO_CONTROL_TILT_THRUST { \
	"CONTROL_TILT_THRUST", \
	3, \
	{  { "x", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_control_tilt_thrust_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_control_tilt_thrust_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_control_tilt_thrust_t, z) }, \
         } \
}


/**
 * @brief Pack a control_tilt_thrust message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param z Z-axis, normalized to the range [0,256]. Generally corresponds to a separate slider movement with maximum being 256 and minimum being 0 on a joystick and the thrust of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_thrust_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int8_t x, int8_t y, uint8_t z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_uint8_t(buf, 2, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#else
	mavlink_control_tilt_thrust_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT_THRUST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif
}

/**
 * @brief Pack a control_tilt_thrust message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param z Z-axis, normalized to the range [0,256]. Generally corresponds to a separate slider movement with maximum being 256 and minimum being 0 on a joystick and the thrust of a vehicle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_control_tilt_thrust_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int8_t x,int8_t y,uint8_t z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_uint8_t(buf, 2, z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#else
	mavlink_control_tilt_thrust_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONTROL_TILT_THRUST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif
}

/**
 * @brief Encode a control_tilt_thrust struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt_thrust C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_thrust_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_control_tilt_thrust_t* control_tilt_thrust)
{
	return mavlink_msg_control_tilt_thrust_pack(system_id, component_id, msg, control_tilt_thrust->x, control_tilt_thrust->y, control_tilt_thrust->z);
}

/**
 * @brief Encode a control_tilt_thrust struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param control_tilt_thrust C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_control_tilt_thrust_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_control_tilt_thrust_t* control_tilt_thrust)
{
	return mavlink_msg_control_tilt_thrust_pack_chan(system_id, component_id, chan, msg, control_tilt_thrust->x, control_tilt_thrust->y, control_tilt_thrust->z);
}

/**
 * @brief Send a control_tilt_thrust message
 * @param chan MAVLink channel to send the message
 *
 * @param x X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 * @param y Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 * @param z Z-axis, normalized to the range [0,256]. Generally corresponds to a separate slider movement with maximum being 256 and minimum being 0 on a joystick and the thrust of a vehicle.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_control_tilt_thrust_send(mavlink_channel_t chan, int8_t x, int8_t y, uint8_t z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN];
	_mav_put_int8_t(buf, 0, x);
	_mav_put_int8_t(buf, 1, y);
	_mav_put_uint8_t(buf, 2, z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST, buf, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST, buf, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif
#else
	mavlink_control_tilt_thrust_t packet;
	packet.x = x;
	packet.y = y;
	packet.z = z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONTROL_TILT_THRUST, (const char *)&packet, MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif
#endif
}

#endif

// MESSAGE CONTROL_TILT_THRUST UNPACKING


/**
 * @brief Get field x from control_tilt_thrust message
 *
 * @return X-axis, normalized to the range [-128,128]. Generally corresponds to forward(128)-backward(-128) movement on a joystick and the pitch of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_thrust_get_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Get field y from control_tilt_thrust message
 *
 * @return Y-axis, normalized to the range [-128,128]. Generally corresponds to left(-128)-right(128) movement on a joystick and the roll of a vehicle.
 */
static inline int8_t mavlink_msg_control_tilt_thrust_get_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Get field z from control_tilt_thrust message
 *
 * @return Z-axis, normalized to the range [0,256]. Generally corresponds to a separate slider movement with maximum being 256 and minimum being 0 on a joystick and the thrust of a vehicle.
 */
static inline uint8_t mavlink_msg_control_tilt_thrust_get_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a control_tilt_thrust message into a struct
 *
 * @param msg The message to decode
 * @param control_tilt_thrust C-struct to decode the message contents into
 */
static inline void mavlink_msg_control_tilt_thrust_decode(const mavlink_message_t* msg, mavlink_control_tilt_thrust_t* control_tilt_thrust)
{
#if MAVLINK_NEED_BYTE_SWAP
	control_tilt_thrust->x = mavlink_msg_control_tilt_thrust_get_x(msg);
	control_tilt_thrust->y = mavlink_msg_control_tilt_thrust_get_y(msg);
	control_tilt_thrust->z = mavlink_msg_control_tilt_thrust_get_z(msg);
#else
	memcpy(control_tilt_thrust, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CONTROL_TILT_THRUST_LEN);
#endif
}
