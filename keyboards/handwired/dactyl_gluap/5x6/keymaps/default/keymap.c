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
                    MT(MOD_LALT,KC_DEL) , MT(MOD_LCTL,KC_ESC),                                                          DE_PLUS, DE_BSLS,
                                        MT(MOD_LALT,KC_DEL),MO(_RAISE),                      KC_LGUI,  MT(MOD_RALT,KC_ENTER),
                                        MT(MOD_LSFT,KC_BSPC), MO(_LOWER),                        MT(MOD_LCTL,KC_TAB), KC_SPC
  ),
  [_LOWER] = LAYOUT_5x6(

     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
     _______,_______,_______,_______,_______,DE_LBRC,                        DE_RBRC, _______ ,_______ ,_______ ,_______,KC_PLUS,
     _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,DE_LPRN,                        DE_RPRN, KC_HOME , KC_PGUP ,KC_PGDN ,KC_END,DE_PIPE,
     _______,_______,_______,_______,_______,DE_LCBR,                        DE_RCBR, _______ ,_______ ,_______ ,KC_EQL ,DE_UNDS,
                                             _______,KC_PSCR,            _______, KC_P0,

                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______
  ),

  [_RAISE] = LAYOUT_5x6(
       KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,                        KC_F7  , KC_F8 , KC_F9 , KC_F10 ,KC_F11 ,KC_F12,
       _______,_______,_______,_______,_______,DE_LBRC,                        DE_RBRC,_______,_______,KC_INS ,KC_SLCK,KC_MUTE,
       _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,DE_LPRN,                        DE_RPRN,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_VOLU,
       _______,_______,_______,_______,_______,DE_LCBR,                        DE_RCBR,_______,_______,_______,_______,KC_VOLD,
                                               _______,_______,            KC_EQL ,_______,

                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______
  ),
};
int timer = 0;
int timer2 =0;
char wpm_text[5]="asdf";
int x = 64;
int currwpm = 0;

//USER CONFIG PARAMS
float max_wpm = 140.0f; //WPM value at the top of the graph window
int graph_refresh_interval = 160; //in milliseconds
int graph_area_fill_interval = 64;

#ifdef OLED_ENABLE

bool oled_task_user(void) {

	//get current WPM value
	currwpm = get_current_wpm();
  itoa(currwpm ,wpm_text,10);

	//check if it's been long enough before refreshing graph
	if(timer_elapsed(timer) > graph_refresh_interval){

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

	}
	//format current WPM value into a printable string


	//formatting for triple digit WPM vs double digits, then print WPM readout
	if(currwpm>100){
		oled_set_cursor(14, 7);
		oled_write("WPM: ", false);
		oled_set_cursor(18, 7);
		oled_write(wpm_text, false);
	} else if (currwpm >= 10){
		oled_set_cursor(15, 7);
		oled_write("WPM: ", false);
		oled_set_cursor(19, 7);
		oled_write(wpm_text, false);
	} else if (currwpm>0) {
		oled_set_cursor(16, 7);
		oled_write("WPM: ", false);
    oled_set_cursor(20, 7);
		oled_write(wpm_text, false);
	}


oled_set_cursor(0, 0);
      // Host Keyboard Layer Status


    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("        "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("PgupDown"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Arrows"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
oled_set_cursor(1, 1);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    if((led_state.num_lock  || led_state.caps_lock || led_state.scroll_lock) ){
    oled_write_P(led_state.num_lock ? PSTR(" NUM") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR(" CAP") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR(" SCR") : PSTR("    "), false);
    } else if (!(led_state.num_lock  || led_state.caps_lock || led_state.scroll_lock) && (timer_elapsed(timer2) > graph_refresh_interval*128)) {
      oled_set_cursor(0, 1);

      oled_write_P(PSTR(" gluap ") ,false);
      timer2 =timer_read();
    }
  return false;
}

#endif
