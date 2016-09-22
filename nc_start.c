//--------------------------------------------------------------
//
//	ncurses start and initialise routine
//
//	usage:	nc_start()
//
//	GNU GPLv3+ licence	ncurses utilities by Andrew Bennington Jan-2016 <www.benningtons.net>
//
//--------------------------------------------------------------

#include <curses.h>							// for ncurses - screen handling

void nc_start(void)
  {
    initscr();								// initialise ncurses
    start_color();							// enable use of colour
    cbreak();								// keyboard input mode without waiting for enter
    noecho();								// don't echo keys to the screen
    keypad(stdscr, TRUE);					// enable function keys, cursor keys and keypad
    init_pair(1, COLOR_RED, COLOR_BLACK);	// setup 1st colour pairing, COLOUR_PAIR(1) for title
    init_pair(2, COLOR_GREEN, COLOR_BLACK);	//										for menu items
    init_pair(3, COLOR_CYAN, COLOR_BLACK);	//										for unavailable menu items
  }
