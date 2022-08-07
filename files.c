/* [files.c]
 * author: Curt Bridgers
 * email: prestonbridgers@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "files.h"

/* Populates a list of strings created by fmgr_flist_create with the filenames
 * contained in a given directory.
 *
 * Returns 0 on success, and 1 on error.
 *
 * list_entries - The list created with fmgr_flist_create.
 * size         - The size of the list_entries as given to fmgr_flist_create
 *                when it was created.
 * dirname      - The path to the directory to list.
 */
int
fmgr_fm_ls(char **list_entries, int size, char *dirname)
{
	DIR *d;
    struct dirent *dir;
    int count;

    d = opendir(dirname);
    if (!d) {
        return EXIT_FAILURE;
    }

    count = 0;
    while ((dir = readdir(d)) != NULL) {
        strncpy(list_entries[count], dir->d_name, MAX_FNAME_SIZE);
        count++;
    }

    closedir(d);
    return EXIT_SUCCESS;
}

