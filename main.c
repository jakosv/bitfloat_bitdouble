#include <stdio.h>
#include <stdlib.h>

typedef union {
    float value;
    struct {
        unsigned mantissa: 23;
        unsigned exponent: 8;
        unsigned sign: 1;
    } Bits;
} BitFloat;

typedef union {
    double value;
    struct {
        unsigned long long mantissa: 52;
        unsigned exponent: 11;
        unsigned sign: 1;
    } Bits;
} BitDouble;

char* printBits(unsigned long long num, int bitsCount) {
    char* res = (char*) malloc(sizeof(char) * (bitsCount + 1));
    int ptr = 0;
    for (int i = bitsCount - 1; i >= 0; --i) {
        if (num & (1LL << i)) {
            res[ptr] = '1';
        }
        else {
            res[ptr] = '0';
        }
        ptr++;
    }
    res[ptr] = '\0';

    return res;
}

char* getBitFloatString(BitFloat* bitFloat) {
    const int size = sizeof(float) * 8 + 3;
    char* res = (char*) malloc(sizeof(char) * size);
    char* signString = printBits(bitFloat->Bits.sign, 1);
    char* exponentString = printBits(bitFloat->Bits.exponent, 8);
    char* mantissaString = printBits(bitFloat->Bits.mantissa, 23);
    sprintf(res, "%s %s %s", signString, exponentString, mantissaString);
    res[size] = '\0';

    return res;
}

char* getBitDoubleString(BitDouble* bitDouble) {
    const int size = sizeof(double) * 8 + 3;
    char* res = (char*) malloc(sizeof(char) * size);
    char* signString = printBits(bitDouble->Bits.sign, 1);
    char* exponentString = printBits(bitDouble->Bits.exponent, 11);
    char* mantissaString = printBits(bitDouble->Bits.mantissa, 52);
    sprintf(res, "%s %s %s", signString, exponentString, mantissaString);
    res[size] = '\0';

    return res;
}

int main() {
    BitDouble d;
    d.value = 0;
    d.Bits.exponent = 1024 + 1023;
    char* bitString = getBitDoubleString(&d);

    printf("%s\n", bitString);
    printf("Value: %lf\n", d.value);
    return 0;
}
