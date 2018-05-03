#include "../include/interrupt.h"

void interrupt_done(void){
  outb(MASTER_PIC_CMD_STAT, PIC_EOI);
  outb(SLAVE_PIC_CMD_STAT, PIC_EOI);
}


void keyboard_interrupt(void){
  outb(MASTER_PIC_CMD_STAT, irq1);
  keyboard_input_int(sh_getchar());
  interrupt_done();
}
