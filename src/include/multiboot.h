#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
} multiboot_elf_section_header_table_t;

typedef struct {
  uint32_t tab_size;
  uint32_t str_size;
  uint32_t addr;
  uint32_t reserved;
} aout_symbol_table_t;

typedef struct {
  uint32_t flag;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t module_count;
  uint32_t module_addr;

  union {
    aout_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;

  uint32_t mmap_length;
  uint32_t mmap_addr;
} multiboot_info_t;

typedef struct{
  uint32_t size;
  uint32_t base_addr_low;
  uint32_t base_addr_high;
  uint32_t length_low;
  uint32_t length_high;
  uint32_t type;
} multiboot_memory_t;

#endif _MULTIBOOT_H_
