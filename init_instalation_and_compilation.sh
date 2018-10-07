##### Script created by ShyanJMC for ProyectoInvierno.

#!/bin/bash
clear
echo "Working...."
echo "Making configuration files..."

cp Invierno_shell/inviernorc /etc/inviernorc
touch /etc/invierno
echo "BSH=0" >> /etc/invierno
echo "DCK=1" >> /etc/invierno

echo "-------------"
echo "Compiling core utils..."
cd Invierno_shell/core/coreutils-8.30/
./configure
make
cd src/
mkdir -p /var/lib/invierno/core
ls | grep -Ev ".h|.c|.mk|blake2|dcgen" | xargs cp -t /var/lib/invierno/core

echo "-------------"
echo "Copying the Ivierno's Containers"
cp -r ../../../../Images /var/lib/invierno


echo "-------------"
echo "Compiling BASH and Grep"
cd ../../bash-4.4.18/
./configure
make
cp bash /var/lib/invierno/core
cd ../grep-3.1
./configure
make
cp src/grep /var/lib/invierno/core
cp src/egrep /var/lib/invierno/core
cp src/fgrep /var/lib/invierno/core

echo "-------------"
echo "Compiling shell....."
cd ../../
gcc invierno_shell.c -o invierno_shell
cp invierno_shell /usr/bin/

echo
echo "Done"
