//--------------------------------------------------------------
//
//	ncurses single string input in a seperate window
//
//	usage:	i = nc_input(title, buffer, size);
//		where:
//			title points to an array of details to display at the top of the window
//			buffer points to the input string
//			size is the max size of input to avoid overflows
//
//		The input window will be displayed in the centre of an otherwise clear screen
//
//		returns:
//			0 if ok
//
//	GNU GPLv3 licence	GXT and libgxtnc by Andrew Bennington Jan-2016 <www.benningtons.net>
//
//--------------------------------------------------------------

#include <curses.h>			// for ncurses - screen handling
#include <string.h>			// for strlen

#include <nc_main.h>		// for gxt ncurses functions

int nc_input(char **cpTitle, char *cpBuff, int iMax)
  {
    WINDOW *ncInputWin;			//input window handle

    int i, j;
    int	iR, iC;					// row and column counts
    int iTitleSize = 0;			// count of lines to display in the title
    int iTitleWidth = 0;		// max width of title


    while (cpTitle[iTitleSize] != NULL)
      {
		j=strlen(cpTitle[iTitleSize]);
		if (j>iTitleWidth) iTitleWidth=j;						// find the widest title line
		iTitleSize++;											// how many title lines?
      }

    iR=((iTitleSize+4) < LINES) ? iTitleSize+4 : LINES;			// determine total height of the window
    iC=(iMax > iTitleWidth) ? iMax : iTitleWidth;				// determine the total width of the window
	iC+=2;
    if (iC > COLS) iC=COLS;

    ncInputWin=newwin(iR, iC, ((LINES-iR)/2), ((COLS-iC)/2));	// create window in centre of screen
    keypad(ncInputWin, TRUE);									// enable function keys, cursor keys and keypad

    box	(ncInputWin, 0, 0);										// box entire window

    wattron(  ncInputWin, COLOR_PAIR(1));						//Use colour for title
    for (i=0; i < iTitleSize; ++i)
	  {
		mvwprintw(ncInputWin, (i+1),
		(iTitleWidth < iC)?((iC-iTitleWidth)/2):2, cpTitle[i]);
	  }
    wattroff( ncInputWin, COLOR_PAIR(1));

    mvwaddch( ncInputWin, (iTitleSize+1), 0,	ACS_LTEE);		// box title from rest of window
    mvwhline( ncInputWin, (iTitleSize+1), 1,	ACS_HLINE, iC-2);
    mvwaddch( ncInputWin, (iTitleSize+1), iC-1,	ACS_RTEE);

    wrefresh( ncInputWin);

    echo();
    mvwgetnstr(ncInputWin, (iTitleSize+2), 1, cpBuff, iMax);	//Allow user to input a string
    noecho();

    delwin(ncInputWin);											// remove window
    touchwin(stdscr);											// touch and refresh screen to actually clear menu
    refresh();

    return 0;
  }
