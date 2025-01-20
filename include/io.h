#ifndef IO_H
#define IO_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* projects struct rule
   It's serialized so project should be reworked if this struct'd been changed */
typedef struct{
    char name[50];
    // list and description of used technology
    char tech[100];
    // description of project itself
    char desc[300];
    char open[150];
    // support of only 2^8=256 colors
    uint8_t color;
} project;

extern char *savfile_path;
char *get_savfile_path(int argc,char *argv[]);

#endif