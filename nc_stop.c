//--------------------------------------------------------------
//
//	ncurses close down and tidily stop routine
//
//	usage:	nc_stop()
//
//	GNU GPLv3+ licence	ncurses utilities for gxt by Andrew Bennington Jan-2016 <www.benningtons.net>
//
//--------------------------------------------------------------


#include <curses.h>		// for ncurses - screen handling

void nc_stop(void)
  {
    endwin();			// end ncurses
  }
