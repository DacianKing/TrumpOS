#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void main() {

    isr_install();
    irq_install();

    kprint("\nTrump Shell booted\n\nType HELP for commands\n",WHITE_ON_BLACK);
    kprint("> ",BLUE_ON_BLACK);
}

void user_input(char *input) {
  if (!strcmp(input, "HALT")) { //returns 0 if equal. thanks libc
        kprint("CPU stopped\n",WHITE_ON_BLACK);
        asm volatile("hlt");
    }

  if(!strcmp(input,"HISTORY")) {
  //  kprint(histarray,0);
  }

    else if(strchek(input,"STRLEN",strlen("STRLEN"))) {
        int strnum = strlen(input) - 7;
        kprint("Length is ",WHITE_ON_BLACK);
        kprintint(strnum,RED_ON_WHITE);
    }

    else if(!strcmp(input,"CLEAR")) {
      clear_screen();
    }

    else if(!strcmp(input,"HELP")) {
      kprint("HALT - Disable interrupts and halts CPU\nCLEAR - clear screen\nSTRLEN (string) - calculate string length\nHELP - Print this helpful message\n",WHITE_ON_BLACK);
    }

    else {
      kprint("Command not found. Type HELP for available commands",RED_ON_BLACK);
    }

      kprint("\n> ",BLUE_ON_BLACK);
}
