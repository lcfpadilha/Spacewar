/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "getIndex.h"
#include "projectile.h"

#define G 1.0        /* Constante gravitacional universal. */
#define CENTERX 360  /* Centro x da imagem. */
#define CENTERY 240  /* Centro y da imagem. */
#define MAX_VEL 300  /* Velocidade maxima.   */
#define LIFE_T  2.0  /* Tempo de vida de um projétil */
#define LIFE_T_SPECIAL 3.5 /* Temp de vida de um projetil especial */
#define TRUE 1
#define FALSE 0

/*      Funções e variáveis privadas        */
static int size; /* tamanho do array de projectile  */

static float accelerateProjectile (projectile p, float mass, float posX, float posY, 
                            char c) {
    float dx = posX - p.posX;
    float dy = posY - p.posY;
    float delta = sqrt (dx * dx + dy * dy);
    float accel = G * mass / (delta * delta);

    if (c == 'x') return accel * dx / delta;
    return accel * dy / delta;
}

static projectile *resize (int max, int size, projectile *old) {
    int i;
    projectile *new;
    new = malloc (max * sizeof (projectile));
    for (i = 0; i < size; i++)
        new[i] = old[i];
    free (old);
    return new;
}

/*      Funções públicas        */
projectile *initProj () {
    projectile *bullets;

    size = 100;
    bullets = malloc (size * (sizeof (projectile)));

    return bullets;
}

void shoot (projectile *bullets, int n, ship player) {
    if (size == n - 1) {
        bullets = resize (2 * size, size, bullets);
        size = 2 * size;
    }
    bullets[n].posX = player.posX + cos (player.direction) * 30;
    bullets[n].posY = player.posY + sin (player.direction) * 30;
    bullets[n].velX = cos (player.direction) * 200;
    bullets[n].velY = sin (player.direction) * 200;
    bullets[n].aceX = bullets[n].aceY = 0.0;
    bullets[n].lifeTime = LIFE_T;
    if (player.superShot) {
        bullets[n].doubleDamage = TRUE;
        bullets[n].mass = 200.0;
    }
    else {
        bullets[n].doubleDamage = FALSE;
        bullets[n].mass = 2.0;
    }
    strcpy (bullets[n].playerID, player.name);
}

void deleteBullet (projectile *bullets, int n, int index) {
    int i;
    for (i = index + 1; i < n; i++)
        bullets[i - 1] = bullets [i];
}

void accelerateProjToWorld (projectile *bullet, planet world) {
    bullet->aceX += accelerateProjectile (*bullet, world.mass, world.posX, world.posY, 'x');
    bullet->aceY += accelerateProjectile (*bullet, world.mass, world.posX, world.posY, 'y');
}

void accelerateProjToShip (projectile *bullet, ship player) {
    bullet->aceX += accelerateProjectile (*bullet, player.mass, player.posX, player.posY, 'x');
    bullet->aceY += accelerateProjectile (*bullet, player.mass, player.posX, player.posY, 'y');
}

void accelerateProjToProj (projectile *bullet, projectile other) {
    bullet->aceX += accelerateProjectile (*bullet, other.mass, other.posX, other.posY, 'x');
    bullet->aceY += accelerateProjectile (*bullet, other.mass, other.posX, other.posY, 'y');
}

projectile increaseTimeProjectile (projectile p, int maxX, int minX, 
                                                 int maxY, int minY, float dt) {
    projectile *new = malloc (sizeof (projectile));
    new->mass = p.mass;
    new->velX = p.velX + p.aceX * dt;
    new->velY = p.velY + p.aceY * dt;
    if (new->velX > MAX_VEL) new->velX = MAX_VEL;
    if (new->velY > MAX_VEL) new->velY = MAX_VEL;
    new->posX = p.posX + new->velX * dt;
    new->posY = p.posY + new->velY * dt;
    new->aceX = p.aceX;
    new->aceY = p.aceY;
    new->doubleDamage = p.doubleDamage;
    new->lifeTime = p.lifeTime - dt;
    strcpy (new->playerID, p.playerID);
    /* Ajustando posição caso tenha excedido o tamanho máximo ou mínimo */
    while (new->posX < minX || new->posX > maxX) {
        if      (new->posX > maxX) new->posX = new->posX - maxX + minX;
        else if (new->posX < minX) new->posX = maxX - minX + new->posX;
    }

    while (new->posY < minY || new->posY > maxY) {
        if      (new->posY > maxY) new->posY = new->posY - maxY + minY;
        else if (new->posY < minY) new->posY = maxY - minY + new->posY;
    }
    return *new;
}

int projCollided (projectile bullet, planet world) {
    int dx   = world.posX - bullet.posX;
    int dy   = world.posY - bullet.posY;
    int dist = sqrt (dx * dx + dy * dy);

    return dist <= 5 + world.radius;
}

void initProjImage (PIC *bulletImg, PIC *bulletMsk, PIC *bulletAux, WINDOW *w) {
    int i;

    /* Definindo as imagens dos projéteis. */
    bulletImg[0] =  ReadPic (w, "img/bullet/bullet01.xpm", NULL);
    bulletImg[1] =  ReadPic (w, "img/bullet/bullet02.xpm", NULL);
    bulletImg[2] =  ReadPic (w, "img/bullet/bullet03.xpm", NULL);
    bulletImg[3] =  ReadPic (w, "img/bullet/bullet04.xpm", NULL);
    bulletImg[4] =  ReadPic (w, "img/bullet/bullet05.xpm", NULL);
    bulletImg[5] =  ReadPic (w, "img/bullet/bullet06.xpm", NULL);
    bulletImg[6] =  ReadPic (w, "img/bullet/bullet07.xpm", NULL);
    bulletImg[7] =  ReadPic (w, "img/bullet/bullet08.xpm", NULL);
    bulletImg[8] =  ReadPic (w, "img/bullet/bullet09.xpm", NULL);
    bulletImg[9] =  ReadPic (w, "img/bullet/bullet10.xpm", NULL);
    bulletImg[10] = ReadPic (w, "img/bullet/bullet11.xpm", NULL);
    bulletImg[11] = ReadPic (w, "img/bullet/bullet12.xpm", NULL);
    bulletImg[12] = ReadPic (w, "img/bullet/bullet13.xpm", NULL);
    bulletImg[13] = ReadPic (w, "img/bullet/bullet14.xpm", NULL);
    bulletImg[14] = ReadPic (w, "img/bullet/bullet15.xpm", NULL);
    bulletImg[15] = ReadPic (w, "img/bullet/bullet16.xpm", NULL);

    for (i = 0; i < 16; i++)
        bulletMsk[i] =  NewMask (w, 10, 10);

    bulletAux[0] =  ReadPic (w, "img/bulletMask/bulletMask01.xpm", bulletMsk[0]);
    bulletAux[1] =  ReadPic (w, "img/bulletMask/bulletMask02.xpm", bulletMsk[1]);
    bulletAux[2] =  ReadPic (w, "img/bulletMask/bulletMask03.xpm", bulletMsk[2]);
    bulletAux[3] =  ReadPic (w, "img/bulletMask/bulletMask04.xpm", bulletMsk[3]);
    bulletAux[4] =  ReadPic (w, "img/bulletMask/bulletMask05.xpm", bulletMsk[4]);
    bulletAux[5] =  ReadPic (w, "img/bulletMask/bulletMask06.xpm", bulletMsk[5]);
    bulletAux[6] =  ReadPic (w, "img/bulletMask/bulletMask07.xpm", bulletMsk[6]);
    bulletAux[7] =  ReadPic (w, "img/bulletMask/bulletMask08.xpm", bulletMsk[7]);
    bulletAux[8] =  ReadPic (w, "img/bulletMask/bulletMask09.xpm", bulletMsk[8]);
    bulletAux[9] =  ReadPic (w, "img/bulletMask/bulletMask10.xpm", bulletMsk[9]);
    bulletAux[10] = ReadPic (w, "img/bulletMask/bulletMask11.xpm", bulletMsk[10]);
    bulletAux[11] = ReadPic (w, "img/bulletMask/bulletMask12.xpm", bulletMsk[11]);
    bulletAux[12] = ReadPic (w, "img/bulletMask/bulletMask13.xpm", bulletMsk[12]);
    bulletAux[13] = ReadPic (w, "img/bulletMask/bulletMask14.xpm", bulletMsk[13]);
    bulletAux[14] = ReadPic (w, "img/bulletMask/bulletMask15.xpm", bulletMsk[14]);
    bulletAux[15] = ReadPic (w, "img/bulletMask/bulletMask16.xpm", bulletMsk[15]);
}

void showBullet (projectile bullet, WINDOW *w, PIC bulletImg[], MASK bulletMsk[]) {
    int x = CENTERX + bullet.posX - 5;
    int y = CENTERY - bullet.posY - 5;
    int index = getBulletIndexByOrientation (bullet.velX, bullet.velY);

    /* Desenhando o projétil. */
    SetMask (w, bulletMsk[index]);
    PutPic (w, bulletImg[index], 0, 0, 10, 10, x, y);
    UnSetMask (w);
    /* Desenhando o superShot */
    if (bullet.doubleDamage) 
        WArc(w, x, y, 0, 360*64, 10, 10, WNamedColor("DimGrey"));
}

void freeBulletImg (PIC bulletImg[], MASK bulletMsk[], PIC bulletAux[]) {
    int i;
    for (i = 0; i < 16; i++) {
        FreePic (bulletImg[i]);
        FreePic (bulletMsk[i]);
        FreePic (bulletAux[i]);
    }
}
