##### Script created by ShyanJMC for ProyectoInvierno.#####
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
IMAGESDIR=$WORKDIR/Images
SHELLDIR=$WORKDIR/Invierno_shell
UTILSDIR=$WORKDIR/Invierno_shell/core/coreutils-8.30/
BASHDIR=$WORKDIR/Invierno_shell/core/bash-4.4.18/
GREPDIR=$WORKDIR/Invierno_shell/core/grep-3.1/
INVDIR=/var/lib/invierno
INVFILE=/etc/invierno
COREDIR=$INVDIR/core

###########################################################

#!/bin/bash
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
./configure
make
cd src/
mkdir -p $COREDIR
ls | grep -Ev ".h|.c|.mk|blake2|dcgen|.o" | xargs cp -t /var/lib/invierno/core

echo "-------------"
echo "Copying the Ivierno's Containers"
mkdir $INVDIR/Images
cp -r $IMAGESDIR $INVDIR


echo "-------------"
echo "Compiling BASH"
cd $BASHDIR
./configure
make
cp bash $INVDIR/core

echo "-------------"
echo "Compiling grep"
cd $GREPDIR
./configure
make
cp src/grep $INVDIR/core
cp src/egrep $INVDIR/core
cp src/fgrep $INVDIR/core

echo "-------------"
echo "Compiling shell....."
cd $SHELLDIR
gcc -lpthread invierno_shell.c -o invierno_shell
cp invierno_shell /usr/bin/

echo
echo "Done. ProyectoInvierno compiled and installed."
