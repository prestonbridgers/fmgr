/* [util.c]
 * author: Curt Bridgers
 * email: prestonbridgers@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "fmgr.h"

/* Utility function that prints a centered title at the top of an nCurses
 * window.
 *
 * win   - The nCurses window on which to print a title.
 * width - The width of the nCurses window.
 * title - The title to be printed.
 */
void
fmgr_print_title(WINDOW *win, int width, char *title)
{
    mvwaddstr(win, 0, (width / 2) - (strlen(title) / 2), title);
    mvwchgat(win, 0, width / 2 - strlen(title) / 2, strlen(title),
            A_BOLD | A_UNDERLINE, 0, NULL);
    return;
}

