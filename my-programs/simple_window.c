/*
 * =====================================================================================
 *
 *       Filename:  simple_window.c
 *
 *    Description:  a very simple window
 *
 *        Version:  1.0
 *        Created:  01/23/2018 17:29:51
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

int main(void)
{
	initscr();

	WINDOW *nwin = newwin(10, 10, 10, 10);

	box(nwin, 0, 0);

	wprintw(nwin, "This is a Window");

	printw("hello");

	refresh();

	wrefresh(nwin);

	getch();

	delwin(nwin);

	endwin();
}

