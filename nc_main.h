//--------------------------------------------------------------
//
// nc = ncurses utilities - for non-GUI screen handling
//
//	GNU GPLv3 licence	GXT by Andrew Bennington 2015 <www.benningtons.net>
//
//--------------------------------------------------------------

#ifndef __GXT_NC_MAIN_INCLUDED__
#define __GXT_NC_MAIN_INCLUDED__

//------------------------------nc parameters
#define NC_QUIT		0					// Used to notify calling program of menu/screen quit requests
//#define NC_KEY_LEFT	212
//#define NC_KEY_RIGHT	213

//------------------------------nc data structures
typedef struct
  {
	int iLineCount;
	int	iMaxLineWidth;
  } nc_str;				// used by nc_string() to determine multi-line string characteristics

//------------------------------nc utilities
int		nc_input(char *, char *, int);	// input window management
int		nc_menu(char *, char **);		// menu management
void	nc_message(char *);				// output status message
void	nc_start(void);					// initialise and start-up ncurses
void	nc_stop(void);					// tidy up and stop ncurses
nc_str	nc_string(char *);				// determine multi-line string characteristics

#endif
