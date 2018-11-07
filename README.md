# ProyectoInvierno
Personal project for docker's containers and a custom Arch Linux that will integrate them into a custom shell and environment. <br />
All this programs are programmed in C languaje, using another third party programms (see Credetis and CopyRight).<br />
To keep a minimal of quality, I created and tested all my programs using the gcc's arguments; -Wall -Werror <br>
<br />

## The same is composed by;
-BlackOS Linux; <br /> A custom Arch Linux for use as base for this project. <br /><br />
-Invierno Shell; <br /> A custom Shell with inits checks and independient from the distribution.<br /><br />
-Docker's containers; <br /> They will include all my personal projects (in alpha at today). The same are; <br /><br />
 &nbsp;&nbsp;&nbsp; -Pentesting Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Tor Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Privoxy Invierno. <br/><br />

# Escepcion de responsabilidad y terminos de uso.
-Link en español; <br />
https://github.com/ShyanJMC/ProyectoInvierno/wiki/Condiciones-de-uso-y-escepcion-de-responsabilidad.
 
# Disclaimer and terms of use.
-Link in english; <br />
https://github.com/ShyanJMC/ProyectoInvierno/wiki/Terms-of-use-and-disclaimer

## Requeriments;
-Gcc <br />
-Docker <br />
-Dhcpcd <br />
-Automake <br />
-Autoconf <br />
-Dhclient <br /><br />
## Credits and CopyRight;
-[ArchLinux](https://www.archlinux.org/)<br />
-[Docker](https://www.docker.com/) <br />
-[Moby](https://mobyproject.org/) <br />
-[GNU](https://www.gnu.org/)<br />
-[Roy's Place](https://roy.marples.name/)<br />
-[Parrot Linux Security](https://www.parrotsec.org/)<br />

## Invierno Shell
![Invierno-shell](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Invierno_shell_screenshot.png) <br />
This is a custom shell for Gnu/Linux that have all dependencies integrated in /var/lib/invierno folder.<br />
This shell check at the init all needed services and the requeriments of ProyectoInvierno, setting automatically IP address, Invierno's containers, shell configuration and auto update of the system (and another things), all in different threads (4 in total).<br />

### How to build (run as root); <br />
cd ~ && git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/ && bash +x init_instalation_and_compilation.sh
<br />
## Pentesting Invierno;
![Invnierno-pentesting](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Screenshot2.png) <br />
That proyect is for a minimal and small container for pentesting proposes. <br />
The same is based in Parrot Sec Linux repositories. <br />

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images && mv Invierno_pentesting_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_pentestingcontainer . && docker run -ti -h Invierno_pentesting shyanjmc/proyectoinvierno_pentestingcontainer <br />
#### Use for your own proposes and responsability.<br />

## Tor Invierno;
![Tor ARM](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Screenshot.png) <br />
This version of Tor is configured in a basic configuration to be managmented by Tor-ARM, a monitoring tool for control and check a lot of aspecs of the onion network.
Use Tor for own proposes and responsability, none of Invierno's team will take responsability about the actions taked using Tor.

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images/ && mv Invierno_tor_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_torcontainer . && docker run -ti -h Invierno_Tor shyanjmc/proyectoinvierno_torcontainer <br />

## Privoxy Invierno
Privoxy is a HTTP's protocol proxy for Gnu/Linux. You can customize the same for add your block or white list and in this way customize your web experience.<br />
If you need anonymity in the net, don't block webpages, this cause that your browser have an UID (Unique IDentifier).

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images/ && mv Invierno_privoxy_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_privoxycontainer . && docker run -ti -h Invierno_Tor shyanjmc/proyectoinvierno_privoxycontainer <br />
