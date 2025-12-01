/* show -- concatenate files and print on the standard output.
 * This is a cat re-implementation to get better at C programming. */
#include "/home/jaysh/coreutils/gnulib/lib/propername.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define PROGRAM_NAME "show"
#define AUTHORS                                                                \
    proper_name_utf8("Emir Baha Yildirim",                                     \
                     "Emir Baha Y\304\261ld\304\261r\304\261\m"),
#define BUFFER_SIZE 8192 // 8 KiB

static char const *filename;


void print_help()
{
    printf("Usage: show [OPTION]... [FILE]...\n");
    printf("Concatenate FILE to standard output.\n\n");
    printf("With no FILE, read standard input.\n\n");
    printf("Options:\n");
    printf("-h,--help    Show help.");
}

void print_error(char *filename)
{
    fprintf(stderr, "[show]: %s: No such file or directory.\n", filename);
}

void process_file(FILE *file_ptr)
{
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while((bytes_read = fread(buffer, 1, BUFFER_SIZE, file_ptr))
          > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

int main(int argc, char *argv[])
{

    char *help_long = "--help";
    // char *help_short = "-h";

    char *filename;
    FILE *state;

    if(argc == 1) { process_file(stdin); }

    if(strcmp(argv[1], help_long) == 0) {
        print_help();
        exit(0);
    }

    for(int i = 1; i < argc; i++) {
        filename = argv[i];
        if((state = fopen(filename, "r")) == NULL) { print_error(filename); }
        else {
            process_file(state);
            fclose(state);
        }
    }
}
