/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include <keymap_german.h>


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
      KC_1   , KC_2  , KC_3  , KC_4  , KC_5  ,  KC_6  ,                         KC_7  , KC_8  , KC_9  , KC_0  , DE_SS,   DE_GRV ,
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
