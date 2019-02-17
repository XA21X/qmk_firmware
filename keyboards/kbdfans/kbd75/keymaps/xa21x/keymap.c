#include QMK_KEYBOARD_H

#define _______ KC_TRNS

#define LDEF 0
#define LFUN 2
#define LMAC 1
#define LKBD 3


typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;


enum user_keycodes {
  EPRM = SAFE_RANGE,
  RGB_LYR
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [LDEF] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  MO(LFUN), KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGDN,
    KC_LSPO,  MO(LFUN), KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC,            KC_UP,    KC_END,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   MO(LKBD), KC_SPC,                       KC_RALT,  MO(LFUN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [LFUN] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,    _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  RGB_LYR,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  TG(LMAC), _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),

  [LMAC] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    MT(MOD_LGUI, KC_ESC), _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    KC_LCTL,  KC_LALT,  KC_LCMD,                      _______,  _______,  _______,                      KC_RCMD,  KC_RALT,  KC_RCTL,  _______,  _______,  _______
  ),

  [LKBD] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_UP  ,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),
};

void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    layer_state_set(layer_state);
    rgblight_enable_noeeprom();
  }
}


rgblight_config_t old_config;


uint32_t layer_state_set_user(uint32_t state) {
  if (user_config.rgb_layer_change) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    switch (biton32(state)) {
    case LFUN:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case LKBD:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        old_config.raw = eeconfig_read_rgblight();
        rgblight_mode_noeeprom(old_config.mode);
        break;
    }
  } else {
    old_config.raw = eeconfig_read_rgblight();
    rgblight_mode_noeeprom(old_config.mode);
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EPRM:
        if (record->event.pressed) {
            eeconfig_init(); // resets the EEPROM to default
        }
        return false; break;
    case RGB_LYR:  // This allows me to use underglow as layer indication, or as normal
        if (record->event.pressed) {
            user_config.rgb_layer_change ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
            if (user_config.rgb_layer_change) { // if layer state indication is enabled,
                layer_state_set(layer_state);   // then immediately update the layer color
            }
        }
        return false; break;
  }
  return true;
}
