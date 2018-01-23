/*
 * =====================================================================================
 *
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
#define streq(x,y) (strcmp(x,y)==0)

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
			mvprintw(++line,0,"|-> quit,clear,help,setbold,unsetbold,createWindow,destroyWindow");
		} else if (streq(input,"")) {
			continue;
		} else if (streq(input,"setbold")) {
			attron(A_BOLD);
			continue;
		} else if (streq(input,"unsetbold")) {
			attroff(A_BOLD);
			continue;
		} else if (input[0]=='#') {
			continue;
		} else if ((templine=(input,"createWindow"))!=NULL) {
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
			} else {
				mvprintw(++line,0,"|-> createWindow(): Cannot create window; one already present!");
			}
			templine=NULL;
		} else if (strstr(input,"destroyWindow")!=NULL) {
			if (nwin!=NULL) {
				destroy_window(nwin);
				mvprintw(++line,0,"|-> destroyWindow(): Window successfully destroyed.");
			} else {
				mvprintw(++line,0,"|-> destroyWindow(): Cannot destroy window; NewWindow object is null.");
			}
			templine=NULL;
		} else {
			mvprintw(++line,0,"|-> Unknown command: %s \%",input);
		}
		refresh();
	} while (1);

	endwin();
	return 0;
}

