#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│ │Num│ / │ * │ - │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │ │Del│End│PgD│ │ 7 │ 8 │ 9 │   │ 
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent│ └───┴───┴───┘ ├───┼───┼───┤ + │
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │               │ 4 │ 5 │ 6 │   │
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
     * │Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │     │ 1 │ 2 │ 3 │   │
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤Ent│
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │   │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
     */
    [0] = LAYOUT_fullsize_iso(
        KC_NUM, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
        KC_KP_7, KC_KP_8, KC_KP_9,
        KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,
        KC_KP_1, KC_KP_2, KC_KP_3,
        KC_KP_0,  KC_KP_DOT,  KC_KP_ENTER
    )
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
    { 1, 2, 3, 4 },
    { 7, 6, 5 },
    { 8, 9, 10, 11 },
    { 14, 13, 12 },
    { 15, 16, 17 },
  }, {
    // LED Index to Physical Position
    { 0,  0 },
    { 0,  13 }, {75,13}, {150,13}, {224,13},
    {150, 26}, {75,26},  { 0,  26 },
    { 0,  39 }, {75,39}, {150,39}, {224,33},
    {150,52}, {75,52}, { 0,  52 },
    { 38,  64 }, {150,64}, {224,58},
  }, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
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