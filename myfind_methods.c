#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "myfind_methods.h"

int isdirectory( char * filename ) {
    int             err;
    struct  stat            mystat;

    err = stat( filename, &mystat );

    if( -1 == err ) {
        if( ENOENT == errno ) {
            /* does not exist */
            return 0;
        } else {
            perror( "stat" );
            exit(1);
        }
    } else {
        if( S_ISDIR( mystat.st_mode) ) {
            /* it's a dir */
            return 1;
        } else {
            /* exists but is not a directory */
            printf("ls: %s: No such file or directory", filename );
            return 0;
        }
    }

}

void find_directory(char *dirname, char* substring, char* type) {
    DIR         *mydir ;
    struct dirent   *myfile = NULL;
    struct stat     mystat;
    char buffer[1024];

    // finds if it is not a directory
    if( ! isdirectory( dirname ) ) {
         printf("it is not a directory\n" );
         exit(0);
     }

     mydir = opendir( dirname );
     // finds if opendir does not work
     if( mydir == NULL ) {
         perror("opendir");
         exit(0);
     }

     // prints the cwd if the type is directory or all
     if (dirname[0] == '.' && (type[0] == 'd' || type[0] == 'a')) {
         printf("%s\n", dirname);
     }

     // while loop where stat reads from current directory and checks if it is in cwd
      while( (myfile = readdir( mydir ) ) != NULL ) {
         if (strcmp(myfile->d_name, ".") == 0 || strcmp(myfile->d_name, "..") == 0) {
             continue;
         }
         sprintf(buffer, "%s/%s", dirname, myfile->d_name);
         // checks if stat works
         if (lstat(buffer, &mystat) < 0) {
             perror("lstat");
             exit(0);
         }
         // checks if the mode is equal to the type
         if ((S_ISDIR(mystat.st_mode) && type[0] == 'd') ||
         (S_ISBLK(mystat.st_mode) && type[0] == 'b') ||
         (S_ISCHR(mystat.st_mode) && type[0] == 'c') ||
         (S_ISREG(mystat.st_mode) && type[0] == 'f') ||
         (S_ISLNK(mystat.st_mode) && type[0] == 'l') ||
         (S_ISFIFO(mystat.st_mode) && type[0] == 'p') ||
         (S_ISSOCK(mystat.st_mode) && type[0] == 's') || (type[0] == 'D')) {
             // checks if the substring is inside of the name
             if ((strstr(myfile->d_name, substring) != NULL) ||
             (strchr(myfile->d_name, substring[0]) != NULL && strlen(substring) == 1)) {
                 printf("%s\n", buffer);
             }
             // uses recursive function if mode is directory and type is not d
         } else if (S_ISDIR(mystat.st_mode) && type[0] != 'd') {
             find_directory(buffer, substring, type);
         } else if (type[0] == 'a') {
             // checks if the substring is inside of the name
             if ((strstr(myfile->d_name, substring) != NULL) ||
             (strchr(myfile->d_name, substring[0]) != NULL && strlen(substring) == 1)) {
                 printf("%s\n", buffer);
                 // if mode is directory, then use recursive function
                 if (S_ISDIR(mystat.st_mode)) {
                     find_directory(buffer, substring, type);
                 }
             }
         }
      }
      // closes directory structure
     closedir(mydir);
     }
