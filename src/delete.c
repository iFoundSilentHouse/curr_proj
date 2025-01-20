#include "delete.h"
#include "io.h"
#include "layout_handlers.h"
#include <ncurses.h>
#include <string.h>

bool you_sure_win(char *pr_name) {
    WINDOW *you_sure;
    char answer;
    you_sure = create_newwin_in_middle(4, 18+strlen(pr_name));
    mvwprintw(you_sure, 1, 1, "Delete project %s?", pr_name);
    mvwprintw(you_sure, 2, 7+strlen(pr_name)/2, "Y/n");
    answer = wgetch(you_sure);
    if(answer == 'Y' || answer == 'y')
        return(1);
    if(answer == 'N' || answer == 'n')
        return(0);
    return(you_sure_win(pr_name));
}

bool del(int pr_num, char *path_tosave) {
    // ll = linked list
    FILE *ll1_stream, *ll2_stream;
    project ll1, ll2;
    ll1_stream = fopen(path_tosave, "rb+");
    fseek(ll1_stream, pr_num*sizeof(project), SEEK_SET);
    ulong chosen_exists = fread(&ll1, sizeof(project), 1, ll1_stream);
    if(!chosen_exists) {
        fclose(ll1_stream);
        return(0);
    }
    
    if(!you_sure_win(ll1.name)) {
        fclose(ll1_stream);
        return(0);
    }

    ll2_stream = fopen(path_tosave, "r");
    fseek(ll2_stream, (pr_num+1)*sizeof(project), SEEK_SET);
    ulong chosen_not_last = fread(&ll2, sizeof(project), 1, ll2_stream);
    
    if (!chosen_not_last) {
        truncate(path_tosave, pr_num*sizeof(project));
        fclose(ll1_stream);
        fclose(ll2_stream);
        return(1);
    }
/*
    while(chosen_not_last) {
        fwrite(&ll2, sizeof(project), 1, ll1_stream);
        ulong chosen_not_last = fread(&ll2, sizeof(project), 1, ll2_stream);
    }
    truncate(path_tosave, pr_num*sizeof(project));        
    fclose(ll1_stream);
    fclose(ll2_stream);
    return(1);*/
};