
#include "core.h"

static char _int2str[7];

char *int2str(int i) {
    unsigned char L = 1;
    char c;
    bool m = false;
    char b;  // lower-byte of i
    // negative
    if (i < 0) {
        _int2str[0] = '-';
        i = -i;
    } else L = 0;
    // ten-thousands
    if (i > 9999) {
        c = i < 20000 ? 1
                      : i < 30000 ? 2
                                  : 3;
        _int2str[L++] = c + 48;
        i -= c * 10000;
        m = true;
    }
    // thousands
    if (i > 999) {
        c = i < 5000
            ? (i < 3000
               ? (i < 2000 ? 1 : 2)
               : i < 4000 ? 3 : 4
            )
            : i < 8000
              ? (i < 6000
                 ? 5
                 : i < 7000 ? 6 : 7
              )
              : i < 9000 ? 8 : 9;
        _int2str[L++] = c + 48;
        i -= c * 1000;
        m = true;
    } else if (m) _int2str[L++] = '0';
    // hundreds
    if (i > 99) {
        c = i < 500
            ? (i < 300
               ? (i < 200 ? 1 : 2)
               : i < 400 ? 3 : 4
            )
            : i < 800
              ? (i < 600
                 ? 5
                 : i < 700 ? 6 : 7
              )
              : i < 900 ? 8 : 9;
        _int2str[L++] = c + 48;
        i -= c * 100;
        m = true;
    } else if (m) _int2str[L++] = '0';
    // decades (check on lower byte to optimize code)
    b = char(i);
    if (b > 9) {
        c = b < 50
            ? (b < 30
               ? (b < 20 ? 1 : 2)
               : b < 40 ? 3 : 4
            )
            : b < 80
              ? (i < 60
                 ? 5
                 : i < 70 ? 6 : 7
              )
              : i < 90 ? 8 : 9;
        _int2str[L++] = c + 48;
        b -= c * 10;
        m = true;
    } else if (m) _int2str[L++] = '0';
    // last digit
    _int2str[L++] = b + 48;
    // null terminator
    _int2str[L] = 0;
    return _int2str;
}