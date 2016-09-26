//--------------------------------------------------------------
//
//	Example of using libgxtnc library functions
//
//	usage:	./nc_example
//
//	GNU GPLv3+ licence	libgxtnc by Andrew Bennington 2016 <www.benningtons.net>
//
//--------------------------------------------------------------


#include <stdlib.h>
#include <unistd.h>		// for sleep

#include <nc_main.h>	// NC ncurses utility definitions


#define NC_INPUT_TITLE_P0	2				// offset for message input title

char *cpTitle[] =	{	"libgxtnc example Menu",		// Main menu title
						(char *) NULL,
						"Enter your message",			// Message input title
						(char *) NULL};

char *cpMenu[] =	{	"1) Input message",
						"2) Display message",
						(char *) NULL};

int main(void)
  {
//	int	i;
	int	iOpt;			// selected menu option

#define MESS_S0 30
	char cMessage[MESS_S0];			// message buffer

	nc_start();											// initilise and startup ncurses screen display

	while ((iOpt=nc_menu(cpTitle,cpMenu)) != NC_QUIT)	// Display and manage menu until requested to quit
	  {
		switch (iOpt)									// Check for menu selection actions
		  {
			case 1:
				nc_input(	cpTitle+NC_INPUT_TITLE_P0,	// title
							cMessage,					// input buffer
							MESS_S0-1);					// size
				break;
			case 2:
				nc_message(cMessage);
				sleep(2);
				break;
		  }
	  }
	return 0;
  }
