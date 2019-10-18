#ifndef NITELITE_TESTUTIL_H
#define NITELITE_TESTUTIL_H

#include <iostream>
#include <string>

void print_buffer(byte *buffer) {
    for(int page = 0; page < 8; page++) {
        int y = 128 * page;
        for (int row = 0; row < 8; row++) {
            int line_no = page * 8 + row;
            std::string txt = "" + std::to_string(line_no) + " ";
            if(line_no < 10)
                txt = " " + txt;
            int mask = 1 << row;
            for(int col = 0; col < 128; col++) {
                if(buffer[y + col] & mask)
                    txt += "*";
                else
                    txt += " ";
            }
            std::cout << txt << std::endl;
        }
    }
}

#endif //NITELITE_TESTUTIL_H
