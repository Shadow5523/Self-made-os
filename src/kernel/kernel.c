#include "../include/kernel.h"

extern key_buf kb;

void kernel_main(multiboot_info_t* mbt, uint32_t magic){
  terminal_initialize();
  gdt_init();
  pic_init();
  idt_init();
  key_init();

  getmmap(mbt);

  terminal_writestring("Hello, kernel World! \n\n");

  kb.len = 0;
  kb.write = 0;
  kb.read = 0;

  for (;;) {
    asm volatile("cli");
    if (kb.len == 0) {
      asm volatile("sti");
    } else {
      c[0] = kb.pdata[kb.read];
      --kb.len;
      ++kb.read;
      if (kb.read == 128) { kb.read = 0; }
      asm volatile("sti");
      terminal_writestring(c);
    }
  }
}
