#include "mem.h"
#include "../drivers/screen.h"

void memory_copy(u8 *source, u8 *dest, int nbytes) { //gross. to fix
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) { //gross. to fix
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

void history() {
  char *that = (char*)0xb8000;
  kprint(that,WHITE_ON_BLACK);
}

void swap(char *s1, char *s2) { //implement xor swap.
  char tmp;
  tmp = *s1;
  *s1 = *s2;
  *s2 = tmp;
  kprint(s1,0);
  kprint("\n",0);
  kprint(s2,0);
}
