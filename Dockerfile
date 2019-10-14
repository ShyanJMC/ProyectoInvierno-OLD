FROM	debian:latest
LABEL	maintainer="ShyanJMC joaquincrespo96@gmail.com"

RUN	apt update && apt upgrade -y && \
	mkdir -p /root/ProyectoInvierno/

ADD	Invierno_source_code/	/root/ProyectoInvierno/
RUN	chmod +x /root/ProyectoInvierno/scripts/*

CMD	["bash -c /root/ProyectoInvierno/scripts/init_instalation_and_compilation.sh"]
