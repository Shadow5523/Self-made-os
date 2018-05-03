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
  bool flag = false;
  
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
      flag = true;
      format++;
      while(*format >= '0' && *format <= '9'){
	length = (length * 10) + (*format - '0');
	format++;
      }
    }

    char pading[255];
    pading[length - 1] = '\0';

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
      unsigned char decimaldata[11];
      num = va_arg(parameter, int);
      
      sh_itoa(num, decimaldata, 10);
      if (flag && sh_strlen(decimaldata) - 1 < length) {
	for (int i = 0; i < length - sh_strlen(decimaldata); i++) {
	  pading[i] = '0';
	}
	sh_strcat(pading, decimaldata);
	if (!print(pading, sh_strlen(pading))) { return -1; }
	flag = false;
      } else {
	if (!print(decimaldata, sh_strlen(decimaldata))) { return -1; }
      }
      
      break;
      
    case 'x':
      ++format;
      unsigned char hexdata[9];
      num = va_arg(parameter, unsigned long);
      
      sh_itoa(num, hexdata, 16);
      if (flag && sh_strlen(hexdata) - 1 < length) {
	for (int i = 0; i < length - sh_strlen(hexdata); i++) {
	  pading[i] = '0';
	}
	sh_strcat(pading, hexdata);
	if (!print(pading, sh_strlen(pading))) { return -1; }
	flag = false;
      } else {
	if (!print(hexdata, sh_strlen(hexdata))) { return -1; }
      }
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
