##### Script created by ShyanJMC for ProyectoInvierno.#####
###########################################################

WORKDIR=~/ProyectoInvierno/
IMAGESDIR=$WORKDIR/Images
SHELLDIR=$WORKDIR/Invierno_shell
UTILSDIR=$WORKDIR/Invierno_shell/core/coreutils-8.30/
BASHDIR=$WORKDIR/Invierno_shell/core/bash-4.4.18/
GREPDIR=$WORKDOR/Invierno_shell/core/grep-3.1/

INVDIR=/var/lib/invierno
INVFILE=/etc/invierno
COREDIR=$INVDIR/core

#!/bin/bash
clear
echo "Working...."
echo "Making configuration files..."

cp Invierno_shell/inviernorc /etc/inviernorc
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
ls | grep -Ev ".h|.c|.mk|blake2|dcgen" | xargs cp -t /var/lib/invierno/core

echo "-------------"
echo "Copying the Ivierno's Containers"
mkdir $INVDIR/Images
cp -r $IMAGESDIR $INVDIR/Images


echo "-------------"
echo "Compiling BASH and Grep"
cd $BASHDIR
./configure
make
cp bash $INVDIR/core
cd $GREPDIR
./configure
make
cp src/grep $INVDIR/core
cp src/egrep $INVDIR/core
cp src/fgrep $INVDIR/core

echo "-------------"
echo "Compiling shell....."
cd $SHELLDIR
gcc invierno_shell.c -o invierno_shell
cp invierno_shell /usr/bin/

echo
echo "Done"
