#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

void printnumber(int n, int base) {

   if (n < 0) {
       putchar('-');
       n = -n;
   }

   if (n/base) {
       printnumber(n/base, base);
   }

   putchar(n%base + '0');
}

void *convert(unsigned int num, int base)
{
	char Representation[]= "0123456789abcdef";
	int len = 0;
    int numcopy = num;
    char *ptr;

    while (numcopy != 0) {
        numcopy /= base;
        len++;
    }

    ptr = malloc(sizeof(char) * len + 1);

    while(num != 0) {
        *ptr = Representation[num%base];
        num /= base;
        ptr++;
    }

    *ptr = '\0';

    ptr--;

    while(*ptr) {
        putchar(*ptr);
        ptr--;
    }
}

void putDouble(double x)
{
    long d;
    int p = 6;
    if (x < 0) {
        putchar('-');
        x=-x;
    }
    d = x;
    printnumber(d, 10);
    putchar('.');
    while(p--) {
        x = (x - d) * 10;
        d = x;
        putchar('0' + d);
    }
}

int my_printf(char* format, ...) {
    int count = 0;
    char *output;

    char *s, c;
    int d, i;
    float f;

    va_list arg;
    va_start(arg, format);

    for(output = format; *output != '\0'; output++) {
        if(*output == '%') {
            output++;
            count++;

            switch(*output) {
                case 'c':
                    c = (char) va_arg(arg, int);
                    putchar(c);
                    break;
                case 'd':
                    d = va_arg(arg, int);
                    printnumber(d, 10);
                    break;
                case 's':
                    s = va_arg(arg, char *);
                    for(int i = 0; s[i] != '\0'; i++) {
                        putchar(s[i]);
                    }
                case 'x':
                    d = va_arg(arg, unsigned int);
                    convert(d, 16);
                    break;
                case 'o':
                    d = va_arg(arg, unsigned int);
                    convert(d, 8);
                    break;
                case 'f':
                    f = va_arg(arg, double);
                    putDouble(f);
                case 'p':
                    d = va_arg(arg, int);
                    convert(d, 16);
            }
        }
    }

    va_end(arg);

    return count;
};



int main() {

    int a = 567;
    my_printf("%p\n", &a);
}
