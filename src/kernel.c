#include "kernel.h"

void kernel_main(void){
  terminal_initialize();
  gdt_init();     //追加
  key_init();
  terminal_writestring("Hello, \nkernel \nWorld! \n");
  keyboard_input_int();
}


size_t strlen(const uint8_t* str){
  size_t len = 0;
  while (str[len]) ++len;
  return len;
}
