#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" void load_gdtr(uint32_t);
#else
extern void load_gdtr(uint32_t);
#endif

typedef struct{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t s_access;
  uint8_t limit_high;
  uint8_t base_high;
}__attribute__((packed)) gdt_desc;

typedef struct{
  uint16_t gdt_size;
  uint32_t base;
}__attribute__((packed)) gdtr;

#define GDT_LEN 8192
gdt_desc gdt_entries[GDT_LEN];

void gdt_init();
void set_segment_desc(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

#endif _GDT_H_
