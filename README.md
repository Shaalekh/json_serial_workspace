
# json_serializer — Embedded JSON Serialization Library (STM32)

## Project Overview

This repository contains an **embedded-friendly JSON serialization library** designed for STM32-based firmware projects. The library converts structured meter and gateway data into a **strict, predefined JSON format** suitable for gateway/backend integration in smart-meter or w-M-Bus–related systems.

The serializer is implemented as a **standalone static library** with no hardware or transport dependencies. A separate example project demonstrates how to use the library and outputs the generated JSON via UART.

---

## Features

- Pure C implementation suitable for embedded systems
- No dynamic memory allocation in the serialization core
- No external JSON libraries
- Transport-agnostic design (no UART, radio, MQTT, etc. in the library)
- Serializes into a caller-provided buffer with overflow protection
- Clear error handling via return codes
- Separate example application using STM32 HAL + UART

---

## Repository Structure

```
/
├── json_serializer/               # Static library project
│   ├── Inc/
│   │   ├── data_model.h
│   │   └── json_serializer.h
│   └── Src/
│       └── json_serializer.c
├── json_serializer_example/       # Example STM32CubeIDE project
│   ├── Core/
│   │   ├── Inc/
│   │   └── Src/
│   │       └── main.c
│   └── STM32CubeIDE project files
├── README.md
└── LICENSE
```

---

## Platform and Language Choice

- **Platform:** STM32CubeIDE (STM32 microcontrollers)
  - Preferred by the assignment
  - Industry-standard environment for STM32 firmware development

- **Language:** C
  - Deterministic memory usage
  - Minimal runtime overhead
  - Well-suited for embedded firmware

---

## Data Model

The internal data structures are defined in:

```
json_serializer/Inc/data_model.h
```

Key characteristics:
- Fixed-size structures and strings (no heap usage)
- Compile-time configurable limits
- One-to-one mapping with the required JSON structure

Important configuration macros include:
- `MAX_DEVICES`
- `MAX_DATA_POINTS`
- `MAX_STR_GATEWAY_ID`
- `MAX_STR_DEVICE_ID`
- `MAX_STR_TIMESTAMP`

Changing these values directly affects memory usage and the maximum JSON output size.

---

## Public API

Header file:

```
json_serializer/Inc/json_serializer.h
```

```c
typedef enum
{
    JSON_SERIALIZER_OK = 0,
    JSON_SERIALIZER_ERR_NULL_PTR,
    JSON_SERIALIZER_ERR_BUFFER_TOO_SMALL,
    JSON_SERIALIZER_ERR_INVALID_DATA
} json_serializer_status_t;

json_serializer_status_t json_serialize(
    const gateway_data_t *input,
    char *output,
    size_t output_size,
    size_t *bytes_written
);
```

### API behavior

- Serializes the provided `gateway_data_t` structure into JSON
- Writes only into the caller-provided buffer
- Prevents buffer overflows
- Returns explicit error codes
- Does not perform any IO or hardware access

---

## Example Application

The `json_serializer_example` project demonstrates how to use the library:

1. Populate a `gateway_data_t` structure with sample data
2. Call `json_serialize(...)`
3. Output the generated JSON via UART (USART2)

The example uses STM32 HAL and prints the result to a serial monitor (e.g. 115200 baud, 8N1).

The example contains **no serialization logic** and exists purely as a usage demonstration.

---

## Example JSON Output

The library generates JSON exactly matching the required structure:

```json
[
{
"gatewayId":"gateway_1234",
"date":"1970-01-01",
"deviceType":"stromleser",
"interval_minutes":15,
"total_readings":1,
"values":{
"device_count":1,
"readings":[
{
"media":"water",
"meter":"waterstarm",
"deviceId":"stromleser_50898527",
"unit":"m3",
"data":[
{
"timestamp":"1970-01-01 00:00",
"meter_datetime":"1970-01-01 00:00",
"total_m3":107.752,
"status":"OK"
}
]
}
]
}
}
]
```

Field names, structure, and numeric types are **strict** and must not be changed.

---

## Maximum JSON Buffer Size

Using the default compile-time limits defined in `data_model.h` and conservative numeric width assumptions, the **worst-case JSON size** is approximately:

**≈ 2,481 bytes**

### Recommendation

- Use a buffer size of **at least 3 KiB**
- Prefer **4 KiB** for additional safety margin

If any `MAX_*` configuration macros are changed, this value must be recalculated.

---

## Design Decisions and Assumptions

- Fixed-size buffers are used to guarantee deterministic memory usage
- No external JSON libraries are allowed or used
- Output JSON is compact (no spaces or indentation)
- Floating-point values are formatted with three decimal places (`%.3f`)
- Error handling is explicit and simple

---

## Possible Extensions

- Compile-time calculation of maximum JSON buffer size
- Static assertions to enforce safe configuration limits
- Pretty-printed JSON option (for debugging)
- Host-side unit tests for the serializer
- Support for additional meter data fields (if requirements change)

---

## Build and Run (STM32CubeIDE)

1. Import both projects (`json_serializer` and `json_serializer_example`) into the same workspace
2. Build the `json_serializer` project (creates `libjson_serializer.a`)
3. In `json_serializer_example`:
   - Add `../json_serializer/Inc` to include paths
   - Add the library output directory (e.g. `../json_serializer/Debug`) to linker search paths
   - Link against `json_serializer`
4. Build the example project
5. Flash to the target and open the serial monitor

---
