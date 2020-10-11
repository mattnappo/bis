#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <ncurses.h>

#define MAX_BUFF 2048
#define MAX_FNAME 32

enum mode {
    INSERT,
    REPLACE,
    COMMAND
};

char *stringify_mode(enum mode mode)
{
    switch (mode) {

    case INSERT:
        return "INSERT";

    case REPLACE:
        return "REPLACE";

    case COMMAND:
        return "COMMAND";

    default:
        printf("error, unknown mode\n");
        return NULL;
    }
}

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

void init()
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
    keypad(stdscr, TRUE);
}

void draw_bottom_bar(struct bis_state *state)
{
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
}

int main(void)
{
    init();

    struct bis_state *core = init_bis_state();
   
    char lines[10], cols[10];

    sprintf(lines, "%d", LINES);
    sprintf(cols, "%d", COLS);

    mvprintw(0, 0, lines);
    mvprintw(1, 0, cols);
    refresh();
    sleep(3);

    draw_bottom_bar(core);

    sleep(3);

    // if user types :wq, quit
    sleep(1);
    endwin();

    destroy_bis_state(core);

    return 0;
}
