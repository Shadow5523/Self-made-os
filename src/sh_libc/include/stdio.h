#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

#include "../../include/terminal.h"

bool PRINTF_LEN_FLAG;

int sh_printf(const unsigned char*, ...);
int sh_vprintf(const unsigned char*, va_list);
void numeral_formatting(int, int, int);
static bool print(const unsigned char*, size_t);
int sh_putchar(int);
unsigned char sh_getchar(void);

#endif _STDIO_H_
