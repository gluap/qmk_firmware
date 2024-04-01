/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include <stdlib.h>
#include <config.h>


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
      KC_1   , KC_2  , KC_3  , KC_4  , KC_5  ,  KC_6  ,                         KC_7  , KC_8  , KC_9  , KC_0  , DE_SS,   DE_ACUT,
      KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                          KC_Y  , KC_U  , KC_I  , KC_O  , KC_P   , DE_UDIA,
      DE_CIRC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                          KC_H  , KC_J  , KC_K  , KC_L  ,DE_ODIA , DE_ADIA,
      DE_LABK, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                          KC_N  , KC_M  ,DE_COMM,KC_DOT ,DE_MINS , DE_HASH,
                    MT(MOD_LALT,KC_DEL) , MT(MOD_LCTL,KC_ESC),                                 DE_PLUS, DE_BSLS,
                                        MT(MOD_LALT,KC_DEL),MO(_RAISE),                      KC_LGUI,  MT(MOD_RALT,KC_ENTER),
                                        MT(MOD_LSFT,KC_BSPC), MO(_LOWER),                        MT(MOD_LCTL,KC_TAB), KC_SPC
  ),
  [_LOWER] = LAYOUT_5x6(

     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
     _______,_______,_______,_______,_______,DE_LBRC,                        DE_RBRC, _______ ,_______ ,_______ ,_______,KC_PLUS,
     _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,DE_LPRN,                        DE_RPRN, KC_HOME , KC_PGUP ,KC_PGDN ,KC_END,DE_PIPE,
     _______,_______,_______,_______,_______,DE_LCBR,                        DE_RCBR, _______ ,_______ ,_______ ,KC_EQL ,DE_UNDS,
                    _______,KC_PSCR,                                                            _______, KC_P0,

                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______
  ),

  [_RAISE] = LAYOUT_5x6(
       KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,                        KC_F7  , KC_F8 , KC_F9 , KC_F10 ,KC_F11 ,KC_F12,
       KC_CAPS,_______,_______,_______,_______,DE_LBRC,                       DE_RBRC,_______,_______,KC_INS ,_______,KC_MUTE,
       KC_NUM ,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,DE_LPRN,                       DE_RPRN,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_VOLU,
       KC_SCRL,_______,_______,_______,_______,DE_LCBR,                       DE_RCBR,_______,_______,_______,_______,KC_VOLD,
                       _______,_______,                                                        KC_EQL ,_______,

                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______
  ),
};
int timer = 0;
int timer2 = 0;
int timer_invert = 0;
int last_typing = 0;
bool logo= false;
char wpm_text[5]="asdf";
int x = 64;
int currwpm = 0;

//USER CONFIG PARAMS
float max_wpm = 140.0f; //WPM value at the top of the graph window
int graph_refresh_interval = 160; //in milliseconds
int graph_area_fill_interval = 64;

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224, 48, 24, 12,  4,  4,  6,  6,  6,  6,  4, 12, 12, 12, 12,  4,  6,  6,  6,  6,  6,  4,  4,  8, 24, 48, 32,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192, 64, 64,192, 64,  0,240,  0,  0,192,  0,  0,  0,192,  0,  0, 64, 64, 64,192,  0,  0,192, 64, 64, 64,128,  0,  0,  0,  0,  0,128, 64, 64,192,  0,  0,  0,  0,  0, 64,128,  0,128, 64,128,  0,128, 64,  0, 64, 64, 64,192,  0,  0,192, 64, 64,  0,192, 64, 64, 64,128,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 28,  6,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 14, 56,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 79, 74, 74,105, 48,  0, 15,  0,  0, 15,  8,  8,  8, 15,  0,  0, 15,  9,  9, 15,  0,  0,127,  8,  8,  8,  7,  0,  0,  0,  0,  0,  7,  9,  9,  9,  0,  0,  2,  2,  0,  0,  7, 12,  3,  0,  7,  8,  7,  0,  0, 15,  9,  9, 15,  0,  0, 15,  0,  0,  0,127,  8,  8,  8,  7,
        0,  0,192, 96, 16, 16, 24,  8,  4,  4,  6,130,130,194,243,241,243,242,242,242,243,241,241,241,241,241,241,242,242,243,241,241,241,241,241,241,241,241,241,241,241,241,243,242,242,246,228,228,228,197,199,140,  8,  8,  8, 16, 16, 48, 32, 96, 64,192,  0,  0,  0,  0,  0,  0,192,  0,  0,  0,192,  0,  0,192, 64, 64,  0,  0,208,  0,  0,192, 64, 64, 64,128,  0,  0,192, 64, 64,192, 64,  0,  0,  0,  0,128, 64, 64, 64,192,  0,  0,192, 64, 64,192,128, 64, 64,192,  0,  0,240,  0,128, 64,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  7, 28, 16, 48, 32, 32,160,248,252,255,255,255,255,255,255,255,255,127,127,127,255,255,255,255,255,255,255,255,255,127,127, 63,191,191, 63,127,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,240,224, 48, 16, 16, 24, 12,  7,  3,  0,  0,  0,  0,  0, 15,  8,  8,  8, 15,  0,  0,  9,  9, 10,  4,  0, 15,  0,  0, 15,  0,  0,  0, 15,  0, 48, 79, 74, 74,105, 48,  0,  0,  0,  0,  7,  8,  8,  8,127,  0,  0, 15,  0,  0,  0, 15,  0,  0, 15,  0,  0, 15,  1,  2, 12,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,248,255,255,255,255,255,255,255,255,255,  0,254,255,255,255,240,241,243, 15,255,255,255,  3,120,254,255,255,255,255,255,248,248,248,  1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,  0,  0,  0,  0,  0,192, 64, 64,192, 64,  0,208,  0, 64,224, 64, 64,  0,240, 64, 64, 64,128,  0,  0,192,  0,  0,  0,192,  0,  0,240, 64, 64, 64,128,  0,  0,  0,  0,  0,128, 64, 64, 64,  0,128, 64, 64, 64,128,  0,  0,192, 64, 64,192,128, 64, 64,192,  0,  0,  0,224, 16,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  3, 31,255,255,255,255,255,255,255,255,254,190, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  1,  0,  0,  0,  0, 48, 79, 74, 74,105, 48,  0, 15,  0,  0, 15,  8,  8,  0, 15,  0,  0,  0, 15,  0,  0, 15,  8,  8,  8, 15,  0,  0, 15,  8,  8,  8,  7,  0,  0,  8,  0,  0,  7,  8,  8,  8,  0,  7,  8,  8,  8,  7,  0,  0, 15,  0,  0,  0, 15,  0,  0, 15,  0,  8,  7,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 15, 63,127,255,255,255,255,255,254,248,240,224,192,128,  0,  0,  0,128,192,224,224,240,240,240,240,240, 96,  0,128,192,248,255,255,255,255,255,255,255,255,255,127, 63, 31,  7,  3,  0,  0,  0,  0,  0,  0,  0,192, 64, 64,192, 64,  0,240,  0,  0,192,  0,  0,  0,192,  0,  0, 64, 64, 64,192,  0,  0,192, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63, 63,127,127,127,127,127,126,126,126,126,254,254,254,254,254,126,126,127,127,127,127,127, 63, 63, 15,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 79, 74, 74,105, 48,  0, 15,  0,  0, 15,  8,  8,  8, 15,  0,  0, 15,  9,  9, 15,  0,  0,127,  8,  8,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
     oled_scroll_set_speed(4);

// Begin scrolling the entire display right
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
 oled_scroll_left();
 oled_set_brightness(8);
}

void disable_logo(void) {
    if (logo) {
        logo = false;
        oled_clear();
        oled_scroll_off();
        oled_set_brightness(255);
    }
}

bool oled_task_user(void) {

	//get current WPM value
	currwpm = get_current_wpm();
    itoa(currwpm ,wpm_text, 10);


	//check if it's been long enough before refreshing graph
	if((timer_elapsed(timer) > graph_refresh_interval) && (timer_elapsed(last_typing) < 128*graph_refresh_interval)){

		// main calculation to plot graph line
		x = 64- ((currwpm / max_wpm) * 48);

		//first draw actual value line
		oled_write_pixel(1, x, true);

		//then fill in area below the value line
		for(int i = 60; i > x; i-=2){
			if(i % graph_area_fill_interval == 0){
				oled_write_pixel(1, i, true);
			}
		}

		//then move the entire graph one pixel to the right
		oled_pan(false);

		//refresh the timer for the next iteration
		timer = timer_read();

	} else if  (timer_elapsed(last_typing) > 128*graph_refresh_interval) {
        render_logo();
        logo = true;
    }


	//format current WPM value into a printable string


	//formatting for triple digit WPM vs double digits, then print WPM readout
	if(currwpm>100){
		oled_set_cursor(13, 7);
		oled_write(" WPM: ", false);
		oled_set_cursor(18, 7);
		oled_write(wpm_text, false);
		last_typing = timer_read();
		disable_logo();
	} else if (currwpm >= 10){
		oled_set_cursor(14, 7);
		oled_write(" WPM: ", false);
		oled_set_cursor(19, 7);
		oled_write(wpm_text, false);
		last_typing = timer_read();
		disable_logo();

	} else if (currwpm>0) {
		oled_set_cursor(15, 7);
		oled_write(" WPM: ", false);
        oled_set_cursor(20, 7);
		oled_write(wpm_text, false);
		last_typing = timer_read();
		disable_logo();
	}


    oled_set_cursor(0, 0);
      // Host Keyboard Layer Status

    if (logo) {
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("        "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Arrows"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("PGUPDOWN"), false);
            break;
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    if((led_state.num_lock  || led_state.caps_lock || led_state.scroll_lock) ){
        oled_set_cursor(1, 1);
    oled_write_P(led_state.num_lock ? PSTR(" NUM") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR(" CAP") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR(" SCR") : PSTR("    "), false);
    }
  return false;
}

#endif
