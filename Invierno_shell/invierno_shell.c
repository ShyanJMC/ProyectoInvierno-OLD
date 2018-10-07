/*
Invierno SHELL.
Version 0.0.2 ALPHA
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
Are in the order in wich the program execute.
*/
struct Information {
	int core_files;
	int environment;
	int core_invierno_bash;
	int internal_ip_address;
	int docker;
	int invierno_container;
	int updated;
}Init1;

/*
A simple check to corroborate if the Bash's core utilities are
inside the Invierno's directory.
*/
int simple_check(){
	Init1.core_files = system("/var/lib/invierno/core/ls . > /dev/null");
	if (Init1.core_files != 0){
		fprintf(stderr,"[FAIL]\tCore failes are damaged or missing.\n");
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
		fprintf(stderr,"[FAIL]\tInvierno configuration missing.\n");
		return 1;
	}
	printf("[OK]\tEnvironment file.\n");
	 printf("Checking if Bash is enable for the user.\n");
	 Init1.core_invierno_bash = system("/var/lib/invierno/core/grep BSH=0 /etc/invierno > /dev/null");
	 if(Init1.core_invierno_bash != 0){
	 	fprintf(stderr,"[FAIL]\tBash for user is disabled.\n");
	 	return 1;
	 }
	 else {
	 	printf("[OK]\tBash enabled.\n");
	 }
return 0;
}

/*
Checks docker and start it.
After a successful start, check the configuration
*/
int docker_init (){
    int temporal,
    	  temporal2;
    printf("Enabling and starting docker.\n");
    temporal = system("systemctl start docker > /dev/null && systemctl enable docker > /dev/null");
    if (temporal != 0){
        fprintf(stderr,"[FAIL]\tDocker start error.\n");
        Init1.docker = 1;
        return 1;
    }
    else{
    	printf("[OK]\tDocker started.\n");
    	Init1.docker = 0;
    	printf("Checking invierno's container configuration.\n");
    	temporal2 = system("/var/lib/invierno/core/grep DCK=0 /etc/invierno > /dev/null");
    	if (temporal2 != 0){
    		fprintf(stderr,"[FAIL]\tInvierno's container disabled.\n");
    		Init1.invierno_container = 1;
    		return 1;
    	}
    	else{
    		printf("[OK]\tInvierno's container enabled. Checking and building.\n");
    		Init1.invierno_container = 0;
    	}
    }
    return 0;
}

/*
Upgrade the system.
Is very simple but is very neccesary keep the system updated with
the last security updates.
*/

int update(){
	int buffer;
	printf("Updating the system.\n");
	buffer = system("yes | pacman -Syu > /dev/null 2> /dev/null");
	if (buffer != 0){
		fprintf(stderr,"[FAIL]\tError to update the system.\n");
		Init1.updated = 1;
	}
	else {
		printf("[OK]\tSystem updated.\n");
		Init1.updated = 0;
	}
	return 0;
}

/*
Execute the functions and check the return of the same.
*/
int main( int first_arg, char **second_arg){
	system("clear");
	printf("Starting Invierno.\n");
	printf("Checking core programs.\n");
   	simple_check();
	if (Init1.core_files != 0){
		return 1;
	}
	environment();
	if (Init1.environment != 0	|| Init1.core_invierno_bash != 0){
		return 1;
	}
	printf("Assigning internal IP adress.\n");
	Init1.internal_ip_address = system("dhclient");
	if(Init1.internal_ip_address != 0){
		fprintf(stderr,"[FAIL]\tAuto assign IP adress.\n");
	}
	else{
		printf("[OK]\tAuto assign IP adress.\n");
	}
	docker_init();
	if (Init1.docker != 0){
		return 1;
	}
	update();  
    system("/var/lib/invierno/core/bash --init-file /etc/inviernorc");
	return 0;
}
