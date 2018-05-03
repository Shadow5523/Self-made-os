#include "../include/idt.h"

void idt_init(void){
  idtr idt;
  terminal_writestring("Initialize IDT...");
  for (size_t i = 0; i < IDT_LEN; i++) {
    set_gate_desc(i, 0, 0, 0);
  }

  set_gate_desc(33, (uint32_t)as_keyboard_interrupt, 0x08, 0x8e);     //追加
  idt.idt_size = IDT_LEN * sizeof(gate_desc) - 1;
  idt.base = (uint32_t)idt_entries;
  load_idtr((uint32_t)&(idt));
  terminal_writestring("  OK!\n");
}


void set_gate_desc(uint32_t index, uint32_t offset, uint32_t selector, uint8_t ar){
  gate_desc *gd = &idt_entries[index];
  gd -> offset_low = offset & 0xffff;
  gd -> offset_high = (offset >> 16) & 0xffff;
  gd -> dw_count = 0;
  gd -> selector = selector;
  gd -> s_access = ar | 0x60;
}
