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

WORKDIR=~/ProyectoInvierno
IMAGESDIR=$WORKDIR/Images
SHELLDIR=$WORKDIR/Invierno_shell
UTILSDIR=$WORKDIR/Invierno_shell/core/coreutils-8.30/
BASHDIR=$WORKDIR/Invierno_shell/core/bash-4.4.18/
GREPDIR=$WORKDIR/Invierno_shell/core/grep-3.1/
TMUXDIR=$WORKDIR/Invierno_shell/core/tmux
INVDIR=/var/lib/invierno
INVFILE=/etc/invierno
COREDIR=$INVDIR/core

#### System
############# Possible combinatios;
############# Debian
############# RedHat
############# Gentoo
############# Arch

echo "Installing dependencies for compile and install ProyectoInvierno"
echo "The logs will be init_proyectoinvierno and init_proyectoinvierno_error"
echo
SYSTEM=$1
if	[$SYSTEM == "Debian"];	then
	apt install -y build-essentials texinfo bison automake gcc make dh-autoreconf libevent-dev libncurses5-dev pkg-config > init_proyectoinvierno 2> init_proyectoinvierno_error 
	echo "SYS=deb" >> /etc/invierno
elif	[$SYSTEM == "RedHat"];	then
	yum groupinstall -y "Development Tools" > init_proyectoinvierno 2> init_proyectoinvierno_error
	echo "SYS=red" >> /etc/invierno
elif	[$SYSTEM == "Gentoo"];	then
	emerge sys-apps/texinfo sys-devel/bison sys-devel/automake sys-devel/make > init_proyectoinvierno 2> init_proyectoinvierno_error
	echo "SYS=gen" >> /etc/invierno
elif	[$SYSTEM == "Arch"];	then
	yes | pacman -S bison texinfo automake gcc make > init_proyectoinvierno 2> init_proyectoinvierno_error
	echo "SYS=arc" >> /etc/invierno
fi 
###########################################################
####### Bash 		need aclocal-1.14
####### Coreutils 	need aclocal-1.15
####### Grep family 	need aclocal-1.99a
####### Because of that is needed autoreconf -f -i

clear
echo "Working...."
echo "Making configuration files..."

cp $SHELLDIR/inviernorc /etc/inviernorc
touch $INVFILE
echo "BSH=0" >> $INVFILE
echo "DCK=1" >> $INVFILE

echo "-------------"
echo "Compiling core utils..."
cd $UTILSDIR
autoreconf -i -f
./configure
make
cd src/
mkdir -p $COREDIR
ls | grep -Ev ".h|.c|.mk|blake2|dcgen|.o" | xargs cp -t /var/lib/invierno/core

echo "-------------"
echo "Copying the Ivierno's Containers"
mkdir $INVDIR/Images
cp -r $IMAGESDIR $INVDIR

echo "------------"
echo "Compiling tmux."
cd $TMUXDIR
./autogen.sh
./configure
sed -i 's/-std=gnu99/-std=gnu99 -march=native/g' Makefile
make
cp tmux $COREDIR


echo "-------------"
echo "Compiling Invierno Shell"
cd $BASHDIR
autoreconf -i -f
./configure
make
cp bash $COREDIR


echo "-------------"
echo "Compiling grep"
cd $GREPDIR
autoreconf -i -f
./configure
make
cp src/grep $INVDIR/core
cp src/egrep $INVDIR/core
cp src/fgrep $INVDIR/core

echo "-------------"
echo "Compiling shell....."
cd $SHELLDIR
gcc -march=native -lpthread invierno_shell.c -o invierno_shell
cp invierno_shell /bin/

echo
echo "Done. ProyectoInvierno compiled and installed."
