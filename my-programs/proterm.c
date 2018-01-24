/*
 *       Filename:  proterm.c
 *
 *    Description:  proterm - pro-terminal
 *
 *        Version:  1.0
 *        Created:  01/23/2018 15:59:29
 *       Revision:  none
 *
 *         Author:  Rui-Jie Fang (rjf), rfang@temple.edu
 *        Company:  Dept. of Computer and Info. Sciences, Temple University
 *		  Copyright: Copyright (c) 2018 The Trustees of Temple University
 *		  Note: A license is included within the project root directory.
 *
 * =====================================================================================
 */


#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>
#define streq(x,y) (strcmp(x,y)==0)

char * choices[]=
{ "Remote Command Execution", "View System Trace", "Print Logs", "Graphical Visualization (Beta)", "Shell", "Exit", "Version Information" };
char * descriptions[]=
{ "Switch to a remote machine", "Show current status", "Debug! :-)", "Visualize current status of UVR", "Use the ProTerm Shell", "Exit this Menu", "Show help"};
ITEM ** items;
MENU * menu;
ITEM * cur_item;
FILE *fp;
WINDOW * new_window(int height, int width, int start_y, int start_x)
{
	WINDOW * _win;
	_win = newwin(height, width, start_y, start_x);
	box(_win, 0, 0);
	wrefresh(_win);
	return _win;
}

void destroy_window(WINDOW *_win)
{
	wborder(_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(_win);
	delwin(_win);
}
#define ARRAY_SIZE(x) sizeof(x)/sizeof(char*)
#define CTRLD   4


void menu_handle(char *name)
{
	if (streq(name, "Exit")) {
		printw("Exiting this function!");
		free_item(items[0]);
        free_item(items[1]);
        free_menu(menu);

	} else {
		printw("ERROR: The called function %s has not yet been implemented. Called: %s", name);		
	}
}

void show_menu() 
{
		int c,i;

		keypad(stdscr, TRUE);

        int n_choices = ARRAY_SIZE(choices);
        items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

        for(i = 0; i < n_choices; ++i) {
                items[i] = new_item(choices[i], descriptions[i]);
                set_item_userptr(items[i], menu_handle);

		}
		items[n_choices] = (ITEM *)NULL;

        menu = new_menu((ITEM **)items);
        post_menu(menu);
        refresh();
        while((c = getch()) != 'q')
        {   switch(c)
            {   case KEY_DOWN:
                        menu_driver(menu, REQ_DOWN_ITEM);
                                break;
                case KEY_UP:
                                menu_driver(menu, REQ_UP_ITEM);
                                break;
				case 10:
								{
								ITEM *cur;
                                void (*p)(char *);

                                cur = current_item(menu);
                                p = item_userptr(cur);
								p((char *)item_name(cur));
                                pos_menu_cursor(menu);
                                break;

								}
			}
			
        }

        free_item(items[0]);
        free_item(items[1]);
        free_menu(menu);

}

int main(void)
{
	initscr();
	int row, col;
	getmaxyx(stdscr,row,col);
	char input[row];
	const char * display_banner = "> ProTerm Window System v0.1a <";
	const char * owner = "COPYRIGHT (C) 2018 TEMPLE UNIVERSITY";
	mvprintw(0, col/2-strlen(display_banner)/2,display_banner);
	mvprintw(1,col/2-strlen(owner)/2,owner);
	int line=3;
	WINDOW * nwin = NULL;
	memset(input,'\0', row);
	do {
		++line;
		move(line,0);
		printw("> ");
		move(line,2);
		getstr(input);
		char *templine=NULL;
		if(streq(input,"quit")) {
			printw("|-> Bye ~~~");
			endwin();
			return 0;
		} else if (streq(input,"clear")) {
			clear();
			line=0;
			mvprintw(++line,0,"|-> OK");
		} else if (streq(input,"help")) {
			mvprintw(++line,0,"|-> -------------------------------------------");
			mvprintw(++line,0,"|-> ProTerm v1.0 alpha");
			mvprintw(++line,0,"|-> Copyright (C) 2018 Temple University");
			mvprintw(++line,0,"|-> -------------------------------------------");
			mvprintw(++line,0,"|-> quit,clear,help,setbold,unsetbold,createWindow,destroyWindow,printWindow,showMenu,sysExec,fOpen, fClose, fRead, fWrite");
			mvprintw(++line,0,"|-> fInit,gored,goback,setunderline,unsetunderline");
		} else if (streq(input,"")) {
			continue;
		} else if (streq(input,"setbold")) {
			attron(A_BOLD);
			continue;
		} else if (streq(input,"unsetbold")) {
			attroff(A_BOLD);
			continue;
		} else if (streq(input,"setunderline")) {
			attron(A_UNDERLINE);
			continue;
		} else if (streq(input,"unsetunderline")) {
			attroff(A_UNDERLINE);
			continue;
		} else if (streq(input, "gored")) {
			attron(COLOR_RED);
			continue;
		} else if (streq(input,"goback")) {
			attroff(COLOR_RED);
			continue;
		} else if (input[0]=='#') {
			continue;
		} else if ((templine=strstr(input,"createWindow"))!=NULL) {
			mvprintw(++line,0,"|-> createWindow(): %s",templine);
			templine = strchr(input,'w');
			templine+=1;
			while(templine[0]==' ')
				templine+=1;
			if (nwin==NULL) {
				int h,w,sy,sx;
				
				mvprintw(++line,0,"|-> createWindow(): %s", templine);
				sscanf(templine, "%d %d %d %d",&h,&w,&sy,&sx);
				mvprintw(++line,0,
						"|-> createWindow(): Creating window with h=%d, w=%d, startY=%d, startX=%d", h,w,sy,sx);
				nwin = new_window(h,w,sy,sx);
				wprintw(nwin, "Window 1");
				wrefresh(nwin);
			} else {
				mvprintw(++line,0,"|-> createWindow(): Cannot create window; one already present!");
			}
			templine=NULL;
		} else if (strstr(input,"destroyWindow")!=NULL) {
			if (nwin!=NULL) {
				destroy_window(nwin);
				nwin=NULL;
				mvprintw(++line,0,"|-> destroyWindow(): Window successfully destroyed.");
			} else {
				mvprintw(++line,0,"|-> destroyWindow(): Cannot destroy window; NewWindow object is null.");
			}
			templine=NULL;
		} else if ((templine=strstr(input,"printWindow"))!=NULL) {
			if (nwin != NULL) {
				templine=strchr(input,' ');
				while(templine[0]==' ')++templine;
				wprintw(nwin, templine);
				wrefresh(nwin);
			} else {
				mvprintw(++line,0,"|-> printWindow(): Cannot print to window; NewWindow object is null.");
			}
		} else if (strstr(input,"showMenu")!=NULL) {
			mvprintw(++line,0,"|-> Showing menu...");
			show_menu();
		} else if ((templine=strstr(input, "sysExec"))!=NULL) {
			templine=strchr(input,' ');
			while(templine[0]==' ')++templine;
			mvprintw(++line,0,"|-> sysExec(): %s \%", templine);
			system(templine);
		} else if (strstr(input,"fInit")!=NULL) {
			fp = NULL;
			mvprintw(++line,0,"|-> fInit(): Prepared for side effects.");
		} else if ((templine=strstr(input,"fOpen"))!=NULL) {
			if (fp!=NULL)
				mvprintw(++line,0,"|-> fOpen(): Unable to open stream; existing FilePointer object.");
			else {
				templine=strchr(input,' ');
				while(templine[0]==' ')++templine;
				mvprintw(++line,0,"|-> fOpen(): %s",templine);
				fp=fopen(templine, "rw");
				mvprintw(++line,0,"|-> %p, rw", fp);
			}
		} else if ((templine=strstr(input,"fClose"))!=NULL) {
			if (fp!=NULL)
				fclose(fp);
			fp=NULL;
			mvprintw(++line,0,"|-> fClose(): Successfully closed file descriptor.");
		} else if ((templine=strstr(input,"fWrite"))!=NULL) {
			templine=strchr(input,' ');
			while(templine[0]==' ')++templine;
			if (fp!=NULL) {
				mvprintw(++line,0,"|-> fWrite(): Writing (%s) to FilePointer object at %p.", templine, fp);
				fputs(templine,fp);
			} else
				mvprintw(++line,0,"|-> fWrite(): Cannot write to empty stream. (%s)", templine);	
		} else if ((templine=strstr(input,"fRead"))!=NULL) {
			templine=strchr(input,' ');
			while(templine[0]==' ')++templine;
			int read_size = atoi(templine);
			if (fp!=NULL) {
				mvprintw(++line,0,"|-> fRead(): Opening up a buffer of %d CharacterObjects from FilePointer@%p", read_size, fp);
				char * _buf = malloc(read_size);
				fgets(_buf, read_size, fp);
				mvprintw(++line,0,"|-> New *CharacterObject[%d]:=%s.",read_size,_buf);
				free(_buf);
			} else
				mvprintw(++line,0,"|-> fRead(): Cannot open buffer of %d CharacterObjects because FilePointer is empty.",read_size);
		} else {
			mvprintw(++line,0,"|-> Unknown command: %s \%",input);
		}
		refresh();
	} while (1);

	endwin();
	return 0;
}

