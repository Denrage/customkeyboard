#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

#define SETRGBCOMMAND 0

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
        RGB_TOG    
    )
};

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 255;

extern void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds);

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

void matrix_scan_user(void) 
{
    rgblight_mode(1);
    //rgblight_setrgb_range(r, g, b, 0, 3);
    for (size_t i = 0; i < 2; i++)
    {
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
    }
    
    rgblight_call_driver(led, 3);
}

void raw_hid_receive( uint8_t *data, uint8_t length ) 
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
            r = message[0];
            g = message[1];
            b = message[2];
            xprintf("SET COLOR: %d, %d, %d\n", r, g, b);
        }
    }
}