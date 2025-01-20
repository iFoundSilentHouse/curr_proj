#include "io.h"


/* Default savfile path & code to access custom way through terminal arguments*/
char *get_savfile_path(int argc,char *argv[]) {
    // TODO: manupulate argc&argv

    // default savefile path
    char *savfile_path = getenv("HOME"); // linux-only
    strcat(savfile_path, "/.curr_proj");

    return savfile_path;
}