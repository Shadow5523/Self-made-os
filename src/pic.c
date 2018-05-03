#include "include/pic.h"

void pic_init(void){
  terminal_writestring("Initialize PIC...");

  outb(MASTER_PIC_MASK_DATA, CLEAR_MASK);
  outb(SLAVE_PIC_MASK_DATA, CLEAR_MASK);

  outb(MASTER_PIC_CMD_STAT, WRITE_ICW1);
  outb(SLAVE_PIC_CMD_STAT, WRITE_ICW1);

  outb(MASTER_PIC_MASK_DATA, WRITE_ICW2_M);
  outb(SLAVE_PIC_MASK_DATA, WRITE_ICW2_S);

  outb(MASTER_PIC_MASK_DATA, WRITE_ICW3_M);
  outb(SLAVE_PIC_MASK_DATA, WRITE_ICW3_S);

  outb(MASTER_PIC_MASK_DATA, WRITE_ICW4_X86MODE);
  outb(SLAVE_PIC_MASK_DATA, WRITE_ICW4_X86MODE);

  outb(MASTER_PIC_MASK_DATA, 0xf9);
  outb(SLAVE_PIC_MASK_DATA, 0xef);

  terminal_writestring("  OK!\n");
}
