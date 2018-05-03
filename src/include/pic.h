#ifndef _PIC_H_
#define _PIC_H_

#include <stdint.h>
#include "inb_outb.h"

//PICマスター/スレーブのポートアドレス
#define MASTER_PIC_CMD_STAT  0x20
#define MASTER_PIC_MASK_DATA 0x21
#define SLAVE_PIC_CMD_STAT   0xA0
#define SLAVE_PIC_MASK_DATA  0xa1

//ICWコマンド
#define WRITE_ICW1           0x11
#define WRITE_ICW2_M         0x20
#define WRITE_ICW2_S         0x28
#define WRITE_ICW3_M         0x04
#define WRITE_ICW3_S         0x02
#define WRITE_ICW4_X86MODE   0x01
#define CLEAR_MASK           0xff

//OCW1
#define PIC_MASK_IRQ0        0x01
#define PIC_MASK_IRQ1        0x02
#define PIC_MASK_IRQ2        0x04
#define PIC_MASK_IRQ3        0x08
#define PIC_MASK_IRQ4        0x10
#define PIC_MASK_IRQ5        0x20
#define PIC_MASK_IRQ6        0x40
#define PIC_MASK_IRQ7        0x80
#define PIC_MASK_IRQA        0x00

//EOI
#define PIC_EOI              0x20

void pic_init(void);

#endif _PIC_H_
