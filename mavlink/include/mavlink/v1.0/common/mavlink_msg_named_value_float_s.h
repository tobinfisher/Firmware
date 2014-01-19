// MESSAGE NAMED_VALUE_FLOAT_S PACKING

#define MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S 143

typedef struct __mavlink_named_value_float_s_t
{
 float value; ///< Floating point value
 char name[4]; ///< Name of the debug variable
} mavlink_named_value_float_s_t;

#define MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN 8
#define MAVLINK_MSG_ID_143_LEN 8

#define MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_CRC 0
#define MAVLINK_MSG_ID_143_CRC 0

#define MAVLINK_MSG_NAMED_VALUE_FLOAT_S_FIELD_NAME_LEN 4

#define MAVLINK_MESSAGE_INFO_NAMED_VALUE_FLOAT_S { \
	"NAMED_VALUE_FLOAT_S", \
	2, \
	{  { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_named_value_float_s_t, value) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 4, 4, offsetof(mavlink_named_value_float_s_t, name) }, \
         } \
}


/**
 * @brief Pack a named_value_float_s message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param name Name of the debug variable
 * @param value Floating point value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_named_value_float_s_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const char *name, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN];
	_mav_put_float(buf, 0, value);
	_mav_put_char_array(buf, 4, name, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#else
	mavlink_named_value_float_s_t packet;
	packet.value = value;
	mav_array_memcpy(packet.name, name, sizeof(char)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif
}

/**
 * @brief Pack a named_value_float_s message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param name Name of the debug variable
 * @param value Floating point value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_named_value_float_s_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const char *name,float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN];
	_mav_put_float(buf, 0, value);
	_mav_put_char_array(buf, 4, name, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#else
	mavlink_named_value_float_s_t packet;
	packet.value = value;
	mav_array_memcpy(packet.name, name, sizeof(char)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif
}

/**
 * @brief Encode a named_value_float_s struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param named_value_float_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_named_value_float_s_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_named_value_float_s_t* named_value_float_s)
{
	return mavlink_msg_named_value_float_s_pack(system_id, component_id, msg, named_value_float_s->name, named_value_float_s->value);
}

/**
 * @brief Encode a named_value_float_s struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param named_value_float_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_named_value_float_s_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_named_value_float_s_t* named_value_float_s)
{
	return mavlink_msg_named_value_float_s_pack_chan(system_id, component_id, chan, msg, named_value_float_s->name, named_value_float_s->value);
}

/**
 * @brief Send a named_value_float_s message
 * @param chan MAVLink channel to send the message
 *
 * @param name Name of the debug variable
 * @param value Floating point value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_named_value_float_s_send(mavlink_channel_t chan, const char *name, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN];
	_mav_put_float(buf, 0, value);
	_mav_put_char_array(buf, 4, name, 4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S, buf, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S, buf, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif
#else
	mavlink_named_value_float_s_t packet;
	packet.value = value;
	mav_array_memcpy(packet.name, name, sizeof(char)*4);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S, (const char *)&packet, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S, (const char *)&packet, MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif
#endif
}

#endif

// MESSAGE NAMED_VALUE_FLOAT_S UNPACKING


/**
 * @brief Get field name from named_value_float_s message
 *
 * @return Name of the debug variable
 */
static inline uint16_t mavlink_msg_named_value_float_s_get_name(const mavlink_message_t* msg, char *name)
{
	return _MAV_RETURN_char_array(msg, name, 4,  4);
}

/**
 * @brief Get field value from named_value_float_s message
 *
 * @return Floating point value
 */
static inline float mavlink_msg_named_value_float_s_get_value(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a named_value_float_s message into a struct
 *
 * @param msg The message to decode
 * @param named_value_float_s C-struct to decode the message contents into
 */
static inline void mavlink_msg_named_value_float_s_decode(const mavlink_message_t* msg, mavlink_named_value_float_s_t* named_value_float_s)
{
#if MAVLINK_NEED_BYTE_SWAP
	named_value_float_s->value = mavlink_msg_named_value_float_s_get_value(msg);
	mavlink_msg_named_value_float_s_get_name(msg, named_value_float_s->name);
#else
	memcpy(named_value_float_s, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_NAMED_VALUE_FLOAT_S_LEN);
#endif
}
