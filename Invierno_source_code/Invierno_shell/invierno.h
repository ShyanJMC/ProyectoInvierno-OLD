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
	short 	core_files,
		environment,
		core_invierno_bash,
		internal_ip_address,
		docker,
		invierno_container,
		updated,
		pthreads;
}Init1;

struct DockerInformation
{
    short   daemon,
        containers;
}Init2;

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
#include<unistd.h>
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
	temporal2 = system("ps aux | grep -i docker | grep -v grep > /dev/null 2> /dev/null");
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
Upgrade the system.
Is very simple but is very neccesary keep the system updated with
the last security updates.
*/

void *update()
{
	int childp;
	short buffer1, buffer2;
	printf("%sUpdating the system.\n",SWHT);
	const char *aptupd[]={"/usr/bin/apt","update",NULL};
	const char *aptupg[]={"/usr/bin/apt","upgrade","-y",NULL};
	childp = fork();
	switch(childp){
		 case 0:{
		 	 buffer1 = execvp(aptupd[0],aptupd);
			 buffer2 = execvp(aptupg[0],aptupg);
			 if (buffer1 != 0){
				 fprintf(stderr,"%s[FAIL]\tError to update the system.\n",SRED);
				 Init1.updated = 1;
			 }
			 else 
			 {
				 printf("%s\n[OK]\tSystem updated.\n",SWHT);
				 Init1.updated = 0;
				 }
			 return 0;
			}
		 case 1:{
				fprintf(stderr, "Failed to fork process");
			}
		 default:{
			 }
	}
	 return;
}

/* Build the images of docker */
void docker_build(){
    short temporal1, temporal2;
    /* 
    Just for do a new line.
     */
    system("echo");
    printf("Creating Invierno's containers. This will take some minutes, depending of your connection. \n");
    temporal1 = system("ls -l /var/lib/invierno/Images/Invierno* > /dev/null 2> /dev/null");
    switch(temporal1){
        case 1:
            fprintf(stderr,"%sNo Invierno's dockerfiles founded.\n",SRED);
        default:
            printf("Invierno's dockerfiles founded. Building.\n");
    }
    /*
     * Taking in consideration this images;
     *  Invierno_tor_dockerfile
     *  Invierno_privoxy_dockerfile
     *  Invierno_pentesting_dockerfile
     *  Invierno_ansible_dockerfile
     */
    temporal2 = system("cp /var/lib/invierno/Images/Invierno_tor_dockerfile /var/lib/invierno/Images/Dockerfile && docker build -t invierno_tor /var/lib/invierno/Images");
    if(temporal2 !=0){
        fprintf(stderr,"%s[FAIL] Error building Invierno's tor container.\n",SRED);
    }
    temporal2 = system("cp /var/lib/invierno/Images/Invierno_provoxy_dockerfile /var/lib/invierno/Images/Dockerfile && docker build -t invierno_privoxy /var/lib/invierno/Images");
    if(temporal2 !=0){
        fprintf(stderr,"%s[FAIL] Error building Invierno's provoxy container.\n",SRED);
    }
    temporal2 = system("cp /var/lib/invierno/Images/Invierno_pentesting_dockerfile /var/lib/invierno/Images/Dockerfile && docker build -t invierno_pentesting /var/lib/invierno/Images");
    if(temporal2 !=0){
        fprintf(stderr,"%s[FAIL] Error building Invierno's pentesting container.\n",SRED);
    }
    temporal2 = system("cp /var/lib/invierno/Images/Invierno_ansible_dockerfile /var/lib/invierno/Images/Dockerfile && docker build -t invierno_ansible /var/lib/invierno/Images");
    if(temporal2 !=0){
        fprintf(stderr,"%s[FAIL] Error building Invierno's ansible container.\n",SRED);
    }
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

void docker_thread_check(){
   short temporal1, temporal2;
   int childp;
   childp = fork();
   switch(childp) {
	   case 0: {
	   	char *check[]={"ps","aux","|","grep","dockerd","|","grep","-v","grep",NULL};
		temporal1 = execvp(check[0],check);
		switch(temporal1){
        		case 1:
            			fprintf(stderr,"[FAIL]\tDocker's daemon not recognized in the system.\n");
        		default:
            			printf("%s[OK]\tDocker's daemon running.\n",SGRN);
    		}
		   }
	   case 1: {
			   fprintf(stderr,"Fail to fork process");
		   }
	   default:{
		   }
   }
    		return;

}
