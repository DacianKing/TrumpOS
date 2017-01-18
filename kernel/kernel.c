#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cpu/ports.h"
#include "../filesystem/fs.c"
#include "../filesystem/fs.h"
#include "../drivers/clock.h"
//#include "../drivers/sysinfo.h"

u32 sleeptick,seconds = 0;
u32 uptimetick,uptime = 0;


static void shell_callback() {
sleeptick++;
if(sleeptick % 18 == 0) {
    ++seconds;
  kprintint(seconds,GREEN_ON_BLACK);
  kprint("\n",1);
}
if(seconds == 10) {
  register_interrupt_handler(IRQ0,0);
}
}

static void uptime_callback() {
uptimetick++;
if(uptimetick % 50 == 0) {
  uptime++;
}
}

void main() {

    isr_install();
    irq_install();

      register_interrupt_handler(IRQ0,uptime_callback);

    kprint("\nTrump Shell booted\n\nType HELP for commands\n",WHITE_ON_BLACK);
    kprint("> ",BLUE_ON_BLACK);
}

void user_input(char *input) {

  if(!strcmp(input,"WRITE")) {
      outb(0x1F6,0xA0);
      for(int i = 0x1F2; i < 0x1F6;++i ) {
        outb(i,0);
      }
      outb(0x1F7,0xEC);

      for(int i =0;i < 999;++i) {
        char read = inb(0x1F7);
        if(read > 0) {
          kprintint(i,1);
        }
      }

  }

  else if(!strcmp(input,"read-file")) {

  }

  else if(!strcmp(input,"UPTIME")) {
    kprint("System has been up for: ",0);
    kprintint(uptime,RED_ON_BLACK);
    kprint(" seconds\n",0);
  }

  else if(!strcmp(input,"BEEP")) {
    outb(0x43,182);
    u16 freq = 4560;

    outb(0x42,freq & 0xFF);
    outb(0x42,(freq >> 8) & 0xFF);
    char val = inb(0x61);
    val = val | 192;
    outb(0x61, val);
    //sleep(5000);

    /*
    mov     al, 182         ; Prepare the speaker for the
   out     43h, al         ;  note.
   mov     ax, 4560        ; Frequency number (in decimal)
                           ;  for middle C.
   out     42h, al         ; Output low byte.
   mov     al, ah          ; Output high byte.
   out     42h, al
   in      al, 61h         ; Turn on note (get value from
                           ;  port 61h).
   or      al, 00000011b   ; Set bits 1 and 0.
   out     61h, al         ; Send new value.
   mov     bx, 25          ; Pause for duration of note.
.pause1:
   mov     cx, 65535
.pause2:
   dec     cx
   jne     .pause2
   dec     bx
   jne     .pause1
   in      al, 61h         ; Turn off note (get value from
                           ;  port 61h).
   and     al, 11111100b   ; Reset bits 1 and 0.
   out     61h, al         ; Send new value.
   */
  }

  else if (!strcmp(input, "HALT")) { //returns 0 if equal
        kprint("CPU stopped\n",WHITE_ON_BLACK);
        asm volatile("hlt");
        kprint("test\n",0);
    }

    else if(strchek(input,"STRLEN",strlen("STRLEN"))) {
        int strnum = strlen(input) - 7;
        kprint("Length is ",WHITE_ON_BLACK);
        kprintint(strnum,GREEN_ON_BLACK);
    }

    else if(!strcmp(input,"CLEAR")) {
      clear_screen();
    }

    else if(!strcmp(input,"HELP")) {
      kprint("HALT - Disable interrupts and halts CPU\nCLEAR - clear screen\nSTRLEN (string) - calculate string length\nHELP - Print this helpful message\nREBOOT - Reboot the operating system\nDEBUG - test whatever debug features there is\n",WHITE_ON_BLACK);
    }

    else if (!strcmp(input,"DEBUG")) {
      asm volatile ("int $5");
    }


    else if (!strcmp(input,"REBOOT")) {
       outb(0x64, 0xFE); //reboot using keyboard to pulse the CPU's reset pin
    }

    else if(!strcmp(input,"TIME")) {
      int seconds = getTime(0x00);
      int minutes = getTime(0x02);
      int hours = getTime(0x04) + 7;

      kprintint(hours,GREEN_ON_BLACK);
      kprint("h : ",GREEN_ON_BLACK);
      kprintint(minutes,GREEN_ON_BLACK);
      kprint("m : ",GREEN_ON_BLACK);
      kprintint(seconds,GREEN_ON_BLACK);
      kprint("s",GREEN_ON_BLACK);
      kprint("\n",0);

    }

    else if(!strcmp(input,"DATE")) {
      outb(0x70,0x08);
      char val = inb(0x71);
      kprint(&val,GREEN_ON_BLACK);
    }
    else if(!strcmp(input,"TIMER")) {
      asm("cli");
        register_interrupt_handler(IRQ0, shell_callback);
    }

    else {
      kprint("Command not found. Type HELP for available commands",RED_ON_BLACK);
    }

      kprint("\n> ",BLUE_ON_BLACK);
}
