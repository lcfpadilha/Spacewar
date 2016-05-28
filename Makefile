CFLAGS= -Wall -g -pedantic -O2


all : spacewar

ifndef NOXPM
spacewar : spacewar.o libs/planet.o libs/ship.o libs/projectile.o libs/getIndex.o libs/controller.o libs/xwc.o  libs/error.o
	${CC} ${CFLAGS} -o spacewar spacewar.o libs/planet.o libs/ship.o libs/projectile.o libs/getIndex.o libs/controller.o libs/xwc.o libs/error.o -lm -lXpm -lX11 
else
spacewar :
	echo Este programa só funciona com a biblioteca Xpm instalada
endif

spacewar.o : spacewar.c

libs/planet.o : libs/planet.c

libs/ship.o : libs/ship.c

libs/projectile.o : libs/projectile.c

libs/getIndex.o : libs/getIndex.c

libs/controller.o : libs/controller.c

libs/xwc.o : libs/xwc.c

libs/error.o : libs/error.c

