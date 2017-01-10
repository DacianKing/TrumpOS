#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cpu/ports.h"
#include "../drivers/sysinfo.c"

void main() {

    isr_install();
    irq_install();

    kprint("\nTrump Shell booted\n\nType HELP for commands\n",WHITE_ON_BLACK);
    kprint("> ",BLUE_ON_BLACK);
}

void user_input(char *input) {

  if(!strcmp(input,"SYSINFO")) {
    /*
    volatile asm("pushad");
    volatile asm("xor eax,eax")
    volatile asm("cpuid");
    volatile asm("popad");
    */
  }

  if (!strcmp(input, "HALT")) { //returns 0 if equal. thanks libc
        kprint("CPU stopped\n",WHITE_ON_BLACK);
        asm volatile("hlt");
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
      asm volatile ("int $15");
    }


    else if (!strcmp(input,"REBOOT")) {
       outb(0x64, 0xFE); //reboot using keyboard to pulse the CPU's reset pin
    }

    else {
      kprint("Command not found. Type HELP for available commands",RED_ON_BLACK);
    }

      kprint("\n> ",BLUE_ON_BLACK);
}
