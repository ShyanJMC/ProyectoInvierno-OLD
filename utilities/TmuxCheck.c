/*
Invierno SHELL Tmux's check file.
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

#include<stdio.h>
#include<stdlib.h>

int main(){
	int var1;
	var1 = system("ps aux | grep tmux | grep -Ev 'grep|man|vi|vim|nano'");
	if(var1 !=0){
		system("clear");
		system("tmux");
	}
	return 0;
}
