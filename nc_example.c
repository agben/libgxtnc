//--------------------------------------------------------------
//
//	Example of using libgxtnc library functions
//
//	usage:	./nc_example
//
//	Display a simple menu that allows you to input or display a message.
//
//	GNU GPLv3+ licence	libgxtnc by Andrew Bennington 2016 <www.benningtons.net>
//
//--------------------------------------------------------------


#include <unistd.h>		// for sleep

#include <nc_main.h>	// libgxtnc definitions


char *cpTitle[] =	{	"libgxtnc example Menu",		// Main menu title
						(char *) NULL};

char *cpMenu[] =	{	"1) Input message",
						"2) Display message",
						"!3) Unavailable option",		// the ! marks this option as unavailable
						(char *) NULL};

int main(void)
  {
	int	iOpt;							// selected menu option

#define MESS_S0 30
	char cMessage[MESS_S0] = " ";		// message buffer

	nc_start();											// initilise and startup ncurses screen display

	while ((iOpt=nc_menu(cpTitle,cpMenu)) != NC_QUIT)	// Display and manage menu until requested to quit
	  {
		switch (iOpt)									// Check for menu selection actions
		  {
			case 1:										// Display a message input window
				nc_input(	"Enter your message",		// title
							cMessage,					// input buffer
							MESS_S0-1);					// size
				break;
			case 2:										// Display stored message at bottom of screen
				nc_message(cMessage);
				sleep(2);
				break;
		  }
	  }

	nc_stop();											// tidily shutdown ncurses

	return 0;
  }
