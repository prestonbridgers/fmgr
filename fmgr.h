#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#define MAX_FNAME_SIZE 64

#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <dirent.h>

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

/* BEGIN files.c */
int    fmgr_fm_ls(struct dirent **list_entries, int size, char *dirname);
struct dirent** fmgr_flist_create(int size);
void   fmgr_flist_destroy(struct dirent **flist, int size);
/* END files.c */


/* BEGIN util.c */
void fmgr_print_title(WINDOW *win, int width, char *title);
/* END util.c */

#endif /* FILES_H_INCLUDED */
