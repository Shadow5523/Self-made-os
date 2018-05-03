#ifndef _IO_H_
#define _IO_H_

#include <stddef.h>
#include "../../include/syscall.h"
#include "sysdep.h"

size_t sh_write(int, const void*, size_t);

#endif _IO_H_
