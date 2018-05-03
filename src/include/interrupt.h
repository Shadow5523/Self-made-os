#ifndef _INETRRUPT_H_
#define _INETRRUPT_H_

#include "pic.h"

#include <stdint.h>
#include <stddef.h>

void interrupt_done(void);

//irq
void keyboard_interrupt(void);

//irqnum
#define irq1 0x61

#endif _INETRRUPT_H_
