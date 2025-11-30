#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t test;
} Test;

int main(int argc, char* argv[])
{
    Test testing;

    testing.test = 100;
    printf("struct testing.test: %u", testing.test);

    return 0;
}
