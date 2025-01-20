#include "add.h"
#include "io.h"
#include "colors.h"

static char* trim_tr_whitespaces (char *str)
{
    char *end;
    // trim leading space
    while(isspace(*str)) {
        str++;
    }
    // if all spaces, return
    if(*str == '\0') {
        return str;
    }
    // trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) {
        --end;
    }
    *(end+1) = '\0';

    return str;
}

void addproj(char *path_tosave) {
    WINDOW *addwin;
    int max_w = getmaxx(stdscr);
    addwin = create_newwin(12, max_w-2, 1, 2);

    FORM *addproj_form;
    FIELD *addproj_fields[5];
    char *buffers[4] = {"project name", "used tech", "description", "shell command to open"};

    addproj_fields[0] = new_field(1, max_w-5, 0, 0, 0, 0);
	addproj_fields[1] = new_field(1, max_w-5, 2, 0, 0, 0);
	addproj_fields[2] = new_field(2, max_w-5, 4, 0, 0, 0);
	addproj_fields[3] = new_field(1, max_w-5, 7, 0, 0, 0);
	addproj_fields[4] = NULL;

    for (int i = 0; i < sizeof(addproj_fields)/sizeof(addproj_fields[0]) -1; i++) {
        set_field_buffer(addproj_fields[i], 0, buffers[i]);
        set_field_opts(addproj_fields[i], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	    set_field_back(addproj_fields[i], A_UNDERLINE);
    }
    
    addproj_form = new_form(addproj_fields);
	set_form_win(addproj_form, addwin);
    set_form_sub(addproj_form, derwin(addwin, 8, max_w-4, 1, 1));
	post_form(addproj_form);
    
    mvwaddstr(addwin, 10, 1, "Edit options. q: quit without saving; Enter: add with this options");
	
    refresh();
	wrefresh(addwin);

    int ch = 0;
    keypad(addwin, true);
    curs_set(1);
    while(ch != 'Q' && ch != 'q' && ch != '\n') { 
            switch (ch) {
            case KEY_DOWN:
                form_driver(addproj_form, REQ_NEXT_FIELD);
                form_driver(addproj_form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(addproj_form, REQ_PREV_FIELD);
                form_driver(addproj_form, REQ_END_LINE);
                break;
            case KEY_LEFT:
                form_driver(addproj_form, REQ_PREV_CHAR);
                break;
            case KEY_RIGHT:
                form_driver(addproj_form, REQ_NEXT_CHAR);
                break;
            // Delete the char before cursor
            case KEY_BACKSPACE:
                form_driver(addproj_form, REQ_DEL_PREV);
                break;
            // Delete the char under the cursor
            case KEY_DC:
                form_driver(addproj_form, REQ_DEL_CHAR);
                break;
            case KEY_HOME:
                form_driver(addproj_form, REQ_BEG_LINE);
                break;
            case KEY_END:
                form_driver(addproj_form, REQ_END_LINE);
                break;
            default:
                form_driver(addproj_form, ch);
                break;
        }
        wrefresh(addwin);
        ch = wgetch(addwin);
    }

    if (ch == '\n') {
        form_driver (addproj_form, REQ_VALIDATION);
        project new;
        // adding
        strcpy(new.name, trim_tr_whitespaces(field_buffer(addproj_fields[0], 0)));
        strcpy(new.tech, trim_tr_whitespaces(field_buffer(addproj_fields[1], 0)));
        strcpy(new.desc, trim_tr_whitespaces(field_buffer(addproj_fields[2], 0)));
        strcpy(new.open, trim_tr_whitespaces(field_buffer(addproj_fields[3], 0)));
        // color choice
        new.color = choose_color_win();
        
        FILE *savfile = fopen(path_tosave, "a");
        fwrite(&new, sizeof(project), 1, savfile);
        rewind(savfile);
    }

    destroy_win(addwin);
    unpost_form(addproj_form);
    for(int i=0; i<=4; i++) {
        free_field(addproj_fields[i]);
    }
    curs_set(0);
}