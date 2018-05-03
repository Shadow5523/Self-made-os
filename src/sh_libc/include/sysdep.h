#ifndef _SYSDEP_H_
#define _SYSDEP_H_

#include <stdint.h>

#define GET_MACRO(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define system_call(...) GET_MACRO(__VA_ARGS__, system_call5, system_call4, system_call3, \
				   system_call2, system_call1)(__VA_ARGS__)

uint32_t system_call5(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t system_call4(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t system_call3(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t system_call2(uint32_t, uint32_t, uint32_t);
uint32_t system_call1(uint32_t, uint32_t);

#endif _SYSDEP_H_
