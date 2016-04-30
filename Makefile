CFLAGS= -Wall -g -pedantic -O2


all : spacewar

ifndef NOXPM
spacewar : spacewar.o libs/planet.o libs/ship.o libs/projectile.o libs/simulation.o libs/getIndex.o libs/xwc.o 
	${CC} ${CFLAGS} -o spacewar spacewar.o libs/planet.o libs/ship.o libs/projectile.o libs/simulation.o libs/getIndex.o libs/xwc.o -lm -lXpm -lX11 
else
spacewar :
	echo Este programa s� funciona com a biblioteca Xpm instalada
endif

spacewar.o : spacewar.c

libs/planet.o : libs/planet.c

libs/ship.o : libs/ship.c

libs/projectile.o : libs/projectile.c

libs/simulation.o : libs/simulation.c

libs/getIndex.o : libs/getIndex.c

libs/xwc.o : libs/xwc.c
