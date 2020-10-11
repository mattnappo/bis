#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <ncurses.h>

#define MAX_BUFF 2048
#define MAX_FNAME 32

#define ESCAPE (int)27

#define CENTER(item) ((COLS / 2) - (strlen(item) / 2))
#define END(item) (COLS - strlen(item))

enum mode {
    INSERT,
    REPLACE,
    COMMAND
};

char str_modes[][10] = {
    "INSERT",
    "REPLACE",
    "COMMAND"
};

typedef struct point {
    uint16_t x;
    uint16_t y;
} point;

struct bis_state {
    /* Data */
    char *buffer;
    char *filename;

    /* Metadata */
    enum mode mode;
    uint16_t cx; // Cursor x and y
    uint16_t cy;
};

struct bis_state *init_bis_state()
{
    struct bis_state *state = malloc(sizeof(struct bis_state));
    state->buffer = calloc(MAX_BUFF, 1);
    state->filename = calloc(MAX_FNAME, 1);
    state->filename = "newfile";
    state->mode = INSERT; // TODO: Start in command mode
    state->cx = 0;
    state->cy = 0;
    return state;
}

void destroy_bis_state(struct bis_state *state)
{
    free(state->buffer);
    free(state->filename);
    free(state);
}

void sync_cursor(struct bis_state *state)
{
    move(state->cy, state->cx);
}

void init_bis_scr()
{
    initscr();
    cbreak();
    noecho();
    /*
    if (has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support color\n");
        exit(1);
    }
    */
    clear();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    keypad(stdscr, TRUE);
}

void draw_bottom_bar(struct bis_state *state)
{
    // Print window mode
    char mode_str[20];
    // TODO: Color this
    sprintf(mode_str, "%s", str_modes[state->mode]);
    mvprintw(LINES - 1, 0, mode_str);

    // Print cursor pos
    char pos[25];
    sprintf(pos, "%d:%d", state->cy, state->cx);
    mvprintw(LINES - 1, CENTER(pos), pos);
    
    // Print file name
    char fname[MAX_FNAME + 5];
    sprintf(fname, "%s", state->filename);

    // int index = (CENTER(pos) - strlen(mode_str) / 2) / 2;
    int index = strlen(mode_str) + 2;
    mvprintw(LINES - 1, index, fname);

    // Print window size
    char size[30];
    sprintf(size, "%dx%d", LINES, COLS);
    mvprintw(LINES - 1, END(size), size);

    sync_cursor(state);
}

int main(void)
{
    /* init */

    struct bis_state *core = init_bis_state();
    init_bis_scr();
    
    /* main loop */ 

    timeout(-1); // Blocking mode
    while (1) {
        draw_bottom_bar(core);
        // refresh();
        sync_cursor(core);

        uint32_t c = getch();
        if (c == 96) {
            mvprintw(LINES - 3, 0, "ESCAPED!");
            core->mode = COMMAND;
            refresh();
            break;
        }

        char c_str[10];

        // Debug
        sprintf(c_str, "%d", c);
        mvprintw(LINES - 2, 0, c_str);

        core->cx += 1;
        // core->buffer->append(c); // Buffer the char
        addch(c);
        
        // Actually, move the special keys above
        // the code for the regular keys
        // if (c == ESCAPE) {
        //     break;
        // }
    }

    sleep(5);

    /* cleanup */

    endwin();
    destroy_bis_state(core);
    return 0;
}
