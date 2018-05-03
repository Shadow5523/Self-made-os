#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//command
#define SWITCH_LED           0xED
#define ENABLE_KEYBOARD      0xF4
#define SET_SCANCODESET      0xF0
#define SET_TYPEMATIC_RATE   0xF3

//options
#define SCAN_CODE_SET1       0x01
#define SCAN_CODE_SET2       0x02
#define SCAN_CODE_SET3       0x03
#define GET_SCAN_CODE_SET    0x00

#define TYPEMATICDELAY_SET01 0x01
#define TYPEMATICDELAY_SET02 0x02
#define TYPEMATICDELEY_SET11 0x0B

#define PORTMAP_KEYBOARD1    0x60
#define PORTMAP_KEYBOARD2    0x64

//keyled
#define SET_CAPSLOCK_LED     0x04
#define SET_NUMLOCK_LED      0x02
#define SET_SCROLLLOCK_LED   0x01

//scan_code
#define L_SHIFT              0x2A
#define R_SHIFT              0x36
#define CAPS_LOCK            0x3A
#define NUM_LOCK             0x45
#define SCROLL_LOCK          0x46

typedef struct{
  uint8_t pdata[128];
  size_t write;
  size_t read;
  size_t len;
}key_buf;

typedef struct{
  uint8_t base[0x80];
  uint8_t shift[0x80];
  uint8_t numlock[0x80];
}keymap;

typedef struct{
  bool shift_enable:1;
  bool relese_enable:1;
  bool caps_lock:1;
  bool num_lock:1;
  bool scr_lock:1;
  uint8_t led_stat;
}kb_stat;

kb_stat ks;
const keymap key_code;
bool ext_input;

void key_init(void);
uint8_t ps2_kerboard_init(void);
void keyboard_input_int(uint8_t);
void switch_kb_led(uint8_t);
uint8_t enable_keyboard(void);
uint8_t getscode(void);
uint8_t getchar(void);
uint8_t getscodeset(void);
void change_codeset(uint8_t);
void change_trate_delay(uint8_t);
void input_bufdata(uint8_t);

#endif _KEYBOARD_H_
