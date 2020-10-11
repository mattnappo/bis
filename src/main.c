// TODO: Replace all instances of LINES and COLS with dynamic values stored in a bis_state_t
#include "bis.h"

int main(void)
{
    /* init */

    struct bis_state *core = init_bis_state();
    init_bis_scr();
    
    /* main loop */ 

    int status;
    status = run(core);

    /* cleanup */

    sleep(5);

    endwin();
    destroy_bis_state(core);
    exit(status);
    return 0;
}
