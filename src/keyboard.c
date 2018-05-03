#include "include/keyboard.h"
#include "include/inb_outb.h"

key_buf kb;

void key_init(void){
  change_trate_delay(TYPEMATICDELAY_SET2);     //追加
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


//下の関数を全面的に変更
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

  if (scan_code <= 0x80) {
    if (kb.len < 128) {
      kb.pdata[kb.write++] = us_keytable_set2[scan_code];
      ++kb.len;
      if (kb.write == 128) { kb.write = 0; }
    }
  }
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


//型をuint8_tにしないとVMWareでのキー入力の挙動がおかしくなる
//ので変更
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


//関数名変更
void change_codeset(uint8_t set){
  outb(PORTMAP_KEYBOARD1, SET_SCANCODESET);
  outb(PORTMAP_KEYBOARD1, set);
}

//追加
void change_trate_delay(uint8_t set){
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, SET_TYPEMATIC_RATE);
  while (inb(PORTMAP_KEYBOARD2) & 0x02);
  outb(PORTMAP_KEYBOARD1, set);

}
