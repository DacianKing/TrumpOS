#ifndef STRINGS_H
#define STRINGS_H

#define true 1
#define false 0

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int strchek(char s1[],char s2[],int pos); //booleans are not implemented in standard c
void kprintint(int number,char color);
char *itoa(int i, char b[]);
char *strcpy(char *dest, const char *src);
 void hex_to_ascii(int n, char str[]);

#endif
