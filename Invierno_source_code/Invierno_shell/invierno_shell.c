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
 * Invierno's header.
 */

#include"invierno.h"


/*
Execute the functions in poxis threads and check the return of the same.
*/
int main( int first_arg, char **second_arg)
{
	pthread_t thread1, thread2, thread3, thread4, thread5;
	int	  irthread1, irthread2, irthread3, irthread4, irthread5;
	system("clear");
	printf("%sStarting Invierno.\n",SCYN);
	printf("%sBash, Grep family and Coreutils are in GPLv3. Copy of license are under ProyectoInvierno/Licenses.\n",SGRN);
	printf("%s==================================================================================================\n",SWHT);
    
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
	
	irthread3 = pthread_create(&thread3,NULL,docker_internal_init,NULL);
	if (Init1.docker != 0)
	{
		return 1;
	}
	
	irthread4 = pthread_create(&thread4,NULL, update, NULL);
    
	irthread5 = pthread_create(&thread5, NULL, invierno_images, NULL);


/* Awaiting the finish of the pthreads before start Bash in the line post comments */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);
    
/* Execution of bash */
    printf("%s==================================================================================================\n",SWHT);
	system("/var/lib/invierno/core/bash --init-file /etc/inviernorc");
	return 0;
}

