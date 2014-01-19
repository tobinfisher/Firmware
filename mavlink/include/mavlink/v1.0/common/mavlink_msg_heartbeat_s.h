// MESSAGE HEARTBEAT_S PACKING

#define MAVLINK_MSG_ID_HEARTBEAT_S 145

typedef struct __mavlink_heartbeat_s_t
{
 uint32_t custom_mode; ///< A bitfield for use for autopilot-specific flags.
 uint8_t base_mode; ///< System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
} mavlink_heartbeat_s_t;

#define MAVLINK_MSG_ID_HEARTBEAT_S_LEN 5
#define MAVLINK_MSG_ID_145_LEN 5

#define MAVLINK_MSG_ID_HEARTBEAT_S_CRC 225
#define MAVLINK_MSG_ID_145_CRC 225



#define MAVLINK_MESSAGE_INFO_HEARTBEAT_S { \
	"HEARTBEAT_S", \
	2, \
	{  { "custom_mode", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_heartbeat_s_t, custom_mode) }, \
         { "base_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_heartbeat_s_t, base_mode) }, \
         } \
}


/**
 * @brief Pack a heartbeat_s message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param base_mode System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
 * @param custom_mode A bitfield for use for autopilot-specific flags.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_s_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t base_mode, uint32_t custom_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HEARTBEAT_S_LEN];
	_mav_put_uint32_t(buf, 0, custom_mode);
	_mav_put_uint8_t(buf, 4, base_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#else
	mavlink_heartbeat_s_t packet;
	packet.custom_mode = custom_mode;
	packet.base_mode = base_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HEARTBEAT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HEARTBEAT_S_LEN, MAVLINK_MSG_ID_HEARTBEAT_S_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif
}

/**
 * @brief Pack a heartbeat_s message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param base_mode System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
 * @param custom_mode A bitfield for use for autopilot-specific flags.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_s_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t base_mode,uint32_t custom_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HEARTBEAT_S_LEN];
	_mav_put_uint32_t(buf, 0, custom_mode);
	_mav_put_uint8_t(buf, 4, base_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#else
	mavlink_heartbeat_s_t packet;
	packet.custom_mode = custom_mode;
	packet.base_mode = base_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HEARTBEAT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HEARTBEAT_S_LEN, MAVLINK_MSG_ID_HEARTBEAT_S_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif
}

/**
 * @brief Encode a heartbeat_s struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_s_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_heartbeat_s_t* heartbeat_s)
{
	return mavlink_msg_heartbeat_s_pack(system_id, component_id, msg, heartbeat_s->base_mode, heartbeat_s->custom_mode);
}

/**
 * @brief Encode a heartbeat_s struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_s_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_heartbeat_s_t* heartbeat_s)
{
	return mavlink_msg_heartbeat_s_pack_chan(system_id, component_id, chan, msg, heartbeat_s->base_mode, heartbeat_s->custom_mode);
}

/**
 * @brief Send a heartbeat_s message
 * @param chan MAVLink channel to send the message
 *
 * @param base_mode System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
 * @param custom_mode A bitfield for use for autopilot-specific flags.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_s_send(mavlink_channel_t chan, uint8_t base_mode, uint32_t custom_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HEARTBEAT_S_LEN];
	_mav_put_uint32_t(buf, 0, custom_mode);
	_mav_put_uint8_t(buf, 4, base_mode);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT_S, buf, MAVLINK_MSG_ID_HEARTBEAT_S_LEN, MAVLINK_MSG_ID_HEARTBEAT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT_S, buf, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif
#else
	mavlink_heartbeat_s_t packet;
	packet.custom_mode = custom_mode;
	packet.base_mode = base_mode;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT_S, (const char *)&packet, MAVLINK_MSG_ID_HEARTBEAT_S_LEN, MAVLINK_MSG_ID_HEARTBEAT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEARTBEAT_S, (const char *)&packet, MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif
#endif
}

#endif

// MESSAGE HEARTBEAT_S UNPACKING


/**
 * @brief Get field base_mode from heartbeat_s message
 *
 * @return System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
 */
static inline uint8_t mavlink_msg_heartbeat_s_get_base_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field custom_mode from heartbeat_s message
 *
 * @return A bitfield for use for autopilot-specific flags.
 */
static inline uint32_t mavlink_msg_heartbeat_s_get_custom_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a heartbeat_s message into a struct
 *
 * @param msg The message to decode
 * @param heartbeat_s C-struct to decode the message contents into
 */
static inline void mavlink_msg_heartbeat_s_decode(const mavlink_message_t* msg, mavlink_heartbeat_s_t* heartbeat_s)
{
#if MAVLINK_NEED_BYTE_SWAP
	heartbeat_s->custom_mode = mavlink_msg_heartbeat_s_get_custom_mode(msg);
	heartbeat_s->base_mode = mavlink_msg_heartbeat_s_get_base_mode(msg);
#else
	memcpy(heartbeat_s, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_HEARTBEAT_S_LEN);
#endif
}
