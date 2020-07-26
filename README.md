# ProyectoInvierno
# THIS PROYECT WAS MOVE TO THE NEW REPO, WITH THE SAME NAME BUT NOW WILL WORK WITH RUST FROM SCRATCH.<br /><br /> 


This is personal project for docker's containers, and a custom shell for manage specific containers. <br /><br />
The objetive of this is create a personal, and distro independent, environment. <br /><br />
To keep a minimal of quality, I created and tested all my programs using the gcc's arguments; -Wall -Werror <br />
Some warnings (like unused variables) are ignored by obviously reasons.<br /><br />

THIS PROGRAM INTEGRATE THREE SOFTWARE FROM GNU PROJECT UNDER Invierno_shell/core/

<br />

#### How to run;
- git clone https://www.github.com/ShyanJMC/ProyectoInvierno && cd ProyectoInvierno &&docker build -t proyectoinvierno:0.0.3 . 
<br />
<br />
Then start the container with; <br/>
- docker run -ti -v /var/run/docker.sock:/var/run/docker.sock proyectoinvierno:0.0.3
<br />
<br />
Remember, the hostname is the ID of your container.

## Requeriments;
- Docker in your computer where you will run this.

## Features;
- Custom BASH shell.
- Independent grep and coreutils family under "/var/lib/invierno/core".
- Upgrade the container at startup.
- Containers management (working on this actually).

## Credits and CopyRight;
- [ArchLinux](https://www.archlinux.org/)
- [Docker](https://www.docker.com/)
- [Moby](https://mobyproject.org/)
- [GNU](https://www.gnu.org/)
- [Roy's Place](https://roy.marples.name/)
- [Parrot Linux Security](https://www.parrotsec.org/)
