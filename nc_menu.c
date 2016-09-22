//--------------------------------------------------------------
//
//	ncurses menu control
//
//	usage:	selection = nc_menu(title, menu);
//		where:	title points to an array of details to display at the top of the menu
//				menu points to an array of menu items
//		include: calling programs will need to include nc_main.h for function and data definitions
//
//	The menu will be displayed in the centre of an otherwise clear screen
//	Any menu item starting with a ! will be displayed but unavailable for selection
//
//	Using the menu:
//		Cursor keys to move the selection up/down.
//		For large lists use Page-up and Page-down keys to scroll.
//		Confirm menu selection by pressing the Return key.
//			Or by pressing the line number of the required menu item.
//		Use F1 to quit a menu (displayed at bottom of screen).
//
//	returns:
//		menu selection - menu item/row number
//		or NC_QUIT to notify calling program of the request.
//
//	GNU GPLv3 licence	ncurses utilities for GXT by Andrew Bennington Jan-2016 <www.benningtons.net>
//
//--------------------------------------------------------------

#include <ctype.h>		// common I/O functions like toupper()
#include <curses.h>		// ncurses library
#include <menu.h>		// ncurses menu library
#include <stdlib.h>		// memory management
#include <string.h>		// for strlen

#include <nc_main.h>	// gxt ncurses functions
#include <ut_error.h>	// error log and debug macros


int nc_menu(char **cpTitle, char **cpMenu)
  {
    MENU *ncMenu;				//menu handle
    ITEM **ncMenuItems;			//items to add to menu
    WINDOW *ncMenuWin;			//menu's window handle

    int i, j;
    int	iR, iC;					// row and column counts
    int iOpt = -1;				// selected menu option
    int iMenuSize = 0;			// count of menu items
    int iMenuWidth = 0;			// max width of menu items
    int iTitleSize = 0;			// count of lines to display in the title
    int iTitleWidth = 0;		// max width of title


    nc_message("Press F1 to quit");

    while (cpTitle[iTitleSize] != NULL)
      {
		j=strlen(cpTitle[iTitleSize]);
		if (j>iTitleWidth) iTitleWidth=j;	// find the widest title line
		iTitleSize++;						// how many title items?
      }

    while (cpMenu[iMenuSize] != NULL)
      {
		j=strlen(cpMenu[iMenuSize]);
		if (j>iMenuWidth) iMenuWidth=j;		// find the widest menu line
		iMenuSize++;						// how many menu items?
      }

    ut_check((ncMenuItems=(ITEM **) calloc(iMenuSize+1,
    				   sizeof(ITEM *))) != NULL,
    				   "memory");			// allocate and clear memory for menu

    for (i=0; i < iMenuSize; ++i)
	  {
		if (cpMenu[i][0] == '!')			// a leading ! marks an unavailable option
		  {
			ncMenuItems[i]=new_item(   		// load menu items into ncurses
					&cpMenu[i][1],			// but don't display the leading '!'
					NULL);
			item_opts_off(ncMenuItems[i], O_SELECTABLE);	// mark item as unavailable
		  }
		else
		  {
			ncMenuItems[i]=new_item(   		// load menu items into ncurses
					cpMenu[i],
					NULL);
		  }
	  }

    iR=((iMenuSize+iTitleSize+3) < LINES) ? iMenuSize+iTitleSize+3 : LINES;	// determine total height of menu
    iC=((iMenuWidth+6) > iTitleWidth+4) ? iMenuWidth+6 : iTitleWidth+4;	// determine the total width of the menu
    if (iC > COLS) iC=COLS;

    ncMenuWin=newwin(iR, iC, ((LINES-iR)/2), ((COLS-iC)/2));	// create window for menu in centre of screen
    keypad(ncMenuWin, TRUE);				// enable function keys, cursor keys and keypad

    ncMenu=new_menu((ITEM **)ncMenuItems);	// create a new menu
    set_menu_win(	ncMenu,
    			ncMenuWin);					// set a window for our menu
    set_menu_sub(	ncMenu,
			derwin(	ncMenuWin,				// define a sub-window for the menu
				iR-(iTitleSize+2),
				iC-2,
				iTitleSize+2,
				1));
    set_menu_format(	ncMenu,  			// setting menu display size to allow scrolling
			iR-(iTitleSize+2),				// menu rows to display
			1);								// menu columns (if using multi columns)

    menu_opts_off(ncMenu, O_NONCYCLIC);		// allow wrapping from bottom/top of menu

    set_menu_fore(ncMenu, COLOR_PAIR(1)|A_REVERSE);		// Set menu colours for, selected item
    set_menu_back(ncMenu, COLOR_PAIR(2));				//			other menu items
    set_menu_grey(ncMenu, COLOR_PAIR(3));				//			unavailable menu items

    set_menu_mark(ncMenu, ">> ");			// set a prompt to show current selection

    box	(ncMenuWin, 0, 0);					// box entire menu window

    wattron(  ncMenuWin, COLOR_PAIR(1));			//Use colour for title
    for (i=0; i < iTitleSize; ++i)
		mvwprintw(ncMenuWin, (i+1), (iTitleWidth < iC)?((iC-iTitleWidth)/2):2, cpTitle[i]);
    wattroff( ncMenuWin, COLOR_PAIR(1));

    mvwaddch( ncMenuWin, (iTitleSize+1), 0,	ACS_LTEE);	// box title from rest of menu
    mvwhline( ncMenuWin, (iTitleSize+1), 1,	ACS_HLINE, iC-2);
    mvwaddch( ncMenuWin, (iTitleSize+1), iC-1,	ACS_RTEE);

    post_menu(ncMenu);
    wrefresh( ncMenuWin);

    while ((iOpt=toupper(wgetch(ncMenuWin))) != KEY_F(1))	// Get keystroke and convert to uppercase - F1 to quit
	  {
		switch (iOpt)						// first check for menu control actions
		  {
			case KEY_DOWN:					// cursor down
				menu_driver(ncMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:					// cursor up
				menu_driver(ncMenu, REQ_UP_ITEM);
				break;
			case KEY_NPAGE:					// scroll down
				menu_driver(ncMenu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:					// scroll up
				menu_driver(ncMenu, REQ_SCR_UPAGE);
				break;
			case 10:						// enter key so select current item
				iOpt=item_index(current_item(ncMenu))+1;
				break;
			default:
				iOpt-='0';					// Typed menu selection number?
		  }

		if (iOpt > 0 && iOpt <= iMenuSize)
			if (cpMenu[iOpt-1][0] != '!') break;		//valid selection?
	  }

    if (iOpt== KEY_F(1)) iOpt=NC_QUIT;		// Convert F1 so calling program doesn't need to deal with keydefs

error:										//Tidy-up and close
	unpost_menu(ncMenu);
	for (i=0; i < iMenuSize; ++i) free_item(ncMenuItems[i]);
	free_menu(ncMenu);
	delwin( ncMenuWin);						// remove menu from display
	touchwin(stdscr);						// touch and refresh screen to actually clear menu
	refresh();

	return iOpt;
  }
