/*
 *	This program is part of ProyectoInvierno
 *	Copyleft by Joaquin Manuel Crespo.
 *	GPLv3
 *	github.com/ShyanJMC/ProyectoInvierno
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
