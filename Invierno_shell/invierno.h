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
 * Colors, for the strings.
 */

#define SNRM  "\x1B[0m"
#define SRED  "\x1B[31m"
#define SGRN  "\x1B[32m"
#define SYEL  "\x1B[33m"
#define SBLU  "\x1B[34m"
#define SMAG  "\x1B[35m"
#define SCYN  "\x1B[36m"
#define SWHT  "\x1B[37m"

/*
Store for information about the program.
1 is errror.
0 is OK.
Are in the order in wich the program execute.
*/
struct Information 
{
	int 	core_files,
		environment,
		core_invierno_bash,
		internal_ip_address,
		docker,
		invierno_container,
		updated,
		pthreads;
}Init1;

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
    printf("%sChecking core programs.\n",SWHT);
	Init1.core_files = system("/var/lib/invierno/core/ls . > /dev/null");
	if (Init1.core_files != 0)
	{
		fprintf(stderr,"%s[FAIL]\tCore failes are damaged or missing.\n",SRED);
		Init1.core_files = 1;
	}
	else 
	{
		printf("%s[OK]\tCore files.\n",SWHT);
		Init1.core_files = 0;
	}
	return;
}

/*
Check the configuration of the environment.
*/

void *environment()
{
	printf("%sChecking environment file.\n",SWHT);
	Init1.environment  = system("/var/lib/invierno/core/ls /etc/invierno > /dev/null");
	if (Init1.environment != 0)
	{
		fprintf(stderr,"%s[FAIL]\tInvierno configuration missing.\n",SRED);
	}
	printf("%s[OK]\tEnvironment file.\n",SWHT);
	printf("Checking if Bash is enable for the user.\n");
	Init1.core_invierno_bash = system("/var/lib/invierno/core/grep BSH=0 /etc/invierno > /dev/null");
	if(Init1.core_invierno_bash != 0)
	{
	 	fprintf(stderr,"%s[FAIL]\tBash for user is disabled.\n",SRED);
	}
	 else 
	{
	 	printf("%s[OK]\tBash enabled.\n",SWHT);
	}
	return;
}

/*
Manual start of docker
*/
void *docker_init()
{
	short temporal1, temporal2;
	printf("%sStarting Invierno's docker.\n",SWHT);
	temporal2 = system("ps aux | grep -i docker | grep -v grep");
	if (temporal2 != 0){
		temporal1 = system("nohup dockerd &");
		switch(temporal1)
		{
			case 0:
				printf("%s[OK]\tInvierno's docker started.\n",SWHT);
				break;
			default:
				fprintf(stderr,"%s[FAIL]\tInvierno's docker failed to start.\n",SRED);
				break;
		}
	}
	else {
		return; 
	}
	return;
}
/*

/*
Checks docker and start it.
After a successful start, check the configuration
*/
void *docker_internal_init ()
{
    short temporal, temporal2;
    printf("%sEnabling and starting docker.\n",SWHT);
    temporal = system("systemctl start docker > /dev/null && systemctl enable docker > /dev/null");
    if (temporal != 0)
    {
        fprintf(stderr,"%s[FAIL]\tDocker start error.\n",SRED);
        Init1.docker = 1;
    }
    else
    {
	docker_init();
        }
	return;
}

/*
Upgrade the system.
Is very simple but is very neccesary keep the system updated with
the last security updates.
*/

void *update()
{
	short buffer;
	printf("%sUpdating the system.\n",SWHT);
	buffer = system("su -c 'yes | pacman -Syu' > /dev/null 2> /dev/null");
	if (buffer != 0)
	{
		fprintf(stderr,"%s[FAIL]\tError to update the system.\n",SRED);
		Init1.updated = 1;
	}
	else 
	{
		printf("%s\n[OK]\tSystem updated.\n",SWHT);
		Init1.updated = 0;
	}
	return;
}

/* Build the images of docker */
void docker_build(){
	return;
}

/* Check the existence of Invierno's Containers */
void invierno_images(){
	short	temporal1, temporal2;
	char	temporal3;
	printf("%sChecking Invierno Containers.\n",SWHT);
	temporal1 = system("/var/lib/invierno/core/grep -E DCK=0 /etc/invierno");
	if (temporal1 !=0){
		fprintf(stderr,"%s[FAIL]\tInvierno's containers not enabled.\n",SRED);
		return;
	}
	else {
		printf("%s[OK]\tInvierno's containers enabled. Checking existence.\n",SWHT);
		temporal2 = system("docker images | /var/lib/invierno/core/grep -E 'InvPent|InvProx|InvTor'");
		if (temporal2 !=0){
			fprintf(stderr,"%s[Fail]\tInvierno's containers not detected. Do you want build them? y/n; ",SRED);
			temporal3 = getchar();
			if( temporal3 == 'y'){
				docker_build();
			}
			else {
				return;
			}
		}
		else {
			printf("%s[OK]\tInvierno's containers detected.\n",SWHT);
		}
	}
	return;
}
