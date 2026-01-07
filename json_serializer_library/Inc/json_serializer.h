/*
 * json_serializer.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Aalekh Sharma
 */

#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include <stddef.h>
#include "data_model.h"

/* ============================
 * Return / Error Codes
 * ============================ */
typedef enum
{
    JSON_SERIALIZER_OK = 0,
    JSON_SERIALIZER_ERR_NULL_PTR,
    JSON_SERIALIZER_ERR_BUFFER_TOO_SMALL,
    JSON_SERIALIZER_ERR_INVALID_DATA

} json_serializer_status_t;

/* ============================
 * API
 * ============================ */
/**
 * @brief Serialize gateway data into JSON format
 *
 * @param input          Pointer to populated gateway_data_t structure
 * @param output         Caller-provided output buffer
 * @param output_size    Size of output buffer in bytes
 * @param bytes_written  Number of bytes written (excluding null terminator)
 *
 * @return json_serializer_status_t
 */
json_serializer_status_t json_serialize(
    const gateway_data_t *input,
    char *output,
    size_t output_size,
    size_t *bytes_written
);

#endif /* JSON_SERIALIZER_H_ */
