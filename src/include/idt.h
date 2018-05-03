#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>
#include <stddef.h>
#include "interrupt.h"

#ifdef __cplusplus
extern "C" void load_idtr(uint32_t);
#else
extern void load_idtr(uint32_t);
#endif

extern as_keyboard_interrupt(void);
extern as_software_interrupt(void);

typedef struct{
  uint16_t offset_low;
  uint16_t selector;
  uint8_t dw_count;
  uint8_t s_access;
  uint16_t offset_high;
}__attribute__((packed)) gate_desc;

typedef struct{
  uint16_t idt_size;
  uint32_t base;
}__attribute__((packed)) idtr;

#define LIDT      0x000007ff
#define IDT_LEN   256
gate_desc idt_entries[IDT_LEN];

void idt_init(void);
void set_gate_desc(uint32_t, uint32_t, uint32_t, uint8_t);

#endif _IDT_H_
