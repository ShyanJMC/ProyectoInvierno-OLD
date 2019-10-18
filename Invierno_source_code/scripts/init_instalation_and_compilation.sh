#/*
# Invierno SHELL init and instalation script.
# Version 0.0.5 ALPHA
# Copyright 2018 - Joaquin Manuel Crespo
# Licensed in GeneralPublicLicense v3.
#
# This file is part of ProyectoInvierno.
# ProyectoInvierno is free software, you can use,
# redistribute it and/or modify it under the terms
# of the GNU General Public License as published by 
# Free Software Foundation, either version 3 of the license.
#
#
# Developed by ShyanJMC initially at 2018.
#*/

##### Script created by ShyanJMC for ProyectoInvierno.#####
###########################################################
#!/bin/bash
###########################################################
#Requeriments;
# GCC
# MAKE
# AUTOMAKE
# BISON
# TEXINFO
# PACMAN <------ Invierno_shell use that for update.

# DEBIAN Systems; build-essentials
###########################################################
#### This set is only for you can configure
#### ProyectoInvierno inside a docker container, if this is 
#### not that scenario please comment the below line
export FORCE_UNSAFE_CONFIGURE=1

###########################################################
#### Variables for compile and crate

WORKDIR=~/ProyectoInvierno/
SHELLDIR=$WORKDIR/Invierno_shell
UTILSDIR=$WORKDIR/Invierno_shell/core/coreutils-8.30/
BASHDIR=$WORKDIR/Invierno_shell/core/bash-5.0/
GREPDIR=$WORKDIR/Invierno_shell/core/grep-3.1/
TMUXDIR=$WORKDIR/Invierno_shell/core/tmux
INVDIR=/var/lib/invierno
INVFILE=/etc/invierno
INVBUILT=$INVDIR/builtin
COREDIR=$INVDIR/core

#### System
############# Possible combinatios;
############# Debian
############# RedHat
############# Gentoo
############# Arch

echo "Installing dependencies for compile and install ProyectoInvierno"
echo "The logs will be init_proyectoinvierno and init_proyectoinvierno_error"

apt install -y build-essential texinfo bison automake gcc make dh-autoreconf libevent-dev libncurses5-dev pkg-config > init_proyectoinvierno 2> init_proyectoinvierno_error 

###########################################################
####### Bash 		need aclocal-1.14
####### Coreutils 	need aclocal-1.15
####### Grep family 	need aclocal-1.99a
####### Because of that is needed autoreconf -f -i

welcome (){
	echo "Working...."
	echo "Making configuration files..."
	echo "All logs in /var/log/invierno_[component]"
}

inv_configuration(){
	cp $SHELLDIR/inviernorc /etc/inviernorc
	touch $INVFILE
	echo "BSH=0" >> $INVFILE
	echo "DCK=1" >> $INVFILE
}

inv_core_utils(){
	echo "-------------"
	echo "Compiling core utils..."
	cd $UTILSDIR
	autoreconf -i -f > /var/log/invierno_coreutils 2> /var/log/invierno_coreutils_error
	./configure > /var/log/invierno_configure_core_utils 2> /var/log/invierno_error_configure_core_utils
	make > /var/log/invierno_make_core_utils 2> /var/log/invierno_error_make_core_utils
	cd src/
	mkdir -p $COREDIR >> /var/log/invierno_coreutils 2>> /var/log/invierno_coreutils_error
	ls | grep -Ev ".h|.c|.mk|blake2|dcgen|.o" | xargs cp -t /var/lib/invierno/core
}

inv_shell(){
	echo "-------------"
	echo "Compiling Invierno Shell"
	cd $BASHDIR
	./configure > /var/log/invierno_configure_shell 2> /var/log/invierno_error_configure_shell
	make > /var/log/invierno_make_shell 2> /var/log/invierno_error_make_shell
	cp bash $COREDIR
}

inv_grep(){
	echo "-------------"
	echo "Compiling grep"
	cd $GREPDIR
	autoreconf -i -f > /var/log/invierno_grep 2> /var/log/invierno_grep_error
	./configure > /var/log/invierno_configure_grep 2> /var/log/invierno_error_configure_grep
	make > /var/log/invierno_make_grep 2> /var/log/invierno_error_make_grep
	cp src/grep $INVDIR/core
	cp src/egrep $INVDIR/core
	cp src/fgrep $INVDIR/core
}

inv_cshell(){
	echo "-------------"
	echo "Compiling shell....."
	cd $SHELLDIR
	gcc -march=native -lpthread invierno_shell.c -o invierno_shell > /var/log/invierno_shell_launcher 2> /var/lib/invierno_shell_launcher_error
	cp invierno_shell /bin/
}

end(){
	echo
	echo "Done. ProyectoInvierno compiled and installed."
	echo "For errors, check the logs in; /var/log/invierno_[component]"
}

inv_builtin(){
	mkdir -p $INVBUILT

}

###############################################################################################################
welcome
inv_builtin
inv_configuration
inv_cshell

inv_core_utils
inv_grep
inv_shell

end

