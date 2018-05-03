#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>

#define SCAN_CODE_SET1 0x01
#define SCAN_CODE_SET2 0x02
#define SCAN_CODE_SET3 0x03

static uint64_t i = 0;
static uint64_t j = 0;

typedef struct{
  uint8_t pdata[2];
  uint8_t flag;
}key_buf;

key_buf kb;
extern key_buf kb;

void key_init(void);
uint8_t ps2_kerboard_init(void);
void keyboard_input_int(void);
uint8_t enable_keyboard(void);
uint8_t getscode(void);
uint8_t getchar(void);
uint8_t getscodeset(void);
void change_codeset(uint8_t);

#endif _KEYBOARD_H_
