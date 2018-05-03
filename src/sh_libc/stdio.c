#include "include/stdio.h"

int sh_printf(const unsigned char* format, ...){
  va_list parameter;
  va_start(parameter, format);
  sh_vprintf(format, parameter);
  va_end(format);
  return 0;
}


int sh_vprintf(const unsigned char* format, va_list parameter) {
  unsigned long num = 0;
  size_t amount = 0;
  
  while (*format != '\0') {
    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%') { ++format; }
      amount = 1;
      while (format[amount] && format[amount] != '%') { ++amount; }
      if (!print(format, amount)) { return -1; }
      format += amount;
      continue;
    }

    const char* format_begun_at = format++;
    unsigned int length = 0;

    //length
    if (*format == '0'){
      PRINTF_LEN_FLAG = true;
      format++;
      while(*format >= '0' && *format <= '9'){
	length = (length * 10) + (*format - '0');
	format++;
      }
    }

    //type
    switch (*format) {
    case 's':
      ++format;
      const char* string = va_arg(parameter, const char*);
      if (!print(string, sh_strlen(string))) { return -1; }
      break;

    case 'c':
      ++format;
      unsigned char chardata[2];
      chardata[0] = (char)va_arg(parameter, int);
      chardata[1] = '\0';
      if (!print(chardata, sh_strlen(chardata))) { return -1; }
      break;

    case 'i':
    case 'd':
      ++format;
      num = va_arg(parameter, int);
      numeral_formatting(num, length, 10);
      break;
      
    case 'x':
      ++format;
      num = va_arg(parameter, unsigned long);
      numeral_formatting(num, length, 16);      
      break;
      
    default:
      format = format_begun_at;
      if (!print(format, sh_strlen(format))) { return -1; }
      format += sh_strlen(format);
    }
    num = 0;
  }
  return 0;

}


void numeral_formatting(int num, int length, int redix) {
  char pading[255];
  unsigned char data[255];  
  pading[length - 1] = '\0';
  sh_itoa(num, data, redix);
  if (PRINTF_LEN_FLAG && sh_strlen(data) - 1 < length) {
    for (int i = 0; i < length - sh_strlen(data); i++) {
      pading[i] = '0';
    }
    sh_strcat(pading, data);
    if (!print(pading, sh_strlen(pading))) { return -1; }
    PRINTF_LEN_FLAG = false;
  } else {
    if (!print(data, sh_strlen(data))) { return -1; }
  }
}


static bool print(const unsigned char* data, size_t length) {
  const unsigned char* bytes = (const unsigned char*) data;
  for (size_t i = 0; i < length; i++) {
    if (sh_putchar(bytes[i]) == '\0') { return false; }
  }
  return true;
}


int sh_putchar(int intchar) {
  char ch = (char) intchar;
  terminal_write(&ch, sizeof(ch));
  return intchar;
}


unsigned char sh_getchar(void){
  return getscode();
}
