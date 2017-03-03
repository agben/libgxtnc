//--------------------------------------------------------------
//
//	utilities for libgxtnc ncurses functions
//
//	GNU GPLv3 licence	GXT and libgxtnc by Andrew Bennington Mar-2016 <www.benningtons.net>
//
//--------------------------------------------------------------

#include <nc_main.h>		// for gxt ncurses functions

//--------------------------------------------------------------
//	determine number of lines in a string and the max line length
//
//	usage:	nc_str = nc_string(string);
//		where:
//			string points to a null terminated string that may contain newlines (\n).
//		returns:
//			nc_str structure containing ints for iLineCount and iMaxLineWidth
//--------------------------------------------------------------

nc_str nc_string(char *cpString)
  {
    int i, j = 0;

	nc_str ncs;


	ncs.iLineCount=0;			// count of lines in string
    ncs.iMaxLineWidth=0;		// max line width in string

	for (i=0; ; i++)			// check through string to count lines and find max line width
      {
		if (cpString[i] == '\n' || cpString[i] == '\0')
		  {
			if (j > ncs.iMaxLineWidth) ncs.iMaxLineWidth=j;	// widest line?
			ncs.iLineCount++;								// count lines
			if (cpString[i] == '\0') break;					// end of string?
			j=0;
		  }
		else
			j++;						// count length of each line
      }

	return ncs;
  }
