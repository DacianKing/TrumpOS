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


void swap(char *x,char *y) {
  if (x != y) {
     *x ^= *y;
     *y ^= *x;
     *x ^= *y;
 }
}

u32 free_mem = 0x10000; //heap pointer

void *kmalloc(u32 size) {
  void *ptr = (void*)free_mem; //base address to return

  free_mem +=size;
  return ptr;
}

/*
void kfree(void *start,void *end) {
  for(unsigned int i = start; i =< end; ++i) {
    *start[i] = 0;
  }

}
*/
