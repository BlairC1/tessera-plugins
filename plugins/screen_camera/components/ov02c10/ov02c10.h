/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_cam_sensor_types.h"

#define OV02C10_SCCB_ADDR   0x36

/**
 * @brief Power on camera sensor device and detect the device connected to the designated sccb bus.
 *
 * @param[in] config Configuration related to device power-on and detection.
 * @return
 *      - Camera device handle on success, otherwise, failed.
 */
esp_cam_sensor_device_t *ov02c10_detect(esp_cam_sensor_config_t *config);

/**
 * @brief The slowest frame rate auto exposure may bring the sensor to (Blair, 2026-11-14).
 *
 * With one set, auto exposure may ask for an exposure of up to 1/fps second, and the sensor makes each frame as long
 * as its exposure needs: the set frame rate in good light, slower in a dark room, never slower than this. Call it
 * before the camera is set up (the ISP pipeline reads the longest exposure once, when it starts). 0, the default:
 * exposure never past the format's own frame, 1/30 s.
 *
 * @param[in] fps Frames a second, 2 or more; 0 for none.
 */
void ov02c10_sensor_slow_fps(int fps);

/**
 * @brief The exposure and gain auto exposure set last, and one line's time.
 *
 * @param[out] lines     Exposure, in lines.
 * @param[out] gain_x16  Total gain x 16.
 * @param[out] tline_ns  One line's time in nanoseconds (0 until the first exposure is written).
 */
void ov02c10_sensor_exposure(uint32_t *lines, uint32_t *gain_x16, uint32_t *tline_ns);

#ifdef __cplusplus
}
#endif
