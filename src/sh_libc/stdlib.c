#include "include/stdlib.h"

void sh_itoa(unsigned long data, unsigned char* str, unsigned int base){
  size_t i = 0;
  unsigned long num = data;
  unsigned long copynum = data;
  unsigned long lorder;
  do {
    if(base == 16) {
      lorder = num & 0xF;
      num >>= 4;
    } else {
      lorder = num;
      copynum >>= 27;
    }
    copynum >>= 4;
    do {
      data = lorder % base;
      if (data < 0x0A) {
	str[i++] = '0' + data;
      } else {
	str[i++] = 'A' + data - 0x0A;
      }
      lorder /= base;
    } while (lorder);
  } while (copynum);
  str[i] = '\0';

  sh_strrev(str);
}
