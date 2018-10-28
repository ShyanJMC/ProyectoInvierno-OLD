/*
Invierno SHELL.
Version 0.0.2 ALPHA
Licensed in GPL v3.

Developed by ShyanJMC.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
/*
Store for information about the program.
1 is errror.
0 is OK.
Are in the order in wich the program execute.
*/
struct Information 
{
	int core_files,
	environment,
	core_invierno_bash,
	internal_ip_address,
	docker,
	invierno_container,
	updated,
	pthreads;
}Init1;

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
}

/*
Checks docker and start it.
After a successful start, check the configuration
*/
void *docker_init ()
{
    int temporal, temporal2;
    printf("Enabling and starting docker.\n");
    temporal = system("systemctl start docker > /dev/null && systemctl enable docker > /dev/null");
    if (temporal != 0)
    {
        fprintf(stderr,"[FAIL]\tDocker start error.\n");
        Init1.docker = 1;
    }
    else
    {
    	printf("[OK]\tDocker started.\n");
    	Init1.docker = 0;
    	printf("Checking invierno's container configuration.\n");
    	temporal2 = system("/var/lib/invierno/core/grep DCK=0 /etc/invierno > /dev/null");
    	if (temporal2 != 0)
	{
    		fprintf(stderr,"[FAIL]\tInvierno's container disabled.\n");
    		Init1.invierno_container = 1;
       	}
    	else
	{
    		printf("[OK]\tInvierno's container enabled. Checking and building.\n");
    		Init1.invierno_container = 0;
    	}
    }
}

/*
Upgrade the system.
Is very simple but is very neccesary keep the system updated with
the last security updates.
*/

void *update()
{
	int buffer;
	printf("Updating the system.\n");
	buffer = system("yes | pacman -Syu > /dev/null 2> /dev/null");
	if (buffer != 0)
	{
		fprintf(stderr,"[FAIL]\tError to update the system.\n");
		Init1.updated = 1;
	}
	else 
	{
		printf("[OK]\tSystem updated.\n");
		Init1.updated = 0;
	}
	return 0;
}

/*
Execute the functions in poxis threads and check the return of the same.
*/
int main( int first_arg, char **second_arg)
{
	pthread_t thread1, thread2, thread3, thread4, thread5;
	int	  irthread1, irthread2, irthread3, irthread4, irthread5;
	system("clear");
	printf("Starting Invierno.\n");
	printf("Checking core programs.\n");
   	
	irthread1 = pthread_create(&thread1,NULL,simple_check, NULL);
	if (Init1.core_files != 0)
	{
		return 1;
	}
	irthread2 = pthread_create(&thread2,NULL,environment, NULL);
	if (Init1.environment != 0	|| Init1.core_invierno_bash != 0)
	{
		return 1;
	}
	printf("Assigning internal IP adress.\n");
	Init1.internal_ip_address = system("dhclient");
	if(Init1.internal_ip_address != 0)
	{
		fprintf(stderr,"[FAIL]\tAuto assign IP adress.\n");
	}
	else
	{
		printf("[OK]\tAuto assign IP adress.\n");
	}
	irthread3 = pthread_create(&thread3,NULL,docker_init, NULL);
	if (Init1.docker != 0)
	{
		return 1;
	}
	irthread4 = pthread_create(&thread4,NULL, update, NULL);  


/* Awaiting the finish of the pthreads before start Bash in the line post comments */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	
/* */
	system("/var/lib/invierno/core/bash --init-file /etc/inviernorc");
	return 0;
}

