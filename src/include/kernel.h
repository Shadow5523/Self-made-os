#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

/* コンパイラが正しいターゲットを認識しているかの確認 */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* 32-bit x86ターゲット以外のコンパイラを使用するとエラーになる */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "terminal.h"
#include "keyboard.h"
#include "inb_outb.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"

uint8_t* c[2];     //追加

size_t strlen(const uint8_t*);

#if defined(__cplusplus)
us_keytableextern "C"
#endif
