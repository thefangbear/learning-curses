/*
 * =====================================================================================
 *
 *       Filename:  helloworld.c
 *
 *    Description:  hello world ncurses program
 *
 *        Version:  1.0
 *        Created:  01/23/2018 15:01:39
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
	/* initializes terminal in curses mode
	 * this guy needs *at least some* memory
	 * to succeed */
	initscr();

	/* prints on stdscr on current (y,x) coordinates */
	printw("hello world!!");
	/* this is equilvalent to flushing the stream */
	refresh();
	/* endwin() frees out the memory taken by curses.
	 *
	 * Remember to do this, otherwise your terminal goes into mush */
	getch();endwin();
	return 0;
}
