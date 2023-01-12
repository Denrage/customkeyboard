// Copyright 2023 Denrage (@Denrage)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define RGB_DI_PIN B3
#define RGBLED_NUM 3
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_HUE_STEP 50
#define RGBLIGHT_SAT_STEP 50
#define RGBLIGHT_VAL_STEP 50
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD