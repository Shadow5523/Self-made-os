#include "../include/get_ksize.h"

uint32_t get_ksize(void){
  return &__kernel_end - &__kernel_start;
}
