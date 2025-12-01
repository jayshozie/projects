#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long long amount = 100000;
    FILE *test_file;
    char *test_text = "test\n";
    char *test_file_name = "test.txt";

    if(argc != 1) {
        amount = strtoll(argv[1], NULL, 10); // Base 10
    }
    printf("[TC]: %Ld lines written to %s.", amount, test_file_name);

    test_file = fopen(test_file_name, "w");
    int i = 0;
    do {
        fputs(test_text, test_file);
        i++;
    }
    while(i < amount);
    fclose(test_file);
}
