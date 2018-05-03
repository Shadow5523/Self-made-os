#include "keyboard.h"
#include "inb_outb.h"

void key_init(void){
  if (enable_keyboard() == 0xFA) {
    terminal_writestring("Keyboard enable OK\n");
  }
  if (ps2_kerboard_init() == 0) {
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


void keyboard_input_int(void){
  uint32_t old, scan_code;
  uint8_t us_keytable_set2[0x54] = {
    '0', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '-', '=', '\b', '\t', 'Q', 'W', 'E', 'R', 'T',
    'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '0', 'A',
    'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'',
    '`', '0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',
    ',', '.', '/', '0', '*', '0', ' ', '0', '0', '0',
    '0', '0', '0', '0', 'a', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0'};
  uint8_t psend[2];

  while(1){
    scan_code = getchar();
    if (scan_code <= 0x80) {
      psend[0] = us_keytable_set2[scan_code];
      psend[1] = 0;
      if (i == 1) {
	if (j == 0) {
	  terminal_writestring(psend);
	  old = scan_code;
	} else if (j > 800000) {

	  terminal_writestring(psend);
	}
      }

      if (old != scan_code) {
	i = 0;
	j = 0;
      } else if (old == scan_code) {
	++j;
      }

      if(i > 700000) i = 0;
      ++i;
    }
  }
}


uint8_t enable_keyboard(void){
  outb(0x60, 0xF4);
  return getscode();
}


uint8_t getscodeset(void){
  while (inb(0x64) & 0x02);
  outb(0x60, 0xf0);
  if (getscode() == 0xFA) {
    while (inb(0x64) & 0x02);
    outb(0x60, 0x00);
    return getscode();
  } else {
    return 0x00;
  }
}


uint8_t getscode(void){
  uint8_t c = 0;
  do {
    if (inb(0x60) != c) {
      c = inb(0x60);
      if (c > 0) return c;
    }
  } while (1);
}


uint8_t getchar(void){
  return getscode();
}


void change_codeset(uint8_t set){
  outb(0x60, 0xf0);
  outb(0x60, set);
}
