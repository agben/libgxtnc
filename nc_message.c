//--------------------------------------------------------------
//
//	ncurses message output
//
//	usage:	nc_message(message);
//		where:	message is to be displayed at the centre bottom of the screen
//
//	GNU GPLv3 licence	ncurses for gxt by Andrew Bennington 2016 <www.benningtons.net>
//
//--------------------------------------------------------------

#include <curses.h>		// for ncurses - screen handling
#include <string.h>		// for strlen


void nc_message(char *cpMess)
  {
    move(LINES-1, 0);
    clrtoeol();													// clear bottom line of screen
    mvprintw(LINES-1, ((COLS-strlen(cpMess))/2), "%s", cpMess);	// output message
    refresh();
  }
