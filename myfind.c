#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "myfind_methods.c"

int main ( int argc, char * argv[] )
{

    if( (argc < 2))
      {
      printf("Usage: %s <directory-where to start looking> -n <substring-criteria> -t <filetype>\n",argv[0]);
      return -1;
    }

    char* file_name;
    int opt = 0;
    char* type = "a";
    if (argv[1] != NULL) {
        file_name = argv[1];
    } else {
        file_name = ".";
    }
    char* substring = "";

    while ((opt = getopt(argc, argv, "n:t:")) != -1) {
        switch(opt) {
        case 'n':
            substring = optarg;
        case 't':
            type = optarg;
        }
    }

    find_directory(file_name, substring, type);

}
