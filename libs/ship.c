/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       ship.c
 *  Dependências:  getIndex.h xwc.h
 * 
 *  Arquivo .c de ship.h
 *
 ******************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "getIndex.h"
#include "ship.h"


#define G 1.0        // Constante gravitacional universal.
#define CENTERX 360  // Centro x da imagem.
#define CENTERY 240  // Centro y da imagem.

float accelerateShip (ship s, float mass, float posX, float posY, char c) {
    float dx = posX - s.posX;
    float dy = posY - s.posY;
    float delta = sqrt (dx * dx + dy * dy);
    float accel = G * mass / (delta * delta);

    if (c == 'x') return accel * dx / delta;
    return accel * dy / delta;
}

ship increaseTimeShip (ship player, int maxX, int minX, 
                                    int maxY, int minY, float dt) {
    int i;
    ship new;
    strcpy (new.name, player.name);
    new.mass = player.mass;
    new.velX = player.velX + player.aceX * dt;
    new.velY = player.velY + player.aceY * dt;
    new.posX = player.posX + new.velX * dt;
    new.posY = player.posY + new.velY * dt;
    for (i = 0; i < 16; i++) {
        new.img[i] = player.img[i];
        new.aux[i] = player.aux[i];
        new.msk[i] = player.msk[i];
    }
    new.aceX = player.aceX;
    new.aceY = player.aceY;

    /* Ajustando posição caso tenha excedido o tamanho máximo ou mínimo */
    while (new.posX < minX || new.posX > maxX) {
        if      (new.posX > maxX) new.posX = new.posX - maxX + minY;
        else if (new.posX < minX) new.posX = maxX - minX + new.posX;
    }

    while (new.posY < minY || new.posY > maxX) {
        if      (new.posY > maxY) new.posY = new.posY - maxY + minY;
        else if (new.posY < minY) new.posY = maxY - minY + new.posY;
    }

    return new;
}

void showShip (ship player, WINDOW *w) {
    int x = CENTERX + player.posX - 23;
    int y = CENTERY - player.posY - 23;
    int index = getIndexByOrientation (player.velX, player.velY);

    SetMask (w, player.msk[index]);
    PutPic (w, player.img[index], 0, 0, 46, 46, x, y);
    UnSetMask (w);
}
