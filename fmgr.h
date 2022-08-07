#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#define MAX_FNAME_SIZE 64

int    fmgr_fm_ls(char **list_entries, int size, char *dirname);
char** fmgr_flist_create(int size);
void   fmgr_flist_destroy(char **flist, int size);

#endif /* FILES_H_INCLUDED */
