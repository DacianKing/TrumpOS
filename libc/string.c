#include "string.h"
#include "../drivers/screen.h"

/**
 * K&R implementation
 */

 char *strcpy(char *dest, const char *src)
{
  unsigned i;
  for (i=0; src[i] != '\0'; ++i)
    dest[i] = src[i];
  dest[i] = '\0';
  return dest;
}

 void hex_to_ascii(int n, char str[]) {
     append(str, '0');
     append(str, 'x');
     char zeros = 0;

     s32 tmp;
     int i;
     for (i = 28; i > 0; i -= 4) {
         tmp = (n >> i) & 0xF;
         if (tmp == 0 && zeros == 0) continue;
         zeros = 1;
         if (tmp > 0xA) append(str, tmp - 0xA + 'a');
         else append(str, tmp + '0');
     }

     tmp = n & 0xF;
     if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
     else append(str, tmp + '0');
 }



void kprintint(int number,char color) {
  char numstr[10] = { 0 };
  int_to_ascii(number,numstr);
  kprint(numstr,color);
}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}
void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strchek(char s1[],char s2[], int pos) { //no bools in c90
  for(int i =0; i < pos;++i) {
    if(s1[i] != s2[i])
    return false;
  }
  return true;
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}
