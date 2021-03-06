#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f
#define BLUE_ON_BLACK 0x01
#define RED_ON_WHITE 0xf4
#define RED_ON_BLACK 0x04
#define GREEN_ON_BLACK 0x02

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row, char color);
void kprint(char *message,char color);
void kprint_backspace();

#endif
