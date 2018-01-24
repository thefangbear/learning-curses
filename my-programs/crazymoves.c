/*
 * =====================================================================================
 *
 *       Filename:  crazymoves.c
 *
 *    Description:  move around like crazy
 *
 *        Version:  1.0
 *        Created:  01/23/2018 15:21:27
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
#include <math.h>
#include <stdlib.h>
int getrand(int rl, int rh)
{
	return rand()%(rl+1)+rh;
}
int main(void) {
	srand(time(NULL));
	initscr();
	
	int x=0,y=0,rclr=1;
	start_color();
	attron(A_BOLD);
	init_pair(1,COLOR_BLUE,COLOR_RED);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_GREEN,COLOR_RED);
	init_pair(4,COLOR_BLUE,COLOR_GREEN);
	init_pair(5,COLOR_YELLOW,COLOR_BLUE);
	init_pair(6,COLOR_MAGENTA,COLOR_CYAN);
	init_pair(7,COLOR_WHITE,COLOR_BLACK);
	init_pair(8,COLOR_RED,COLOR_MAGENTA);
	while (1) {
		x = rand() % (100 + 1 -0)+0;
		y= rand() %(150+1-0)+0;
		mvprintw(y,x," ^(*____*)~");
		wbkgd(stdscr,COLOR_PAIR(rand() % (8+1-1)+1));
		refresh();
//		sleep(1);
		if (halfdelay(10)=='q') {endwin();return 0;}
	
		x=getrand(30, 50);
		y=getrand(30, 50);
		char ch = addch('A' | A_BOLD | A_UNDERLINE | COLOR_RED);
		mvaddch(x,y,ch);
		x=getrand(40,60);
		y=getrand(40,60);
		mvaddch(x,y,ch);
		x=getrand(50,70);
		y=getrand(50,70);
		mvaddch(x,y,ch);
	}

	endwin();

	return 0;
}

