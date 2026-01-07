/*
 * data_model.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Aalekh Sharma
 */

#ifndef DATA_MODEL_H_
#define DATA_MODEL_H_

#include <stdint.h>

/* ============================
 * Configuration Limits
 * ============================ */

/* Adjust these values based on memory constraints */
#define MAX_DEVICES             4
#define MAX_DATA_POINTS         4

#define MAX_STR_GATEWAY_ID      32
#define MAX_STR_DEVICE_TYPE     16
#define MAX_STR_MEDIA           16
#define MAX_STR_METER           16
#define MAX_STR_DEVICE_ID       32
#define MAX_STR_UNIT            8
#define MAX_STR_STATUS          8
#define MAX_STR_DATE            11   /* YYYY-MM-DD + '\0' */
#define MAX_STR_TIMESTAMP       17   /* YYYY-MM-DD HH:MM + '\0' */

/* ============================
 * Data Point (inner "data" array)
 * ============================ */
typedef struct
{
    char timestamp[MAX_STR_TIMESTAMP];
    char meter_datetime[MAX_STR_TIMESTAMP];
    float total_m3;
    char status[MAX_STR_STATUS];

} meter_data_point_t;

/* ============================
 * Device Reading
 * ============================ */
typedef struct
{
    char media[MAX_STR_MEDIA];
    char meter[MAX_STR_METER];
    char device_id[MAX_STR_DEVICE_ID];
    char unit[MAX_STR_UNIT];

    uint8_t data_count;
    meter_data_point_t data[MAX_DATA_POINTS];

} device_reading_t;

/* ============================
 * Values Object
 * ============================ */
typedef struct
{
    uint8_t device_count;
    device_reading_t readings[MAX_DEVICES];

} values_t;

/* ============================
 * Gateway-Level Metadata
 * ============================ */
typedef struct
{
    char gateway_id[MAX_STR_GATEWAY_ID];
    char date[MAX_STR_DATE];
    char device_type[MAX_STR_DEVICE_TYPE];

    uint16_t interval_minutes;
    uint16_t total_readings;

    values_t values;

} gateway_data_t;

#endif /* DATA_MODEL_H_ */
