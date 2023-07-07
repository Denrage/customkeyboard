// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LWIN, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RWIN, KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    )
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
    { 1, 2, 3, 4, 5, 6, 7, 8 ,9 ,10, 11, 12, 13, 14, 15, 16 },
    { 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17 },
    { 34, 35, 36, 37, 38, 39,40,41,42,43,44,45,46,47,48,49,50 },
    { 63, 62, 61,60,59,58,57,56,55,54,53,52,51 },
    { 64, 65, 66,67,68,69,70,71,72,73,74,75,76 },
    { 89,88,87,85,83,82,81,80,79,78,77 },
  }, {
    // LED Index to Physical Position
    { 0,  0 },{ 28,  0 },{ 42,  0 },{ 56,  0 },{ 70,  0 },{ 84,  0 },{ 98,  0 },{ 112,  0 },{ 126,  0 },{ 140,  0 },{ 154,  0 },{ 168,  0 },{ 182,  0 },{ 196,  0 },{ 210,  0 }, { 224,  0 },
    { 0,  12 }, {14,12},{ 28, 12 },{ 42, 12 },{ 56, 12 },{ 70, 12 },{ 84, 12 },{ 98, 12 },{ 112, 12 },{ 126, 12 },{ 140, 12 },{ 154, 12 },{ 168, 12 },{ 182, 12 },{ 196, 12 },{ 210, 12 }, { 224, 12 },
    { 0,  25 }, {14,25},{ 28, 25 },{ 42, 25 },{ 56, 25 },{ 70, 25 },{ 84, 25 },{ 98, 25 },{ 112, 25 },{ 126, 25 },{ 140, 25 },{ 154, 25 },{ 168, 25 },{ 182, 25 },{ 196, 25 },{ 210, 25 }, { 224, 25 },
    { 0,  38  }, {14,38},{ 28, 38 },{ 42, 38 },{ 56, 38 },{ 70, 38 },{ 84, 38 },{ 98, 38 },{ 112, 38 },{ 126, 38 },{ 140, 38 },{ 154, 38 },{ 182, 38 },
    { 0,  51 }, { 28, 51 },{ 42, 51 },{ 56, 51 },{ 70, 51 },{ 84, 51 },{ 98, 51 },{ 112, 51 },{ 126, 51 },{ 140, 51 },{ 154, 51 },{ 182, 51 },{ 210, 51 },
    { 0,  64 }, {14,64},{ 28, 64 },{ 56, 64 },{ 84, 64 },{ 112, 64 },{ 140, 64 },{ 154, 64 },{ 168, 64 },{ 182, 64 },{ 196, 64 },{ 210, 64 }, { 224, 64 },
  }, {
    // LED Index to Flag
    4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
} };

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

void matrix_scan_user(void) 
{

}

void raw_hid_receive(uint8_t *data, uint8_t length)
{
    if(length > 0)
    {
        xprintf("Received HID Data (%d)\n", length);
        raw_hid_send(data, length);
        uint32_t messageLength = (uint32_t)data[0] << 24u | (uint32_t)data[1] << 16u | (uint32_t)data[2] << 8u | (uint32_t)data[3];
        if(messageLength > 0)
        {
            uint8_t* messageCommand = data + 4; // 4bytes = int32
            uint8_t* message = messageCommand + 1; // 1 byte message command
            switch (messageCommand[0])
            {
              case 0:
                rgb_matrix_sethsv(message[0], message[1], message[2]);
                break;
              case 1:
                rgb_matrix_mode(message[0]);
                break;
              
              default:
                break;
            }
            // xprintf("SET COLOR: %d, %d, %d, %d\n", message[0], message[1], message[2], RGB_MATRIX_LED_COUNT);
        }
    }
}