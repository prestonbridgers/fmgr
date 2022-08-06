/* [main.c]
 * author: Curt Bridgers
 * email: prestonbridgers@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include "files.h"

typedef struct
{
    WINDOW *win_nav;
    WINDOW *win_preview;
    WINDOW *win_footer;

    PANEL *pan_nav;
    PANEL *pan_preview;
    PANEL *pan_footer;

    MENU *menu;
    ITEM **items;
    ITEM *cur_item;
} FMGR_STATE;

void
fmgr_print_title(WINDOW *win, int width, char *title) {
    mvwaddstr(win, 0, (width / 2) - (strlen(title) / 2), title);
    mvwchgat(win, 0, width / 2 - strlen(title) / 2, strlen(title),
            A_BOLD | A_UNDERLINE, 0, NULL);
    return;
}

int
fmgr_setup(FMGR_STATE *state)
{
    int h_nav, h_preview, h_footer;
    int w_nav, w_preview, w_footer;
    int y_nav, y_preview, y_footer;
    int x_nav, x_preview, x_footer;

	initscr();
    noecho();
    curs_set(0);

    h_footer = 2;
    h_nav = LINES - h_footer - 1;
    h_preview = h_nav;

    w_footer = COLS;
    w_nav = (COLS / 2);
    w_preview = w_nav;

    y_nav = 1;
    y_preview = y_nav;
    y_footer = h_nav + y_nav;

    x_nav = 0;
    x_footer = x_nav;
    x_preview = w_nav + x_nav;

    state->win_footer = newwin(h_footer, w_footer, y_footer, x_footer);
    state->win_nav = newwin(h_nav, w_nav, y_nav, x_nav);
    state->win_preview = newwin(h_preview, w_preview, y_preview, x_preview);

    state->pan_footer = new_panel(state->win_footer);
    state->pan_nav = new_panel(state->win_nav);
    state->pan_preview = new_panel(state->win_preview);

    box(state->win_nav, 0, 0);
    box(state->win_preview, 0, 0);

    fmgr_print_title(state->win_nav, w_nav, "File Nav");
    fmgr_print_title(state->win_footer, w_footer, "Hotkeys");
    fmgr_print_title(state->win_preview, w_preview, "File Preview");
    fmgr_print_title(stdscr, COLS, "FMGR v0.1");

    return 0;
}

char**
fmgr_flist_create(int size)
{
    int i;
    char **flist;
    
    flist = calloc(size, sizeof *flist);
    for (i = 0; i < size; i++) {
        flist[i] = calloc(MAX_FNAME_SIZE, 1);
    }

    return flist;
}

void
fmgr_flist_destroy(char **flist, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        free(flist[i]);
    }
    free(flist);
}

int
main(int argc, char *argv[])
{
    // Variables
    FMGR_STATE *state = malloc(sizeof *state);
    int flist_size = 20;
    char **flist = fmgr_flist_create(flist_size);

    // Getting a list of files
    fmgr_fm_ls(flist, flist_size, ".");

    // Init UI
    fmgr_setup(state);

    

    // Update stdscr
    update_panels();
    doupdate();

    /* for (int i = 0; i < flist_size; i++) { */
    /*     if (flist[i][0] != '\0') */
    /*         printf("%s\n", flist[i]); */
    /* } */

    getch();
    endwin();
    fmgr_flist_destroy(flist, flist_size);
    free(state);
	return EXIT_SUCCESS;	
}

