#!/bin/bash

#####
#####	Created by Joaquin Manuel Crespo (aka; shyanjmc) for ProyectoInvierno
#####	www.github.com/ShyanJMC/ProyectoInvierno

#################
# FUNCTIONS
#################

inv_portainer_create_volume(){
    docker volume create portainer_data
	if [ $? -eq 0] 
	then
		export PORTAINERVOLUME="portainer_data"
	else
		echo "Failed to create portainer's volume"
	fi

}

inv_portainer_create_run(){
        docker pull portainer/portainer
        echo "Creating portainer container"
		docker run -d -p 9000:9000 -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data --name portainer_invierno_implementation portainer/portainer &> $PORTAINERID
        echo "Portainer container ID;" 
		source /etc/inviernorc
}

inv_portainer_create(){
    if [ -z "$PORTAINERVOLUME" ]
    then 
    	inv_portainer_create_volume
		inv_portainer_create_run
	else
		inv_portainer_create_run
	fi

}

inv_portainer_status(){
	if [ -z "$PORTAINERID" ]
	then
		echo "Portainer container is not created."
	else
        echo "Portainer container details:"
        echo "============================"
		docker ps -a --filter "name=portainer_invierno_implementation"
	fi
}

inv_portainer_stop(){
    docker stop $(docker ps -a | grep portainer | cut -d' ' -f1)
}

inv_portainer_start(){
    docker start $(docker ps -a | grep portainer | cut -d' ' -f1)
}
####################

case $1 in
    create)
        inv_portainer_create
    ;;
    status)
        inv_portainer_status
	;;
    stop)
        inv_portainer_stop
    ;;
    start)
        inv_portainer_start
    ;;
    *)
    echo "Command don't exist
    
    create :    Create portainer's container
    status :    Print the container's status
    stop   :    Stop the portainer's container
    start  :    Start the portainer's container
    "
    ;;
esac
