#include "include/io.h"

size_t sh_write(int fd, const void* buffer, size_t byte){
  return system_call(SYSCALL_WRITE, fd, buffer, byte);
}
