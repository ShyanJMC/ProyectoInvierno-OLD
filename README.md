# ProyectoInvierno
Personal project for docker's containers and an custom Arch Linux that will integrate them into an custom shell and environment. <br />
None source code file from coreutils (the GNU utilities) were modified.<br />

## The same is composed by;
-BlackOS Linux (code name; FrozenLinux); <br /> An custom Arch Linux for use as base for this project. <br /><br />
-Invierno Shell; <br /> An custom Shell with inits checks.<br /><br />
-Docker's containers; <br /> They will include all my personal projects (in alpha at today). The same are; <br /><br />
 &nbsp;&nbsp;&nbsp; -Pentesting Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Tor Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Privoxy Invierno. <br/><br />
## Requeriments ( for now, I'm including the dependencies inside the core directory);
-Gcc <br />
-Docker <br />
-Dhcpcd <br />
-Dhclient <br /><br />
## Credits and CopyRight;
-[ArchLinux]=https://www.archlinux.org/ <br />
-[Docker]=https://www.docker.com/ <br />
-[Moby]=https://mobyproject.org/ <br />
-[GNU]=https://www.gnu.org/<br />
-[Roy's Place]=https://roy.marples.name/<br />

## Pentesting Invierno;
![Invnierno-pentesting](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Screenshot2.png)
That proyect is for an minimal and small container for pentesting proposes. <br />
The same is based in Parrot Sec Linux repositories. <br />

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images && mv Invierno_pentesting_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_pentestingcontainer . && docker run -ti -h Invierno_pentesting shyanjmc/proyectoinvierno_pentestingcontainer <br />
#### Use for your own proposes and responsability.

## Tor Invierno;
![Tor ARM](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Screenshot.png)
This version of Tor is configured in an basic configuration to be managmented by Tor-ARM, an monitoring tool for control and check a lot of aspecs of the onion network.
Use Tor for own proposes and responsability, none of Invierno's team will take responsability about the actions taked using Tor.

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images/ && mv Invierno_tor_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_torcontainer . && docker run -ti -h Invierno_Tor shyanjmc/proyectoinvierno_torcontainer <br />

## Privoxy Invierno
Privoxy is an HTTP's protocol for Gnu/Linux. You can customize the same for add your block or white list and in this way customize your web experience.<br />
If you need anonymity in the net, don't block webpages, this cause that your browser have an UID (Unique IDentifier).

### How to build (run as root); <br />
git clone https://github.com/ShyanJMC/ProyectoInvierno.git && cd ProyectoInvierno/Images/ && mv Invierno_privoxy_dockerfile Dockerfile && docker build -t shyanjmc/proyectoinvierno_privoxycontainer . && docker run -ti -h Invierno_Tor shyanjmc/proyectoinvierno_privoxycontainer <br />
