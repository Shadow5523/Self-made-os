#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

#include "../../include/terminal.h"

int sh_printf(const unsigned char*, ...);
int sh_vprintf(const unsigned char*, va_list);
static bool print(const unsigned char*, size_t);
int sh_putchar(int);

#endif _STDIO_H_
