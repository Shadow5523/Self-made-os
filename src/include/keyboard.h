#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>

//command
#define SET_TYPEMATIC_RATE   0xF3     //追加
#define ENABLE_KEYBOARD      0xF4     //追加
#define SET_SCANCODESET      0xF0     //追加

#define SCAN_CODE_SET1 0x01
#define SCAN_CODE_SET2 0x02
#define SCAN_CODE_SET3 0x03

//以下4つのマクロで定数を宣言
#define TYPEMATICDELAY_SET1 0x01
#define TYPEMATICDELAY_SET2 0x02
#define PORTMAP_KEYBOARD1 0x60
#define PORTMAP_KEYBOARD2 0x64

//構造体は全面的に変更
typedef struct{
  uint8_t pdata[128];
  size_t write;
  size_t read;
  size_t len;
}key_buf;

void key_init(void);
uint8_t ps2_kerboard_init(void);
void keyboard_input_int(uint8_t);
uint8_t enable_keyboard(void);
uint8_t getscode(void);
uint8_t getchar(void);
uint8_t getscodeset(void);
void change_codeset(uint8_t);
void change_trate_delay(uint8_t);     //追加

#endif _KEYBOARD_H_
