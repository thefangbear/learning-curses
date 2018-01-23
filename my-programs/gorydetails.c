/*
 * =====================================================================================
 *
 *       Filename:  gorydetails.c
 *
 *    Description:  some gory details about libncurses
 *
 *        Version:  1.0
 *        Created:  01/23/2018 15:06:34
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

	/* disabling line buffers */
	raw(); /* control chs are directly passed to program w/o a signal */
	cbreak(); /* they get interpreted by terminal */

	/* setting input feedback */
	echo(); /* turns on echoing of input characters */
	noecho(); /* turns off */

	keypad(stdscr, TRUE); /* enable function keys, i.e. F1,F2, arrow keys */

	halfdelay(10); /* wait for input, delay x/10 secs */

	char ch = getch();
	if (ch==KEY_F(1))
		printw("F1 Key pressed");
	else {
		printw("The pressed key is");
		attron(A_BOLD);
		printw("%c",ch);
		attroff(A_BOLD);
	}
	refresh();
	getch();


	endwin();
	return 0;
}
