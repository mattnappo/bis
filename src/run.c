#include "bis.h"

int run(struct bis_state *state)
{
    timeout(-1); // Blocking mode
    while (1) {
        draw_bottom_bar(state);
        sync_cursor(state);
        refresh();

        switch (state->mode) {
            case COMMAND:
                handle_command(state);
                break;

            case INSERT:
                handle_insert(state);
                break;

            case REPLACE:
                handle_insert(state);
                break;

            default:
                mvprintw(LINES - 4, 0, "ERROR: Invalid mode");
                return 1;
        }
    }
    return 0;
}
