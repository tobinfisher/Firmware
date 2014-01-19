// MESSAGE GPS_RAW_INT_S PACKING

#define MAVLINK_MSG_ID_GPS_RAW_INT_S 144

typedef struct __mavlink_gps_raw_int_s_t
{
 int32_t lat; ///< Latitude (WGS84), in degrees * 1E7
 int32_t lon; ///< Longitude (WGS84), in degrees * 1E7
 uint16_t eph; ///< GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: UINT16_MAX
} mavlink_gps_raw_int_s_t;

#define MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN 10
#define MAVLINK_MSG_ID_144_LEN 10

#define MAVLINK_MSG_ID_GPS_RAW_INT_S_CRC 106
#define MAVLINK_MSG_ID_144_CRC 106



#define MAVLINK_MESSAGE_INFO_GPS_RAW_INT_S { \
	"GPS_RAW_INT_S", \
	3, \
	{  { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_gps_raw_int_s_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_gps_raw_int_s_t, lon) }, \
         { "eph", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_gps_raw_int_s_t, eph) }, \
         } \
}


/**
 * @brief Pack a gps_raw_int_s message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat Latitude (WGS84), in degrees * 1E7
 * @param lon Longitude (WGS84), in degrees * 1E7
 * @param eph GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_int_s_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int32_t lat, int32_t lon, uint16_t eph)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN];
	_mav_put_int32_t(buf, 0, lat);
	_mav_put_int32_t(buf, 4, lon);
	_mav_put_uint16_t(buf, 8, eph);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#else
	mavlink_gps_raw_int_s_t packet;
	packet.lat = lat;
	packet.lon = lon;
	packet.eph = eph;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS_RAW_INT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN, MAVLINK_MSG_ID_GPS_RAW_INT_S_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif
}

/**
 * @brief Pack a gps_raw_int_s message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat Latitude (WGS84), in degrees * 1E7
 * @param lon Longitude (WGS84), in degrees * 1E7
 * @param eph GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: UINT16_MAX
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_int_s_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int32_t lat,int32_t lon,uint16_t eph)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN];
	_mav_put_int32_t(buf, 0, lat);
	_mav_put_int32_t(buf, 4, lon);
	_mav_put_uint16_t(buf, 8, eph);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#else
	mavlink_gps_raw_int_s_t packet;
	packet.lat = lat;
	packet.lon = lon;
	packet.eph = eph;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS_RAW_INT_S;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN, MAVLINK_MSG_ID_GPS_RAW_INT_S_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif
}

/**
 * @brief Encode a gps_raw_int_s struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_raw_int_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_raw_int_s_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_raw_int_s_t* gps_raw_int_s)
{
	return mavlink_msg_gps_raw_int_s_pack(system_id, component_id, msg, gps_raw_int_s->lat, gps_raw_int_s->lon, gps_raw_int_s->eph);
}

/**
 * @brief Encode a gps_raw_int_s struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gps_raw_int_s C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_raw_int_s_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gps_raw_int_s_t* gps_raw_int_s)
{
	return mavlink_msg_gps_raw_int_s_pack_chan(system_id, component_id, chan, msg, gps_raw_int_s->lat, gps_raw_int_s->lon, gps_raw_int_s->eph);
}

/**
 * @brief Send a gps_raw_int_s message
 * @param chan MAVLink channel to send the message
 *
 * @param lat Latitude (WGS84), in degrees * 1E7
 * @param lon Longitude (WGS84), in degrees * 1E7
 * @param eph GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: UINT16_MAX
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_raw_int_s_send(mavlink_channel_t chan, int32_t lat, int32_t lon, uint16_t eph)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN];
	_mav_put_int32_t(buf, 0, lat);
	_mav_put_int32_t(buf, 4, lon);
	_mav_put_uint16_t(buf, 8, eph);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_RAW_INT_S, buf, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN, MAVLINK_MSG_ID_GPS_RAW_INT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_RAW_INT_S, buf, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif
#else
	mavlink_gps_raw_int_s_t packet;
	packet.lat = lat;
	packet.lon = lon;
	packet.eph = eph;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_RAW_INT_S, (const char *)&packet, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN, MAVLINK_MSG_ID_GPS_RAW_INT_S_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_RAW_INT_S, (const char *)&packet, MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif
#endif
}

#endif

// MESSAGE GPS_RAW_INT_S UNPACKING


/**
 * @brief Get field lat from gps_raw_int_s message
 *
 * @return Latitude (WGS84), in degrees * 1E7
 */
static inline int32_t mavlink_msg_gps_raw_int_s_get_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from gps_raw_int_s message
 *
 * @return Longitude (WGS84), in degrees * 1E7
 */
static inline int32_t mavlink_msg_gps_raw_int_s_get_lon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field eph from gps_raw_int_s message
 *
 * @return GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: UINT16_MAX
 */
static inline uint16_t mavlink_msg_gps_raw_int_s_get_eph(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Decode a gps_raw_int_s message into a struct
 *
 * @param msg The message to decode
 * @param gps_raw_int_s C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_raw_int_s_decode(const mavlink_message_t* msg, mavlink_gps_raw_int_s_t* gps_raw_int_s)
{
#if MAVLINK_NEED_BYTE_SWAP
	gps_raw_int_s->lat = mavlink_msg_gps_raw_int_s_get_lat(msg);
	gps_raw_int_s->lon = mavlink_msg_gps_raw_int_s_get_lon(msg);
	gps_raw_int_s->eph = mavlink_msg_gps_raw_int_s_get_eph(msg);
#else
	memcpy(gps_raw_int_s, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GPS_RAW_INT_S_LEN);
#endif
}
