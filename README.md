# ProyectoInvierno
Personal project for docker's containers and a custom Arch Linux that will integrate them into a custom shell and environment. <br />
<br />

## Disclaimer [ESPAÑOL] <br />
Estos programas son simplemente eso, programas, cuya intención es facilitar algunas tareas administrativas cuando se inicia el sistema.<br />
Ninguno de los programas y utilidades (con referencia expresa a los containers de Docker situados en el directorio "Images") tiene por fin causar un daño físico o metafórico a cualquier bien o persona ajena al usuario que lo ejecute. Como tal yo, Joaquin Manuel Crespo, no puedo hacerme responsable de las acciones tomadas por el usuario que ejecute y accione usando los archivos de creación de los containers de Tor y Parrot Sec, por tal motivo si usted va a usar estos containers, úselos bajo su propia responsabilidad en las acciones pasadas y venideras que haga con estos programas. <br />
Como tal, abajo en la sección "Credits and CopyRight" están especificados los autores originales de cada uno de estos programas, yo simplemente los he empaquetado en programas independientes de la distribución Gnu/Linux y los he puesto en containers. <br />
Con base en lo anteriormente mencionado, yo solo modifico la forma de instalación de estas herramientas, el usuario puede encontrar información alrededor de la web sobre como hacerlo por él/ella mismo sin la necesidad de usar este proyecto. <br />

## Disclaimer [ENGLISH] <br />
These programs are simply that, programs, whose intention is to facilitate some administrative tasks when the system is started. <br />
None of the programs and utilities (with express reference to the Docker's containers located in the "Images" directory) is intended to cause physical or metaphorical damage to any patrimony or person alien to the user who executes it. As such I, Joaquin Manuel Crespo, can not be held responsible for the actions taken by the user that executes and operates using the Tor and Parrot Sec container creation files, for this reason if you are going to use these containers, use them under your own responsibility in the past and future actions you take with these programs. <br />
As such, below in the section "Credits and CopyRight" the original authors of each of these programs are specified, I have simply packaged them in independent programs of the Gnu / Linux distribution and I have put them in containers. <br />
Based on the aforementioned, I only modify the form of installation of these tools, the user can find information around the web on how to do it himself / herself without the need to use this project. <br />  

## The same is composed by;
-BlackOS Linux; <br /> A custom Arch Linux for use as base for this project. <br /><br />
-Invierno Shell; <br /> A custom Shell with inits checks and independient from the distribution.<br /><br />
-Docker's containers; <br /> They will include all my personal projects (in alpha at today). The same are; <br /><br />
 &nbsp;&nbsp;&nbsp; -Pentesting Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Tor Invierno. <br />
 &nbsp;&nbsp;&nbsp; -Privoxy Invierno. <br/><br />

## Requeriments ( for now, I'm including the dependencies inside the core directory);
-Gcc <br />
-Docker <br />
-Dhcpcd <br />
-Automake <br />
-Autoconf <br />
-Dhclient <br /><br />
## Credits and CopyRight;
-[ArchLinux]=https://www.archlinux.org/ <br />
-[Docker]=https://www.docker.com/ <br />
-[Moby]=https://mobyproject.org/ <br />
-[GNU]=https://www.gnu.org/<br />
-[Roy's Place]=https://roy.marples.name/<br />

## Invierno Shell
![Invierno-shell](https://github.com/ShyanJMC/ProyectoInvierno/blob/master/screenshots/Invierno_shell_screenshot.png) <br />
This is a custom shell for Gnu/Linux that have all dependencies integrated in /var/lib/invierno folder.<br />
This shell check at the init all needed services and the requeriments of ProyectoInvierno, setting automatically IP address, Invierno's containers, shell configuration and auto update of the system (and another things).<br />

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
