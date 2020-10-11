#ifndef BIS_H
#define BIS_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <ncurses.h>

#define MAX_BUFF  2048
#define MAX_FNAME 32

#define ESCAPE (int) 27
#define TILDE  (int) 96
#define RETURN (int) 13

#define CENTER(item) ((COLS / 2) - (strlen(item) / 2))
#define END(item) (COLS - strlen(item))
//#define BETWEEN(item1, item2) (CENTER(CENTER(item) / 2))

enum mode {
    INSERT,
    REPLACE,
    COMMAND
};

static char str_modes[][10] = {
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
    enum mode mode;

    /* Cursor pos */
    uint16_t cx;
    uint16_t cy;

    /* Screen lines and cols */
    uint16_t lines;
    uint16_t cols;
};

void init_bis_scr();

struct bis_state *init_bis_state();
int run(struct bis_state *state);

void destroy_bis_state (struct bis_state *state);
void sync_cursor       (struct bis_state *state);
void draw_bottom_bar   (struct bis_state *state);
void handle_insert     (struct bis_state *state);
void handle_command    (struct bis_state *state);
int  handle_replace    (struct bis_state *state);



#endif

