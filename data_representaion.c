#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

void print_binary_uint32(uint32_t x) {
    for(int i = 31; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if(i % 4 == 0) printf(" ");
    }
}

void print_int_info(const char* name, long long x, int bits) {
    printf("[%s] %sDecimal:%s %s%lld%s | %sHex:%s 0x%llX | %sBinary:%s ", 
           name, YELLOW, RESET, CYAN, x, RESET, GREEN, RESET, MAGENTA, RESET);
    for(int i = bits-1; i >= 0; i--) {
        printf("%lld", (x >> i) & 1);
        if(i % 4 == 0) printf(" ");
    }
    printf("| Size: %zu bytes\n", bits/8);
}

void print_float_info(const char* name, long double f, int type) {
    printf("[%s] %sValue:%s %s%Lf%s | ", name, YELLOW, RESET, CYAN, f, RESET);
    if(type == 4) {
        union { float f; uint32_t u; } data;
        data.f = (float)f;
        printf("%sHex:%s 0x%X | %sBinary:%s ", GREEN, RESET, data.u, MAGENTA, RESET);
        print_binary_uint32(data.u);
        printf(" | Size: 4 bytes\n");
    } else if(type == 8) {
        union { double d; uint64_t u; } data;
        data.d = (double)f;
        printf("%sHex:%s 0x%lX | %sBinary:%s ", GREEN, RESET, data.u, MAGENTA, RESET);
        for(int i = 63; i >= 0; i--) {
            printf("%llu", (data.u >> i) & 1ULL);
            if(i % 4 == 0) printf(" ");
        }
        printf(" | Size: 8 bytes\n");
    }
}

int main() {
    long long ints[] = {0, 1, -1, 123, -123, INT_MAX, INT_MIN, UINT_MAX};
    const char* int_names[] = {"int", "int", "int", "int", "int", "int", "int", "unsigned int"};
    int bits[] = {32,32,32,32,32,32,32,32};
    int n_ints = sizeof(ints)/sizeof(ints[0]);

    printf("\n=== Integer Representation ===\n\n");
    for(int i = 0; i < n_ints; i++)
        print_int_info(int_names[i], ints[i], bits[i]);

    long double floats[] = {0.0, 1.5, -2.75, 3.14159, 1e10, -1e-10};
    const char* float_names[] = {"float", "float", "float", "double", "double", "long double"};
    int types[] = {4,4,4,8,8,8};
    int n_floats = sizeof(floats)/sizeof(floats[0]);

    printf("\n=== Floating Point Representation ===\n\n");
    for(int i = 0; i < n_floats; i++)
        print_float_info(float_names[i], floats[i], types[i]);

    printf("\n=== Decimal → Binary/Octal/Hex Table ===\n\n");
    for(int i = 10; i <= 20; i++) {
        char bin[33] = {0};
        unsigned int mask = 1 << 7;
        for(int j=7; j>=0; j--) {
            bin[7-j] = (i & (1<<j)) ? '1' : '0';
        }
        printf("%sDecimal:%s %s%2d%s | %sBinary:%s %s | %sOctal:%s %o | %sHex:%s %X\n", 
            YELLOW, RESET, CYAN, i, RESET, MAGENTA, RESET, bin, GREEN, RESET, i, BLUE, RESET, i);
    }

    return 0;
}
