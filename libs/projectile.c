/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       projectile.c
 *  Dependências:  getIndex.h xwc.h
 * 
 *  Arquivo .c de projectile.h
 *
 ******************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "getIndex.h"
#include "projectile.h"

#define G 1.0        // Constante gravitacional universal.
#define CENTERX 360  // Centro x da imagem.
#define CENTERY 240  // Centro y da imagem.

float accelerateProjectile (projectile p, float mass, float posX, float posY, 
                            char c) {
    float dx = posX - p.posX;
    float dy = posY - p.posY;
    float delta = sqrt (dx * dx + dy * dy);
    float accel = G * mass / (delta * delta);

    if (c == 'x') return accel * dx / delta;
    return accel * dy / delta;
}

projectile increaseTimeProjectile (projectile p, int maxX, int minX, 
                                                 int maxY, int minY, float dt) {
    projectile new;
    new.mass = p.mass;
    new.velX = p.velX + p.aceX * dt;
    new.velY = p.velY + p.aceY * dt;
    new.posX = p.posX + new.velX * dt;
    new.posY = p.posY + new.velY * dt;
    new.aceX = p.aceX;
    new.aceY = p.aceY;

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

void showBullet (projectile bullet, WINDOW *w, PIC bulletImg[], MASK bulletMsk[]) {
    int x = CENTERX + bullet.posX - 5;
    int y = CENTERY - bullet.posY - 5;
    int index = getIndexByOrientation (bullet.velX, bullet.velY);

    /* Desenhando o projétil. */
    SetMask (w, bulletMsk[index]);
    PutPic (w, bulletImg[index], 0, 0, 10, 10, x, y);
    UnSetMask (w);
}
