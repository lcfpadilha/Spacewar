CFLAGS= -Wall -g -pedantic -O2


all : spacewar

ifndef NOXPM
spacewar : spacewar.o libs/controller.o libs/getIndex.o libs/planet.o libs/projectile.o libs/scenes.o libs/ship.o libs/xwc.o
	${CC} ${CFLAGS} -o spacewar $^ -lm -lXpm -lX11 
else
spacewar :
	echo Este programa só funciona com a biblioteca Xpm instalada
endif

spacewar.o : spacewar.c

libs/controller.o : libs/controller.c

libs/getIndex.o : libs/getIndex.c

libs/planet.o : libs/planet.c

libs/projectile.o : libs/projectile.c

libs/scenes.o : libs/scenes.c

libs/ship.o : libs/ship.c

libs/xwc.o : libs/xwc.c

