##### Script created by ShyanJMC for ProyectoInvierno.

#!/bin/bash
clear
echo "Working...."
echo "Making configuration files..."

cp Invierno_shell/inviernorc /etc/inviernorc
touch /etc/invierno
echo "BSH=0" >> /etc/invierno

echo "-------------"
echo "Compiling core utils..."
cd Invierno_shell/core/coreutils-8.30/
make
cd src/
ls | grep -Ev ".h|.c|.mk|blake2|dcgen" | xargs cp -t ../../
mkdir /var/lib/invierno/core
ls ../../../core/ | grep -v coreutils-8.30 | xargs cp -t /var/lib/invierno/core


echo "-------------"
echo "Compiling shell....."
cd ../../../
gcc invierno_shell.c -o invierno_shell
cp invierno_shell /usr/bin/


clear
echo "Done"
