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


  outb(RTC_PORT_OUT,0x0B);
  char format = inb(0x71);

  if(format == 2) {
    kprintint(2,1);
  }
  else if(format == 4) {
    kprintint(4,1);
  }

    int value = value_high;
    value = value << 8;
    value+= value_low;

    return value;
}

void writeCMOS(char cmos_reg) {
  outb(RTC_PORT_OUT,cmos_reg);
  outb(RTC_PORT_IN,(unsigned char)50);

}

int getDate() {
  return 0;
}
