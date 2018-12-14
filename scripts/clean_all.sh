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
echo "Clean done."
