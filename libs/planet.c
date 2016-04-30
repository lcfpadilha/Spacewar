/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       projectile.c
 *  Dependências:  xwc.h
 * 
 *  Arquivo .c de planet.c
 *
 ******************************************************************************/ 

#include "planet.h"

#define W 720         // Largura da imagem.
#define H 480         // Altura da imagem.
#define CENTERX 360   // Centro x da imagem.
#define CENTERY 240   // Centro y da imagem.

void showScene (planet world, WINDOW *w, PIC bg) {
    int radius = world.radius;
    int x = CENTERX + world.posX - radius;
    int y = CENTERY + world.posY - radius;

    /* Desenhando o background. */
    PutPic (w, bg, 0, 0, W + 10, H + 10, 0, 0);

    /* Desenhando o planeta com a máscara. */
    SetMask (w, world.msk);
    PutPic (w, world.img, 0, 0, radius * 2, radius * 2, x, y);
    UnSetMask (w);
}

void initPlanet (planet *world, WINDOW *w) {
	/* Informações do planeta. */
    scanf ("%f %f", &world->radius, &world->mass);

    /* Imagens relacionadas ao planeta. */
    world->img = ReadPic (w, "img/scenery/planet.xpm", NULL);
    world->msk = NewMask (w, world->radius * 2, world->radius * 2);
    world->aux = ReadPic (w, "img/scenery/planetMask.xpm", world->msk);
}
