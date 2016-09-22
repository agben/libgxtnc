**GXT**
---
gxt is a range of related projects mainly written in c for use on Linux but designed with portability in mind.  
The gxt name derives from a system called fws (in a hal -> ibm or vms -> wnt kind of way!). I worked on fws for many years but sadly its dependence on openVMS hindered its evolution.  
  
For more on gxt see www.benningtons.net  
  
**GXT library projects**
---
Each themed project provides an object library containing functions used by other gxt projects. Although they could also be incorporated into your own project, either as a whole library or as individual code examples.  
As well as the usual purpose of a function (to re-use code) they are also intended to keep system calls or other non-portable code together in one place. Portability issues can then be addressed (i.e. with compiler flags) within these libraries rather than across an entire project.  
In some cases functions are desgned for use from other languages (e.g. Fortran) to enable access to the wealth of system functionality available to c.  
Please note: In most cases there are well-established and much better functions available in the extended c library. I'm not trying to re-invent the wheel or compete with those versions, I'm merely developing my own as a means of learning to code within Linux.  
  
**libgxtnc**
---
This project provides a wrapper around the basic functionality of ncurses with the aim of:-  

- Keeping all calling code ncurses free and as simple as possible
- Keeping all ncurses code together in this one library, making translation to other frameworks easier(?)
- With a view to providing a compile time option/switch between basic text, ncurses or any available GUI framework
 
Functions are added/improved as and when needed in other gxt projects. Currently these are:-  

- nc_start --- startup and initialise ncurses.
- nc_input --- display a pop-up message and collect user input.
- nc_menu --- display and manage a menu of options.
- nc_message --- display the requested message on screen.
- nc_stop --- tidily close down ncurses.  

This desire to seperate calling program(s) from the complexities of ncurses or of any GUI user interface stems from using the openVMS SMG$ library and then finding code difficult to port to other operating systems.
