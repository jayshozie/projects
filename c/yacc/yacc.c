/* yacc -- concatenate files and print on the standard output.
 * This is a cat re-implementation to get better at C programming. */
#include "/home/jaysh/coreutils/gnulib/lib/propername.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_NAME "yacc"
#define AUTHORS                                                                \
    proper_name_utf8("Emir Baha Yildirim",                                     \
                     "Emir Baha Y\304\261ld\304\261r\304\261m"),
#define BUFFER_SIZE 0x2000 // = 8192 bytes = 8 KiB

enum {
    GETOPT_HELP_CHAR = (CHAR_MIN - 2),
};

#define GETOPT_HELP_OPTION_DECL "help", no_argument, NULL, GETOPT_HELP_CHAR

static char const *filename = "-";
int exit_status;

void emit_try_help()
{
    do {
        fprintf(stderr, "Try '%s --help' for more information.\n",
                PROGRAM_NAME);
    }
    while(0);
}

void usage(int status)
{
    if(status != EXIT_SUCCESS) { emit_try_help(); }
    else {
        printf("\
Usage: %s [OPTION]... [FILE]...\n\
Concatenate FILE to standard output.\n\n\
With no FILE, or when FILE is -, read standard input.\n\n\
Options:\n\
-h,--help      Show help.\n\n\
Examples:\n\
%s f - g      Output f's contents, then standard input, then g's contents.\n\
%s            Copy standard input to standard output.\n\
",
               PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME);
    }
    exit(status);
}

void print_error(const char *filename)
{
    exit_status = EXIT_FAILURE;
    fprintf(stderr, "[yacc]: %s: No such file or directory.\n", filename);
}

void process_file(FILE *file_ptr)
{
    int bytes_read;

    while((bytes_read = fgetc(file_ptr)) != EOF) {
        fputc(bytes_read, stdout);
    }
}

int main(int argc, char *argv[])
{
    bool is_help;
    char *help_long = "--help";
    char *help_short = "-h";
    FILE *state;

    if(argc == 1) {
        process_file(stdin);
        exit_status = EXIT_SUCCESS;
    }
    else {
        is_help = ((strcmp(argv[1], help_long) == 0)
                   || strcmp(argv[1], help_short) == 0)
                      ? true
                      : false;

        if(is_help == true) {
            exit_status = EXIT_SUCCESS;
            usage(exit_status);
            exit(0);
        }

        for(int i = 1; i < argc; i++) {
            filename = argv[i];
            if(strcmp(filename, "-") == 0) {
                state = stdin;
            }
            else {
                state = fopen(filename, "r");
            }

            if (state == NULL) {
                exit_status = EXIT_FAILURE;
                print_error(filename);
            }
            else {
                process_file(state);
                exit_status = EXIT_SUCCESS;
                if(state == stdin) {
                    clearerr(stdin);
                }
                if(state != stdin) {
                    fclose(state);
                }
            }
        }
    }
    if(exit_status == EXIT_FAILURE) { exit(1); }
    else {
        exit(0);
    }
}
