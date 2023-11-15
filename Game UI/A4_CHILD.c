/*******************************************************************
 * Jonny Cardosi
 * Assignment #4
 * Date: 11/10/2023
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) 
 * is licensed under a Creative Commons Attribution-NonCommercial 
 * 3.0 Unported License 
 * (http://creativecommons.org/licenses/by-nc/3.0/). 
 *******************************************************************/
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>

#include <stdlib.h>
#include <unistd.h>

int main() {
        int guessNum=0;
        int SecretNumber=0;
        int r = 0;
        char asciiNum[100];
        char *endptr;

        struct timeval tt;
        (void) gettimeofday(&tt, NULL);
        srand(tt.tv_sec * 1000000 + tt.tv_usec);

        SecretNumber = rand() % 100;

        while( 1 ) {
                if( (r = read(0, asciiNum, 100)) > 0 ) {

                        if ( asciiNum[r-1] == '\n' ) { asciiNum[r-1] = '\0'; }
                        else                         { asciiNum[r]   = '\0'; }

                        //printf("USER ENTERED: |%s|\n", asciiNum);
                        errno=0;
                        guessNum = strtol(asciiNum, &endptr, 10);
                        if( errno != 0 ) {
                                fprintf(stderr, "ERRNO: %d\n", errno);
                                exit(-1);
                        }
                        if( *endptr != '\0' ) {
                                fprintf(stderr, "\tNOT A NUMBER|%s|\n", endptr);
                                exit(-2);
                        }

                        if( guessNum == SecretNumber )
                                printf("YOU GOT IT\n");
                        else if( guessNum > SecretNumber )
                                printf("%d is Too BIG\n", guessNum);
                        else 
                                printf("%d is Too SMALL\n", guessNum);

                        fflush(stdout);
                }
                else {
                        return(0);
                }
        }

        return(0);
}
