#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#define SC_HEIGHT 50
#define SC_WIDTH 90

#define BUFFER 1024

#define ESCAPE_OCT "\33"
#define ESCAPE (int)27

void cls()
{
    for (int i = 0; i < SC_HEIGHT * 2; i++) {
        printf("\n");
    }
}

int test()
{
    cls();
    
    puts("test");

    char *input = calloc(BUFFER, sizeof(char));

    printf("\033[0;0H"); // Move to 0,0

    /*
    while (1) {
        input = calloc(BUFFER, sizeof(char)); // Clear the buffer
        fgets(input, 1024, stdin);
        printf("buffer: %s\n", input);
        if (strcmp(input, ESCAPE) == 0) {
            printf("escaped!\n");
            break;
        }
    }
    */

    /*
    while (1) {
        char last = getchar();
        if (last != ESCAPE) {
            break;
        }
        printf("hi");
        fgets(input, 1024, stdin);
    } 
    */

    printf("buffer: %s\n", input);

    printf("broke out of loop\n");

    return 0;
}

