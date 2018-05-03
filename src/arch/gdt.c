#include "../include/gdt.h"

void gdt_init(){
  gdtr   gdt;
  terminal_writestring("Initialize GDT...");
  for (size_t i = 0; i < GDT_LEN; i++) {
    set_segment_desc(i, 0, 0, 0, 0);
  }
  set_segment_desc(1, 0, 0xffffffff, 0x9a, 0xcf);
  set_segment_desc(2, 0, 0xffffffff, 0x92, 0xcf);
  set_segment_desc(3, 0, 0xffffffff, 0xfa, 0xcf);
  set_segment_desc(4, 0, 0xffffffff, 0xf2, 0xcf);

  gdt.gdt_size =  GDT_LEN * sizeof(gdt_desc) - 1;
  gdt.base = (uint32_t)gdt_entries;
  load_gdtr((uint32_t)(&gdt));
  terminal_writestring("  OK!\n");
}


void set_segment_desc(uint32_t index, uint32_t base, uint32_t limit, uint8_t s_access, uint8_t gran){
  gdt_desc * sd = &gdt_entries[index];
  sd -> base_high = (base >> 24 & 0xff);
  sd -> base_low = base & 0xffff;
  sd -> base_mid = (base >> 16) & 0xff;
  sd -> s_access = s_access;
  sd -> limit_low = limit & 0xffff;
  sd -> limit_high = ((limit >> 16) & 0x0f) | (gran & 0xf0);
}
