/*
Invierno SHELL.
Version 0.0.5 ALPHA
Copyright 2018 - Joaquin Manuel Crespo
Licensed in GeneralPublicLicense v3.

This file is part of ProyectoInvierno.
ProyectoInvierno is free software, you can use,
redistribute it and/or modify it under the terms
of the GNU General Public License as published by 
Free Software Foundation, either version 3 of the license.


Developed by ShyanJMC initially at 2018.
*/

/* 
 * Headers file for provide functions.
 */
#include<stdio.h>
#include<string.h>
#include<ncurses.h>

/* Welcome message. */
char wmessage[]="Invierno Shell UI.\n";

int main(int a, char **b){
	/* Import the extern variable. */
	extern char wmessage[];
	/* Create the variables for locate the number of rows and columms. */
	int row, col;
	/* Initialize the ncurses screen. */
	initscr();
	/* Line buffering disabled. */
	raw();
	/* Initialize the support for all keys in keyboard.
	 * stdscr = standard screen */
	keypad(stdscr, TRUE);
	
	/* Get the number of columms and rows of the screen. */
	getmaxyx(stdscr,row,col);
	
	/* Print window message. At top,middle screen. It use at first argument
	 1 because specify the first row. */
	mvprintw(1,(col-strlen(wmessage))/2,"%s",wmessage);
	mvprintw(2,(col-strlen(wmessage))/2,"==================");

	

	/* Print from the ncurses window to standar output. */
	refresh();
	/* Wait for some imput. */
	getch();
	/* End the ncurses window. */
	endwin();

	return 0;
}
