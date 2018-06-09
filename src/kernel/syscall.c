#include "../include/syscall.h"
#include "../sh_libc/include/stdio.h"

uint32_t syscall_interrupt(uint32_t syscall_num,
			   uint32_t arg1,
			   uint32_t arg2,
			   uint32_t arg3,
			   uint32_t arg4,
			   uint32_t arg5){
  switch (syscall_num) {
  case SYSCALL_WRITE:
    return do_write(arg1, arg2, arg3);
    break;
  case SYSCALL_READ:
    return do_read(arg1, arg2, arg3);
    break;
  }
  return 0;
}
