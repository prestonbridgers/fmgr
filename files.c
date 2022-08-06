/* [files.c]
 * author: Curt Bridgers
 * email: prestonbridgers@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "files.h"

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

