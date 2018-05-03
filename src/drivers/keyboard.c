#include "../include/keyboard.h"
#include "../include/inb_outb.h"

key_buf kb;

void key_init(void){
  change_trate_delay(TYPEMATICDELEY_SET11);
  if (enable_keyboard() == 0xFA) {
    terminal_writestring("Keyboard enable OK\n");
  }
  if (!ps2_kerboard_init()) {
    terminal_writestring("PS/2 Keyboard init OK\n");
  }  
}


uint8_t ps2_kerboard_init(void){
  uint8_t scodeset = getscodeset();  
  if (scodeset == 0x43) {
    terminal_writestring("Current Scan code set 1\nCorrection to Scan code set2\n");
    change_codeset(SCAN_CODE_SET2);
  } else if (scodeset == 0x41) {
    terminal_writestring("Scan code set 2\n");
  } else if (scodeset == 0x3f) {
    terminal_writestring("Current Scan code set 3\nCorrection to Scan code set2\n");
    change_codeset(SCAN_CODE_SET2);
  } else {
    terminal_writestring("Unknown scan code set\nPS/2 Emulation?\n");
    return 1;
  }
  return 0;
}


void keyboard_input_int(uint8_t scan_code){
  if (scan_code == 0xE0) {
    if (!ext_input) {
      ext_input = true;
    } else {
      ext_input = false;
    }
  }
  if (scan_code <= 0x80) {
    if (kb.len < 128) {
      if (scan_code == L_SHIFT || scan_code == R_SHIFT) {
	ks.shift_enable = true;
      } else if (scan_code == CAPS_LOCK && !ks.caps_lock) {
	ks.caps_lock = true;
	ks.led_stat += SET_CAPSLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else if (scan_code == CAPS_LOCK && ks.caps_lock) {
	ks.caps_lock = false;
	ks.led_stat -= SET_CAPSLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else if (scan_code == NUM_LOCK && !ks.num_lock) {
	ks.num_lock = true;
	ks.led_stat += SET_NUMLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else if (scan_code == NUM_LOCK && ks.num_lock) {
	ks.num_lock = false;
	ks.led_stat -= SET_NUMLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else if (scan_code == SCROLL_LOCK && !ks.scr_lock) {
	ks.scr_lock = true;
	ks.led_stat += SET_SCROLLLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else if (scan_code == SCROLL_LOCK && ks.scr_lock) {
	ks.scr_lock = false;
	ks.led_stat -= SET_SCROLLLOCK_LED;
	switch_kb_led(ks.led_stat);
      } else {
	input_bufdata(scan_code);
	++kb.len;
	if (kb.write == 128) { kb.write = 0; }
      }
    }
  } else {
    scan_code -= 0x80;
    if (scan_code == L_SHIFT || scan_code == R_SHIFT) {
      ks.shift_enable = false;
    }
  }
}
     

void switch_kb_led(uint8_t set_led){
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, SWITCH_LED);
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, set_led);
}


uint8_t enable_keyboard(void){
  outb(PORTMAP_KEYBOARD1, ENABLE_KEYBOARD);
  return getscode();
}


uint8_t getscodeset(void){
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, SET_SCANCODESET);
  if (getscode() == 0xFA) {
    while (inb(PORTMAP_KEYBOARD2) & 0x02);
    outb(PORTMAP_KEYBOARD1, 0x00);
    return getscode();
  } else {
    return 0x00;
  }
}


uint8_t getscode(void){
  uint8_t c = 0;
  do {
    if (inb(PORTMAP_KEYBOARD1) != c) {
      c = inb(PORTMAP_KEYBOARD1);
      if (c > 0) return c;
    }
  } while (1);
}


uint8_t getchar(void){
  return getscode();
}


void change_codeset(uint8_t set){
  outb(PORTMAP_KEYBOARD1, SET_SCANCODESET);
  outb(PORTMAP_KEYBOARD1, set);
}


void change_trate_delay(uint8_t set){
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, SET_TYPEMATIC_RATE);
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, set);
}


void input_bufdata(uint8_t scan_code) {
  const keymap *key = &key_code;
  uint8_t numpad_data = 0;
  
  if (ks.num_lock) {
    numpad_data = key -> numlock[scan_code];
    ext_input = false;
  }
  
  if (!numpad_data) {
    if (ext_input && scan_code == 0x35) {
      kb.pdata[kb.write++] = '\0';
    } else if (ks.shift_enable && !ks.caps_lock) {
      kb.pdata[kb.write++] = key -> shift[scan_code];
    } else if (!ks.shift_enable && ks.caps_lock) {
      if ((numpad_data = key -> base[scan_code]) >= 'a' && numpad_data <= 'z'){
	kb.pdata[kb.write++] = key -> shift[scan_code];
      }else{
	kb.pdata[kb.write++] = key -> base[scan_code];
      }
    }else if (ks.shift_enable && ks.caps_lock){
      if ((numpad_data = key -> base[scan_code]) >= 'a' && numpad_data <= 'z'){
	kb.pdata[kb.write++] = key -> base[scan_code];
      }else{
	kb.pdata[kb.write++] = key -> shift[scan_code];
      }
    } else {
      kb.pdata[kb.write++] = key -> base[scan_code];
    }
  } else {
    kb.pdata[kb.write++] = numpad_data;
  }
}
