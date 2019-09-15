#!/bin/bash

###############################
echo "Cleaning /var folder."
rm -rf /var/lib/invierno

###############################
echo "Cleaning configurations file."
rm -rf /etc/invierno /etc/inviernorc

##############################
echo "Cleaning bin files."
rm -rf /bin/invierno_shell

#############################
echo
echo
echo "Clean files done."
echo "Cleaning environment."

ENVIRONMENT=~/ProyectoInvierno/Invierno_shell/core/
cd $ENVIRONMENT/bash-5.0 && make clean
cd $ENVIRONMENT/coreutils-8.30 && make clean
cd $ENVIRONMENT/grep-3.1 && make clean
