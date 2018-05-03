#include "../include/kernel.h"

extern key_buf kb;
extern size_t pmstr_len;
size_t pmstr_len;
static size_t i;

void kernel_main(multiboot_info_t* mbt, uint32_t magic){
  terminal_initialize();
  sh_printf("Initialize Terminal... OK\n");
  gdt_init();
  pic_init();
  idt_init();
  key_init();
  getmmap(mbt);
  sh_printf("Hello, kernel World! \n\n");
  prompt();
}


void prompt(void){
  int result = -1;
  char cmdline[1024];
  char *prompt_name = "prompt";
  pmstr_len = sh_strlen(prompt_name);
  sh_printf("\n%s> ", prompt_name);

  kb.len = 0;
  kb.write = 0;
  kb.read = 0;
  i = 0;

  for (;;) {
    if ((result = input_line(prompt_name, cmdline)) != -1) {
      if (i) {
	if (executing(cmdline) == -1) {
	  sh_printf("\nCommand not found!");
	}
      }
      sh_printf("\n%s> ", prompt_name);
      result = -1;
      i = 0;
    }
  }
}


int input_line(char* prompt_name, char* cmdline){
  asm volatile("cli");
  if (!kb.len) {
    asm volatile("sti");
  } else {
    char c = kb.pdata[kb.read];
    --kb.len;
    ++kb.read;
    if (kb.read == 128) { kb.read = 0; }
    asm volatile("sti");

    if (c == '\n') {
      cmdline[i] = '\0';
      return 0;
    } else if (c == '\b') {
      cmdline[i] == '\0';
      if (i > 0) { --i; }
    } else {
      cmdline[i++] = c;
    }
    sh_printf("%c", c);
  }
  return -1;
}


int executing(char* cmdline){
  if (!sh_strcmp(cmdline, "clear")) {
    terminal_initialize();
    return 0;
  } else if (!sh_strcmp(cmdline, "reboot")){
    outb(0x64, 0xFE);
    return 0;
  } else {
    return -1;
  }
}
