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

/* The shell automatically print an error to stderr 
 * and some message to stdout. With this information
 * you can redirect with 2> or > respectively.
 */

/*
 * Libraries
 */

/*
 * C standar libraries. 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Poxis Thread Librarie.
 */

#include<pthread.h>

/*
 * Check's functions.
 */

/*
A simple check to corroborate if the Bash's core utilities are
inside the Invierno's directory.
*/
void *simple_check()
{
	Init1.core_files = system("/var/lib/invierno/core/ls . > /dev/null");
	if (Init1.core_files != 0)
	{
		fprintf(stderr,"[FAIL]\tCore failes are damaged or missing.\n");
		Init1.core_files = 1;
	}
	else 
	{
		printf("[OK]\tCore files.\n");
		Init1.core_files = 0;
	}
	return 0;
}

/*
Check the configuration of the environment.
*/

void *environment()
{
	printf("Checking environment file.\n");
	Init1.environment  = system("/var/lib/invierno/core/ls /etc/invierno > /dev/null");
	if (Init1.environment != 0)
	{
		fprintf(stderr,"[FAIL]\tInvierno configuration missing.\n");
	}
	printf("[OK]\tEnvironment file.\n");
	printf("Checking if Bash is enable for the user.\n");
	Init1.core_invierno_bash = system("/var/lib/invierno/core/grep BSH=0 /etc/invierno > /dev/null");
	if(Init1.core_invierno_bash != 0)
	{
	 	fprintf(stderr,"[FAIL]\tBash for user is disabled.\n");
	}
	 else 
	{
	 	printf("[OK]\tBash enabled.\n");
	}
	return 0;
}

/*
Manual start of docker
*/
void *docker_init()
{
	short temporal1, temporal2;
	printf("Starting Invierno's docker.\n");
	temporal2 = system("ps aux | grep -i docker | grep -v grep");
	if (temporal2 != 0){
		temporal1 = system("nohup dockerd &");
		switch(temporal1)
		{
			case 0:
				printf("[OK]\tInvierno's docker started.\n");
				break;
			default:
				fprintf(stderr,"[FAIL]\tInvierno's docker failed to start.\n");
				break;
		}
	}
	else {
		return 0; 
	}
	return 0;
}
/*

/*
Checks docker and start it.
After a successful start, check the configuration
*/
void *docker_internal_init ()
{
    short temporal, temporal2;
    printf("Enabling and starting docker.\n");
    temporal = system("systemctl start docker > /dev/null && systemctl enable docker > /dev/null");
    printf("[OK]\tInvierno's docker started.\n");
    if (temporal != 0)
    {
        fprintf(stderr,"[FAIL]\tDocker start error.\n");
        Init1.docker = 1;
    }
    else
    {
	docker_init;
        }
	return 0;
}

/*
Upgrade the system.
Is very simple but is very neccesary keep the system updated with
the last security updates.
*/

void *update()
{
	short buffer;
	printf("Updating the system.\n");
	buffer = system("su -c 'yes | pacman -Syu' > /dev/null 2> /dev/null");
	if (buffer != 0)
	{
		fprintf(stderr,"[FAIL]\tError to update the system.\n");
		Init1.updated = 1;
	}
	else 
	{
		printf("\n[OK]\tSystem updated.\n");
		Init1.updated = 0;
	}
	return 0;
}

/* Build the images of docker */
void docker_build(){
	return 0;
}

/* Check the existence of Invierno's Containers */
void invierno_images(){
	short	temporal1, temporal2;
	char	temporal3;
	printf("Checking Invierno Containers.\n");
	temporal1 = system("/var/lib/invierno/core/grep -E DCK=0 /etc/invierno");
	if (temporal1 !=0){
		fprintf(stderr,"[FAIL]\tInvierno's containers not enabled.\n");
		return 1;
	}
	else {
		printf("[OK]\tInvierno's containers enabled. Checking existence.\n");
		temporal2 = system("docker images | /var/lib/invierno/core/grep -E 'InvPent|InvProx|InvTor'");
		if (temporal2 !=0){
			fprintf(stderr,"[Fail]\tInvierno's containers not detected. Do you want build them? y/n; ");
			temporal3 = getchar();
			if( temporal3 == 'y'){
				docker_build();
			}
			else {
				return 0;
			}
		}
		else {
			printf("[OK]\tInvierno's containers detected.\n");
		}
	}
	return 0;
}
