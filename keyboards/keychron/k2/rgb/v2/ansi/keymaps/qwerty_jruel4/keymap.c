/*
Copyright 2022 Dimitris Mantzouranis <d3xter93@gmail.com>
Copyright 2022 Pablo Ramirez
Copyright 2023 Santanu Paik (https://github.com/ITNerd69)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    BASE              = 0,
    FN                = 1,
    NUM               = 2,
    NAV               = 3,
    WIN               = 4,
};
#define KC_TASK LGUI(KC_TAB)        // Task viewer
#define KC_FLXP LGUI(KC_E)          // Windows file explorer

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
#define KC_MSCR LSFT(LGUI(KC_3))    // Mac screenshot
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool

// Save space on the keymap
#define TAP_TAB LT(NAV, KC_TAB)

// Simplify
#define PRESS(...) { if (record->event.pressed) {                         \
    uint16_t codes[] = { __VA_ARGS__ };                                   \
    for (size_t i = 0; i < sizeof(codes)/sizeof(codes[0]); i++) {         \
        register_code(codes[i]);                                          \
    }                                                                     \
    for (size_t i = sizeof(codes)/sizeof(codes[0]) - 1; i >= 0; i--) {    \
        unregister_code(codes[i]);                                        \
    }                                                                     \
} return false;  }

#define UNDO LGUI(KC_Z)
#define REDO LSFT(LGUI(KC_Z))
#define CUT LGUI(KC_X)
#define COPY LGUI(KC_C)
#define PASTE LGUI(KC_V)

enum custom_keycodes {
//    UNDO = SAFE_RANGE, // Starts after the reserved range of keycodes
//    CUT,
//    COPY,
//    PASTE,
//    REDO,
    HALF_PGUP = SAFE_RANGE,
    HALF_PGDN,
    PREV_WORD,
    NEXT_WORD,
    START_LN,
    END_LN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
    *****************************************************************************************************************
    * ESC  * F1   * F2   * F3   * F4   * F5   * F6   * F7   * F8   * F9   * F10  * F11  * F12  * PSCR * DEL  * RMOD *
    *****************************************************************************************************************
    * ~    * 1    * 2    * 3    * 4    * 5    * 6    * 7    * 8    * 9    * 0    * -    * =    * BSPC        * PGUP *
    *****************************************************************************************************************
    * TAB     * Q    * W    * E    * R    * T    * Y    * U    * I    * O    * P    * [    * ]    * \        * PGDN *
    *****************************************************************************************************************
    * CAPS      * A    * S    * D    * F    * G    * H    * J    * K    * L    * ;    * '    * ENT           * HOME *
    *****************************************************************************************************************
    * LSFT         * Z    * X    * C    * V    * B    * N    * M    * ,    * .    * /    * RSFT       * UP   * END  *
    *****************************************************************************************************************
    * LCTL  * LALT  * LGUI  * SPC                                         * LGUI * FN   * RCTL * LEFT * DOWN * RGHT *
    *****************************************************************************************************************
  */
  [BASE] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_MSCR,    KC_DEL,     RM_NEXT  ,
      KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,                KC_PGUP  ,
      TAP_TAB,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,                KC_PGDN  ,
      MO(NUM),    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,                 KC_HOME  ,
      KC_LSFT,                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                KC_RSFT,    KC_UP,      KC_END   ,
      KC_LCTL,    KC_LALT,    KC_LGUI,                                        KC_SPC,                                         KC_RGUI,    MO(FN),     KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
  ),

  /*
    *****************************************************************************************************************
    *RESET * BRID * BRIU * TASK * FLXP * RVAD * RVAI * MPRV * MPLY * MNXT * MUTE * VOLD * VOLU *      *  INS * RTOG *
    *****************************************************************************************************************
    *      *      *      *      *      *      *      *      *      *      *      *      *      *             *      *
    *****************************************************************************************************************
    *         *      *      *      *      *      *      *      *      *      *      *      *      *          *      *
    *****************************************************************************************************************
    *           *      *      *      *      *      *      *      *      *      *      *      *               *      *
    *****************************************************************************************************************
    *              *      *      *      *      *      *      *      *      *      *      *            * RSAI *      *
    *****************************************************************************************************************
    *       *       *       *                                             *      *      *      * RHUD * RSAD * RHUI *
    *****************************************************************************************************************
  */
  [FN] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      QK_BOOT,    KC_BRID,    KC_BRIU,    KC_MSSN,    KC_FIND,    RM_VALD,    RM_VALU,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_MSNP,    KC_INS,     RM_TOGG  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    RM_SATU,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    RM_HUED,    RM_SATD,    RM_HUEU
  ),





/*
 *
 * TODO:
 * 
 * Add navigation layer when space is pressed 
 *  - CTHN should be arrow keys when space is held
 *  - G/R is previous/next word
 *  - F/L should be 1/2 PgUp/PgDown
 *  - -/D should be start/end of line (need to remap both Vim and Alacritty commands for this)
 *  
 * We still have mod+Layer as well. TBD on that.
 * 
 * Other useful ones:
 * split pane vertical/horizontal
 * navigate panes
 * new window
 * go to window
 * 

Also go to specific apps (Slack, Firefox, etc...)

Number pad as well

QJK for cut / copy / paste (remapped to ctrl x/c/v)

I should also utilize combos
- PREVWORD+UP can be half pgup, NEXTWD+UP can be pageup
- LFT+DWN can be half pgdwn, RIGHT+DWN can be page down
- RIGHT+lh


 */


  /*
    =========  ========  =======   =======   ======   NAVIGATION   ======   =======   ========  ========  ===========
    *****************************************************************************************************************
    * ESC  * F1   * F2   * F3   * F4   * F5   * F6   * F7   * F8   * F9   * F10  * F11  * F12  * PSCR * DEL  * RMOD *
    *****************************************************************************************************************
    * ~    * 1    * 2    * 3    * 4    * 5    * 6    * 7    * 8    * 9    * 0    * -    * =    * BSPC        * PGUP *
    *****************************************************************************************************************
    * TAB     * Q    * W    * E    * R    * T    *HFPGUP * PRWRD * UP *NXTWD *HFPGDN * [   * ]    * \        * PGDN *
    *****************************************************************************************************************
    * CAPS      * A    * S    * D    * F    * G    *STRTLN * LFT  * DN   * RGHT *ENDLN * '    * ENT          * HOME *
    *****************************************************************************************************************
    * LSFT         * Z    * X    * C    * V    * B    * N    * M    * ,    * .    * /    * RSFT       * UP   * END  *
    *****************************************************************************************************************
    * LCTL  * LALT  * LGUI  * SPC                                         * LGUI * FN   * RCTL * LEFT * DOWN * RGHT *
    *****************************************************************************************************************
  */
  [NAV] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    HALF_PGUP,  PREV_WORD,  KC_UP,      NEXT_WORD,  HALF_PGDN,  _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    START_LN,   KC_LEFT,    KC_DOWN,    KC_RGHT,    END_LN,     _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    _______,    _______,    _______
  ),







  /*
    =========  ========  =======   =======   ======   Number Pad   ======   =======   ========  ========  ===========
    *****************************************************************************************************************
    * ESC  * F1   * F2   * F3   * F4   * F5   * F6   * F7   * F8   * F9   * F10  * F11  * F12  * PSCR * DEL  * RMOD *
    *****************************************************************************************************************
    * ~    *      *      *      *      *      *      * 7    * 8    * 9    * +    *      *      * BSPC        * PGUP *
    *****************************************************************************************************************
    * TAB     *      * UNDO * REDO *      *      *      * 4    * 5    * 6    * -    *     *     * \          * PGDN *
    *****************************************************************************************************************
    * CAPS      *      * CUT  * COPY* PASTE*      *       * 1    * 2    * 3    * ENT  *       * ENT         * HOME *
    *****************************************************************************************************************
    * LSFT         *      *      *      *      *      *      * 0    * .    * /    *      * RSFT       * UP   * END  *
    *****************************************************************************************************************
    * LCTL  * LALT  * LGUI  * SPC                                         * LGUI * FN   * RCTL * LEFT * DOWN * RGHT *
    *****************************************************************************************************************
  */
  [NUM] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_7,       KC_8,       KC_9,       KC_PLUS,    _______,    _______,    _______,                _______  ,
      _______,    _______,    UNDO,       REDO,       _______,    _______,    _______,    KC_4,       KC_5,       KC_6,       _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    CUT,        COPY,       PASTE,      _______,    _______,    KC_1,       KC_2,       KC_3,       KC_ENT,     _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    KC_0,       KC_DOT,     KC_SLSH,    _______,                _______,    _______,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    _______,    _______,    _______
  ),


  [WIN] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,     _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    _______,    _______,    _______
  ),


};


// UNDO = SAFE_RANGE, // Starts after the reserved range of keycodes
// CUT,
// COPY,
// PASTE,
// REDO,
// HALF_PGUP,
// HALF_PGDN,
// PREV_WORD,
// NEXT_WORD,
// START_LN,
// END_LN

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
        // case UNDO: PRESS(KC_LGUI, KC_Z);
        // case CUT: PRESS(KC_LGUI, KC_X);
        // case COPY: PRESS(KC_LGUI, KC_C);
        // case PASTE: PRESS(KC_LGUI, KC_V);
        // case REDO: PRESS(KC_LGUI, KC_Y);
        case RM_NEXT:
            {
                if (record->event.pressed && ((get_mods() & (MOD_MASK_CTRL | MOD_MASK_SHIFT)) != 0)) {
                  reset_keyboard();
                }
            }
        case KC_BSPC:
            {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
            }

    }
    return true;
};

bool dip_switch_update_user(uint8_t index, bool active) {
  switch(index) {
    case 0: // OS switch
      if (active) { // Mac/iOS mode
        layer_off(WIN);
      }
      else { // Windows/Android mode
        layer_on(WIN);
      }
      break;
    case 1: // Connection switch
      // Probably it's not possible to do anything sensible here as switching from Cable to BT requires turning off the board. (BT / OFF / Cable)
      if (active) { // BT mode
        // do stuff
      }
      else { //Cable mode
        // do stuff
      }
      break;
  }
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable = true;
  // debug_matrix = true;
  // debug_keyboard = true;
  // debug_mouse = true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        // Current highest layer - returns enum value
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    if (layer == FN) {
                        // RGB_BLUE is a hex triplet macro expanding to 0x00, 0x00, 0xFF
                        rgb_matrix_set_color(index, RGB_BLUE);
                    } else if (layer == NAV) {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    } else if (layer == NUM) {
                        rgb_matrix_set_color(index, RGB_PURPLE);
                    } else {
                        rgb_matrix_set_color(index, RGB_RED);
                    }
                }
            }
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(15, 255, 255, 255); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(15, 0, 0, 0);
    }

    return false;
}



// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LT(1, KC_TAB): // Specific key (e.g., Layer-Tap Tab key)
//             return 250;    // Custom tapping term for this key
//         default:
//             return TAPPING_TERM; // Default tapping term for others
//     }
// }