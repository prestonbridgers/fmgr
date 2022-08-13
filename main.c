/* [main.c]
 * author: Curt Bridgers
 * email: prestonbridgers@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include "fmgr.h"

/* Function is set as the user pointer for each file/directory in the nav
 * menu. When a selection is made, this function is called as a result.
 *
 * dir - The directory or filename of the selected entry.
 */
void
fmgr_nav_selected(char *dir)
{
    fprintf(stderr, "Selected: %s\n", dir);
    return;
}

/* Initializes an FMGR_STATE struct.
 * Memory management is left to the caller.
 *
 * state - The FMGR_STATE struct to initialize.
 * flist - The initial file list to create a menu from.
 * flist_size - The size of the flist given.
 */
int
fmgr_setup(FMGR_STATE *state, struct dirent **flist, int flist_size)
{
    int h_nav, h_preview, h_footer;
    int w_nav, w_preview, w_footer;
    int y_nav, y_preview, y_footer;
    int x_nav, x_preview, x_footer;
    int i;

	initscr();
    noecho();
    curs_set(0);

    // Window dimensions
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

    // Creating windows
    state->win_footer = newwin(h_footer, w_footer, y_footer, x_footer);
    state->win_nav = newwin(h_nav, w_nav, y_nav, x_nav);
    state->win_preview = newwin(h_preview, w_preview, y_preview, x_preview);

    // Creating panels
    state->pan_footer = new_panel(state->win_footer);
    state->pan_nav = new_panel(state->win_nav);
    state->pan_preview = new_panel(state->win_preview);

    // Drawing window borders & titles
    box(state->win_nav, 0, 0);
    box(state->win_preview, 0, 0);

    fmgr_print_title(state->win_nav, w_nav, "File Nav");
    fmgr_print_title(state->win_footer, w_footer, "Hotkeys");
    fmgr_print_title(state->win_preview, w_preview, "File Preview");
    fmgr_print_title(stdscr, COLS, "FMGR v0.1");

    // Drawing hotkeys
    mvwaddstr(state->win_footer, 1, 1, "'q' to Exit | 'hjkl' keys to navigate "
                                       "| Etc...");

    // Creating ITEMs and MENU from flist
    state->items = calloc(flist_size + 1, sizeof *state->items);
    for (i = 0; i < flist_size; i++) {
        /* char *tmp = malloc((MAX_FNAME_SIZE + 5) * sizeof *tmp); */
        /* memcpy(tmp, flist[i]->d_name, strlen(flist[i]->d_name)); */
        /* if (flist[i]->d_type == 4) { */
        /*     strcat(tmp, " d"); */
        /* } else { */
        /*     strcat(tmp, " f"); */
        /* } */
        /* if (tmp[0] != ' ') */
        /*     state->items[i] = new_item(tmp, ""); */
        state->items[i] = new_item(flist[i]->d_name, "");
        set_item_userptr(state->items[i], fmgr_nav_selected);
    }
    state->items[i] = (ITEM *) NULL;

    state->menu = new_menu((ITEM **) state->items);

    // Setting menu main window and subwindow
    set_menu_win(state->menu, state->win_nav);
    set_menu_sub(state->menu, derwin(state->win_nav, h_nav - 2, w_nav - 6, 1, 1));

    // Set menu mark?
    set_menu_mark(state->menu, "-> ");

    return 0;
}

/* The main function.
 */
int
main(int argc, char *argv[])
{
    // Variables
    FMGR_STATE *state = malloc(sizeof *state);
    int flist_size = 20;
    struct dirent **flist = fmgr_flist_create(flist_size);
    int c;

    // Getting a list of files
    fmgr_fm_ls(flist, flist_size, ".");

    // Init UI
    fmgr_setup(state, flist, flist_size);

    // Post the menu 
    post_menu(state->menu);

    // Update stdscr
    update_panels();
    doupdate();

    while ((c = getch()) != 'q') {
        switch (c) {
            case 'j':
                menu_driver(state->menu, REQ_DOWN_ITEM);
                break;
            case 'k':
                menu_driver(state->menu, REQ_UP_ITEM);
                break;
            case 'l': /* Enter */
                {
                    ITEM *cur;
                    void (*p)(char *);

                    cur = current_item(state->menu);
                    p = item_userptr(cur);
                    p((char *)item_name(cur));
                    pos_menu_cursor(state->menu);
                    break;
                }
            default:
                break;
        }

        update_panels();
        doupdate();
    }

    endwin();
    /* fmgr_flist_destroy(flist, flist_size); */
    /* free(state); */
    return EXIT_SUCCESS;	
}

