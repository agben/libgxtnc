//--------------------------------------------------------------
//
//	ncurses single string input in a seperate window
//
//	usage:	i = nc_input(title, buffer, size);
//		where:
//			title points to a null terminated string to display at the top of the window.
//				this string may contain newlines (\n) for a multi-line title.
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

#include <nc_main.h>		// for gxt ncurses functions

int nc_input(char *cpTitle, char *cpBuff, int iMax)
  {
    WINDOW *ncInputWin;			//input window handle

    int i, j = 0;
    int	iR, iC;					// row and column counts
	char *cp;


	nc_str nct = nc_string(cpTitle);	// check through the title to count lines and find max line width

    iR=((nct.iLineCount+4) < LINES) ? nct.iLineCount+4 : LINES;	// determine total height of the window
    iC=(iMax > nct.iMaxLineWidth) ? iMax : nct.iMaxLineWidth;	// determine the total width of the window
	iC+=2;
    if (iC > COLS) iC=COLS;

    ncInputWin=newwin(iR, iC, ((LINES-iR)/2), ((COLS-iC)/2));	// create window in centre of screen
    keypad(ncInputWin, TRUE);									// enable function keys, cursor keys and keypad

    box	(ncInputWin, 0, 0);										// box entire window

	wattron(ncInputWin, COLOR_PAIR(1));							//Use colour for title
	cp=cpTitle;
	for (i=0; i < nct.iLineCount; ++i)							// output each title line seperately for neatness
	  {
		j=0;
		while (cp[j] != '\n' && cp[j] != '\0') j++;				// find length of each line
		mvwprintw(ncInputWin, (i+1),
			(j < iC)?((iC-j)/2):2, "%.*s", j, cp);
		cp+=j+1;
	  }
    wattroff( ncInputWin, COLOR_PAIR(1));

    mvwaddch( ncInputWin, (nct.iLineCount+1), 0,	ACS_LTEE);	// box title from rest of window
    mvwhline( ncInputWin, (nct.iLineCount+1), 1,	ACS_HLINE, iC-2);
    mvwaddch( ncInputWin, (nct.iLineCount+1), iC-1,	ACS_RTEE);

    wrefresh( ncInputWin);

    echo();
    mvwgetnstr(ncInputWin, (nct.iLineCount+2), 1, cpBuff, iMax);	//Allow user to input a string
    noecho();

    delwin(ncInputWin);											// remove window
    touchwin(stdscr);											// touch and refresh screen to actually clear menu
    refresh();

    return 0;
  }
