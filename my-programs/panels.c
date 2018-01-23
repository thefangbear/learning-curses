/*
 * =====================================================================================
 *
 *       Filename:  panels.c
 *
 *    Description:  experiments with the panels library
 *
 *        Version:  1.0
 *        Created:  01/23/2018 17:06:22
 *       Revision:  none
 *
 *         Author:  Rui-Jie Fang (rjf), rfang@temple.edu
 *        Company:  Dept. of Computer and Info. Sciences, Temple University
 *		  Copyright: Copyright (c) 2018 The Trustees of Temple University
 *		  Note: A license is included within the project root directory.
 *
 * =====================================================================================
 */
#include <panel.h>
#include <ncurses.h>


int main()
{       WINDOW *my_wins[3];
        PANEL  *my_panels[3];
        int lines = 50, cols = 50, y = 2, x = 4, i;

        initscr();
        cbreak();
        noecho();

        /* Create windows for the panels */
        my_wins[0] = newwin(lines, cols, y, x);
        my_wins[1] = newwin(lines, cols, y + 10, x + 5);
        my_wins[2] = newwin(lines, cols, y + 20, x + 10);

		wprintw(my_wins[0], "Window 0");
		wprintw(my_wins[1], "Window 1");
		wprintw(my_wins[2], "Window 2");
        refresh();
		/*
         * Create borders around the windows so that you can see the effect
         * of panels
         */
        for(i = 0; i < 3; ++i)
                box(my_wins[i], 0, 0);

		mvwprintw(my_wins[0],10,10,"greetings");
		refresh();
		/* Attach a panel to each window */     /* Order is bottom up */
        my_panels[0] = new_panel(my_wins[0]);   /* Push 0, order: stdscr-0 */
        my_panels[1] = new_panel(my_wins[1]);   /* Push 1, order: stdscr-0-1 */
        my_panels[2] = new_panel(my_wins[2]);   /* Push 2, order: stdscr-0-1-2 */

        /* Update the stacking order. 2nd panel will be on top */
        update_panels();

        /* Show it on the screen */
        doupdate();

        getch();
        endwin();
}

