Codebase:
├── Makefile
├── myfind
├── myfind.c
├── myfind_methods
├── myfind_methods.c
├── myfind_methods.h
├── myfind_methods.o
├── myfind.o
└── README.txt

The program must be compiled with at least 2 arguments so that the program can default to a directory to search through. In addition, it is assumed that the user knows what arguments to use or else there will be an error message that will show up on the screen. A known limitation or error is that the user cannot search through a directory that is private or closed to the public and there will be an opendir() error message. In addition, the only known limitations and errors is that the user cannot search through something that is not a directory, the user cannot search through a private directory, and the user cannot search through something that has not been created.
