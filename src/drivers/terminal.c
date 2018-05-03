#include "../include/terminal.h"
#include "../include/vga.h"

void terminal_initialize(void){
  t_row = 0;
  t_column = 0;
  t_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
  t_buffer = (uint16_t*) 0xB8000;   //テキストバッファはこのアドレスから始まる
  for (size_t y = 0; y < VGA_HEIGHT; ++y) {
    for (size_t x = 0; x < VGA_WIDTH; ++x) {
      const size_t index = y * VGA_WIDTH + x;
      t_buffer[index] = vga_entry(' ', t_color);
    }
  }
  terminal_writestring("Initialize Terminal... OK\n");
}


void terminal_setcolor(uint8_t color){
  t_color = color;
}


void terminal_putentryat(uint8_t c, uint8_t color, size_t x, size_t y){
  const size_t index = y * VGA_WIDTH + x;
  t_buffer[index] = vga_entry(c, color);
}


void terminal_uponerow(void){
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      t_buffer[(y - 1) * VGA_WIDTH + x] = t_buffer[index];
      if (y == (VGA_HEIGHT - 1)) {
        t_buffer[index] = vga_entry(' ', t_color);
      }
    }
  }
}


void terminal_putchar(uint8_t c){
  if (c == '\n') {
    c = 0;
    if (++t_row >= VGA_HEIGHT) {
      terminal_uponerow();
      --t_row;
      t_column = -1;
    } else {
      t_column = -1;
    }
  } else if (c == '\t') {
    c = 0;
    t_column += 4;
  } else if(c == '\b') {
    c = 0;
    t_buffer[(t_row * VGA_WIDTH + t_column) - 1] = vga_entry(' ', t_color);
    if (--t_column <= 0) {
      t_column = VGA_WIDTH;
      if (--t_row < 2) {
        t_row = 2;
        t_column = 0;
      }
    }
    return;
  }
  terminal_putentryat(c, t_color, t_column, t_row);
  if (++t_column >= VGA_WIDTH) {
    t_column = 0;
    if (++t_row >= VGA_HEIGHT) {
      terminal_uponerow();
      --t_row;
    }
  }
}


void terminal_write(const uint8_t* data, size_t size){
  for (size_t i = 0; i < size; ++i)
    terminal_putchar(data[i]);
}


void terminal_writestring(const uint8_t* data){
  terminal_write(data, sh_strlen(data));
}
