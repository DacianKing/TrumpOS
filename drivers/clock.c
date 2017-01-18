#include "../libc/string.h"
#include "../drivers/screen.h"
#include "../cpu/ports.h"

#define RTC_PORT_OUT 0x70
#define RTC_PORT_IN 0x71

int getTime(char cmos_reg) {
  outb(RTC_PORT_OUT,cmos_reg);
  u8 value_low = inb(RTC_PORT_IN);

  outb(RTC_PORT_OUT,cmos_reg + 1);
  u8 value_high = inb(RTC_PORT_IN);

  int value = value_high;
  value = value << 8;
  value+= value_low;

  return value;
}

int getDate() {
  return 0;
}
