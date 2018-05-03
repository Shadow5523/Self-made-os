#include "../include/getmmap.h"

void getmmap(multiboot_info_t* mbt){
  multiboot_memory_t* mmap = mbt -> mmap_addr;
  char* type_str;

  sh_printf("\n\n================get memory map=====================\n");

  for (mmap; mmap < (mbt -> mmap_addr + mbt -> mmap_length); mmap++) {

    switch (mmap -> type) {
    case 0x1:;
      sh_strcpy(type_str, "available RAM");
      break;
    case 0x2:;
      sh_strcpy(type_str, "reserved RAM");
      break;
    case 0x03:;
      sh_strcpy(type_str, "ACPI reclaimable RAM");
      break;
    case 0x04:;
      sh_strcpy(type_str, "ACPI non-volatile storage RAM");
      break;
    }
    if (mmap -> base_addr_high == 0x0) {
      sh_printf("base_addr = 0x%x: ", mmap -> base_addr_low);
    } else {
      sh_printf("base_addr = 0x%x%08x: ", mmap -> base_addr_high, mmap -> base_addr_low);
    }

    if (mmap -> length_high == 0x0) {
      sh_printf("length = 0x%x: ", mmap -> length_low);
    } else {
      sh_printf("length = 0x%x%08x: ", mmap -> length_high, mmap -> length_low);
    }
    sh_printf("type = %s\n", type_str);
  }

  sh_printf("===================================================\n\n");
}
