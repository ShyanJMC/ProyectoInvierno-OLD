/*
Invierno SHELL.
Version 0.0.1 ALPHA
Licensed in GPL v3.

Developed by ShyanJMC.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Store for information about the program.
1 is errror.
0 is OK.
Is in the order in wich the program checks.
*/
struct Information {
	int core_files;
	int environment;
	int core_invierno_bash;
}Init1;

/*
A simple check to corroborate if the Bash's core utilities are
inside the Invierno's directory.
*/
int simple_check(){
	Init1.core_files = system("/var/lib/invierno/core/ls . > /dev/null");
	if (Init1.core_files != 0){
		printf("[FAIL]\tCore failes are damaged or missing.\n");
		return Init1.core_files = 1;
	}
	else {
		printf("[OK]\tCore files.\n");
		return Init1.core_files = 0;
	}
}

/*
Check the configuration of the environment.

*/
int environment(){
	 printf("Checking environment file.\n");
	 Init1.environment  = system("/var/lib/invierno/core/ls /etc/invierno > /dev/null");
	if (Init1.environment != 0){
		printf("[FAIL]\tInvierno configuration missing.\n");
		return 1;
	}
	printf("[OK]\tEnvironment file.\n");
	 printf("Checking if Bash is enable for the user.\n");
	 Init1.core_invierno_bash = system("/var/lib/invierno/core/grep BSH=0 /etc/invierno > /dev/null");
	 if(Init1.core_invierno_bash != 0){
	 	printf("[OK]\tBash for user is disabled, using ZSH.\n");
	 }
	 else {
	 	printf("[OK]\tBash enabled.\n");
	 }
return 0;
}

/*
Execute the functions and check the return of the same.
*/
int main( int first_arg, char **second_arg){
	printf("Starting Invierno.\n");
	printf("Checking core programs.\n");
    simple_check();
	if (Init1.core_files != 0){
		return 1;
	}
	environment();
	if (Init1.environment != 0){
		return 1;
	}
    system("/var/lib/invierno/core/bash --init-file /etc/inviernorc");
	return 0;
}
