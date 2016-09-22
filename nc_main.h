//--------------------------------------------------------------
//
// nc = ncurses utilities - for non-GUI screen handling
//
//	GNU GPLv3 licence	GXT by Andrew Bennington 2015 <www.benningtons.net>
//
//--------------------------------------------------------------

#ifndef __GXT_NC_MAIN_INCLUDED__
#define __GXT_NC_MAIN_INCLUDED__

//------------------------------nc key definitions
#define NC_QUIT		0					// Used to notify calling program of menu/screen quit requests
//#define NC_KEY_LEFT	212
//#define NC_KEY_RIGHT	213

//------------------------------nc utilities
void	nc_start(void);					// initialise and start-up ncurses
int		nc_input(char **, char *, int);	// input window management
int		nc_menu(char **, char **);		// menu management
void	nc_message(char *);				// output status message
void	nc_stop(void);					// tidy up and stop ncurses

#endif
