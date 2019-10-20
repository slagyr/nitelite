#include "Hardware.h"

void Hardware::printValue(char *label, int value) {
    print(label);
    print((long)value);
    print("\n");
}

void Hardware::println(const char *value) {
    print(value);
    print("\n");
}

void Hardware::println(long value) {
    print(value);
    print("\n");
}

void Hardware::println(double value) {
    print(value);
    print("\n");
}



