#include "include/keyboard.h"
#include "include/inb_outb.h"

key_buf kb;

void key_init(void){
  change_trate_delay(TYPEMATICDELEY_SET11);
  if (enable_keyboard() == 0xFA) {
    terminal_writestring("Keyboard enable OK\n");
  }
  if (!ps2_kerboard_init()) {
    terminal_writestring("PS/2 Keyboard init OK\n");
  }
  
  //追加
  ks.shift_enable = false;
  ks.caps_lock = false;
}


uint8_t ps2_kerboard_init(void){
  //change_codeset(SCAN_CODE_SET2);
  uint8_t scodeset = getscodeset();  
  if (scodeset == 0x43) {
    terminal_writestring("Scan code set 1\n");
  } else if (scodeset == 0x41) {
    terminal_writestring("Scan code set 2\n");
  } else if (scodeset == 0x3f) {
    terminal_writestring("Scan code set 3\n");
  } else {
    terminal_writestring("Unknown scan code set\n");
    return 1;
  }
  return 0;

}


void keyboard_input_int(uint8_t scan_code){
  uint8_t us_keytable_set2[0x80] = {
    '0', '0', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '0',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', '0', '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', '0', '0', '0', ' ', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0'};

  //追加
  uint8_t us_keytable_set2S[0x80] = {
    '0', '0', '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', '0',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', '0', '|', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?', '0', '0', '0', ' ', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0'};

  if (scan_code <= 0x80) {
    if (kb.len < 128) {
      if (scan_code == L_SHIFT || scan_code == R_SHIFT) {
	ks.shift_enable = true;
	
      } else if (scan_code == CAPS_LOCK && !ks.caps_lock) {
	ks.caps_lock = true;
	
      } else if (scan_code == CAPS_LOCK && ks.caps_lock) {
	ks.caps_lock = false;
	
      } else {
	if (ks.shift_enable && !ks.caps_lock) {
	  kb.pdata[kb.write++] = us_keytable_set2S[scan_code];
	  
	} else if (!ks.shift_enable && ks.caps_lock) {
	  kb.pdata[kb.write++] = us_keytable_set2S[scan_code];
	  
	} else {
	  kb.pdata[kb.write++] = us_keytable_set2[scan_code];
	  
	}
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


uint8_t enable_keyboard(){
  outb(PORTMAP_KEYBOARD1, 0xF4);
  return getscode();
}


uint8_t getscodeset(void){
  outb(PORTMAP_KEYBOARD1, 0xF0);
  if (getscode() == 0xFA ) {
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
  outb(PORTMAP_KEYBOARD1, 0xF0);
  outb(PORTMAP_KEYBOARD1, set);
}


void change_trate_delay(uint8_t set){
  outb(PORTMAP_KEYBOARD1, 0xf3);
  outb(PORTMAP_KEYBOARD1, set);

}
