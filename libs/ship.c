/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
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

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "getIndex.h"
#include "ship.h"
#include "error.h"


#define G 1.0        /* Constante gravitacional universal. */
#define CENTERX 360  /* Centro x da imagem. */
#define CENTERY 240  /* Centro y da imagem. */
#define MAX_VEL 200 /* Velocidade máxima da nave*/

/*      Funções privadas        */
static float accelerateShip (ship s, float mass, float posX, float posY, char c) {
    float dx = posX - s.posX;
    float dy = posY - s.posY;
    float delta = sqrt (dx * dx + dy * dy);
    float accel = G * mass / (delta * delta);

    if (c == 'x') return accel * dx / delta;
    return accel * dy / delta;
}


/*        Funções Públicas        */
void initPlayer (ship *p, int playerID, WINDOW *w) {
    int i, ret;
    
    /* Leitura dos dados do player */
    ret = scanf ("%s %f %f %f %f %f", p->name, &p->mass, &p->posX, &p->posY, &p->velX, &p->velY);
    hasError (ret != 6);
    
    /* Aceleração iniciada com 0 */
    p->aceX = p->aceY = 0.0;
    
    /* Carga de tiros inicializada com 1*/
    p->charge = 4;
    p->timeForCharge = 0.0;

    /* Inicializa as máscaras */
    for (i = 0; i < 16; i++)
        p->msk[i] = NewMask (w, 46, 46);

    /* Inicializa as imagens do player 1 e a sua direção*/
    if (playerID == 1) {
        p->direction = 2 * M_PI;
        p->img[0] =  ReadPic (w, "img/playerOne/playerOne01.xpm", NULL);
        p->img[1] =  ReadPic (w, "img/playerOne/playerOne02.xpm", NULL);
        p->img[2] =  ReadPic (w, "img/playerOne/playerOne03.xpm", NULL);
        p->img[3] =  ReadPic (w, "img/playerOne/playerOne04.xpm", NULL);
        p->img[4] =  ReadPic (w, "img/playerOne/playerOne05.xpm", NULL);
        p->img[5] =  ReadPic (w, "img/playerOne/playerOne06.xpm", NULL);
        p->img[6] =  ReadPic (w, "img/playerOne/playerOne07.xpm", NULL);
        p->img[7] =  ReadPic (w, "img/playerOne/playerOne08.xpm", NULL);
        p->img[8] =  ReadPic (w, "img/playerOne/playerOne09.xpm", NULL);
        p->img[9] =  ReadPic (w, "img/playerOne/playerOne10.xpm", NULL);
        p->img[10] = ReadPic (w, "img/playerOne/playerOne11.xpm", NULL);
        p->img[11] = ReadPic (w, "img/playerOne/playerOne12.xpm", NULL);
        p->img[12] = ReadPic (w, "img/playerOne/playerOne13.xpm", NULL);
        p->img[13] = ReadPic (w, "img/playerOne/playerOne14.xpm", NULL);
        p->img[14] = ReadPic (w, "img/playerOne/playerOne15.xpm", NULL);
        p->img[15] = ReadPic (w, "img/playerOne/playerOne16.xpm", NULL);

        p->aux[0] =  ReadPic (w, "img/playerMask/playerMask01.xpm", p->msk[0]);
        p->aux[1] =  ReadPic (w, "img/playerMask/playerMask02.xpm", p->msk[1]);
        p->aux[2] =  ReadPic (w, "img/playerMask/playerMask03.xpm", p->msk[2]);
        p->aux[3] =  ReadPic (w, "img/playerMask/playerMask04.xpm", p->msk[3]);
        p->aux[4] =  ReadPic (w, "img/playerMask/playerMask05.xpm", p->msk[4]);
        p->aux[5] =  ReadPic (w, "img/playerMask/playerMask06.xpm", p->msk[5]);
        p->aux[6] =  ReadPic (w, "img/playerMask/playerMask07.xpm", p->msk[6]);
        p->aux[7] =  ReadPic (w, "img/playerMask/playerMask08.xpm", p->msk[7]);
        p->aux[8] =  ReadPic (w, "img/playerMask/playerMask09.xpm", p->msk[8]);
        p->aux[9] =  ReadPic (w, "img/playerMask/playerMask10.xpm", p->msk[9]);
        p->aux[10] = ReadPic (w, "img/playerMask/playerMask11.xpm", p->msk[10]);
        p->aux[11] = ReadPic (w, "img/playerMask/playerMask12.xpm", p->msk[11]);
        p->aux[12] = ReadPic (w, "img/playerMask/playerMask13.xpm", p->msk[12]);
        p->aux[13] = ReadPic (w, "img/playerMask/playerMask14.xpm", p->msk[13]);
        p->aux[14] = ReadPic (w, "img/playerMask/playerMask15.xpm", p->msk[14]);
        p->aux[15] = ReadPic (w, "img/playerMask/playerMask16.xpm", p->msk[15]);
    }

    /* Inicializa as imagens do player 2 */
    else {
        p->direction = M_PI;
        p->img[0] =  ReadPic (w, "img/playerTwo/playerTwo01.xpm", NULL);
        p->img[1] =  ReadPic (w, "img/playerTwo/playerTwo02.xpm", NULL);
        p->img[2] =  ReadPic (w, "img/playerTwo/playerTwo03.xpm", NULL);
        p->img[3] =  ReadPic (w, "img/playerTwo/playerTwo04.xpm", NULL);
        p->img[4] =  ReadPic (w, "img/playerTwo/playerTwo05.xpm", NULL);
        p->img[5] =  ReadPic (w, "img/playerTwo/playerTwo06.xpm", NULL);
        p->img[6] =  ReadPic (w, "img/playerTwo/playerTwo07.xpm", NULL);
        p->img[7] =  ReadPic (w, "img/playerTwo/playerTwo08.xpm", NULL);
        p->img[8] =  ReadPic (w, "img/playerTwo/playerTwo09.xpm", NULL);
        p->img[9] =  ReadPic (w, "img/playerTwo/playerTwo10.xpm", NULL);
        p->img[10] = ReadPic (w, "img/playerTwo/playerTwo11.xpm", NULL);
        p->img[11] = ReadPic (w, "img/playerTwo/playerTwo12.xpm", NULL);
        p->img[12] = ReadPic (w, "img/playerTwo/playerTwo13.xpm", NULL);
        p->img[13] = ReadPic (w, "img/playerTwo/playerTwo14.xpm", NULL);
        p->img[14] = ReadPic (w, "img/playerTwo/playerTwo15.xpm", NULL);
        p->img[15] = ReadPic (w, "img/playerTwo/playerTwo16.xpm", NULL);

        p->aux[0] =  ReadPic (w, "img/playerMask/playerMask01.xpm", p->msk[0]);
        p->aux[1] =  ReadPic (w, "img/playerMask/playerMask02.xpm", p->msk[1]);
        p->aux[2] =  ReadPic (w, "img/playerMask/playerMask03.xpm", p->msk[2]);
        p->aux[3] =  ReadPic (w, "img/playerMask/playerMask04.xpm", p->msk[3]);
        p->aux[4] =  ReadPic (w, "img/playerMask/playerMask05.xpm", p->msk[4]);
        p->aux[5] =  ReadPic (w, "img/playerMask/playerMask06.xpm", p->msk[5]);
        p->aux[6] =  ReadPic (w, "img/playerMask/playerMask07.xpm", p->msk[6]);
        p->aux[7] =  ReadPic (w, "img/playerMask/playerMask08.xpm", p->msk[7]);
        p->aux[8] =  ReadPic (w, "img/playerMask/playerMask09.xpm", p->msk[8]);
        p->aux[9] =  ReadPic (w, "img/playerMask/playerMask10.xpm", p->msk[9]);
        p->aux[10] = ReadPic (w, "img/playerMask/playerMask11.xpm", p->msk[10]);
        p->aux[11] = ReadPic (w, "img/playerMask/playerMask12.xpm", p->msk[11]);
        p->aux[12] = ReadPic (w, "img/playerMask/playerMask13.xpm", p->msk[12]);
        p->aux[13] = ReadPic (w, "img/playerMask/playerMask14.xpm", p->msk[13]);
        p->aux[14] = ReadPic (w, "img/playerMask/playerMask15.xpm", p->msk[14]);
        p->aux[15] = ReadPic (w, "img/playerMask/playerMask16.xpm", p->msk[15]);
    }
}

void accelerateShipToWorld (ship *player, planet world) {
    player->aceX += accelerateShip (*player, world.mass, world.posX, world.posY, 'x');
    player->aceY += accelerateShip (*player, world.mass, world.posX, world.posY, 'y');
}

void accelerateShipToShip (ship *player, ship other) {
    player->aceX += accelerateShip (*player, other.mass, other.posX, other.posY, 'x');
    player->aceY += accelerateShip (*player, other.mass, other.posX, other.posY, 'y');
} 

void accelerateShipToProj (ship *player, projectile b) {
    player->aceX += accelerateShip (*player, b.mass, b.posX, b.posY, 'x');
    player->aceY += accelerateShip (*player, b.mass, b.posX, b.posY, 'y');
}

int hasCollidedShip (ship player, ship other) {
    int dx   = other.posX - player.posX;
    int dy   = other.posY - player.posY;
    int dist = sqrt (dx * dx + dy * dy);

    return dist <= 46;
}

int hasCollidedPlanet (ship player, planet world) {
    int dx   = world.posX - player.posX;
    int dy   = world.posY - player.posY;
    int dist = sqrt (dx * dx + dy * dy);

    return dist <= 23 + world.radius;
}

int hasCollidedProj (ship player, projectile bullet) {
    int dx   = bullet.posX - player.posX;
    int dy   = bullet.posY - player.posY;
    int dist = sqrt (dx * dx + dy * dy);

    return dist <= 28;
}

ship increaseTimeShip (ship player, int maxX, int minX, 
                                    int maxY, int minY, float dt) {
    int i;
    ship new;
    strcpy (new.name, player.name);
    new.mass = player.mass;
    new.velX = player.velX + player.aceX * dt;
    new.velY = player.velY + player.aceY * dt;
    if (new.velX > MAX_VEL) new.velX = MAX_VEL;
    if (new.velY > MAX_VEL) new.velY = MAX_VEL;
    new.posX = player.posX + new.velX * dt;
    new.posY = player.posY + new.velY * dt;
    for (i = 0; i < 16; i++) {
        new.img[i] = player.img[i];
        new.aux[i] = player.aux[i];
        new.msk[i] = player.msk[i];
    }
    new.aceX = player.aceX;
    new.aceY = player.aceY;
    if (player.charge < 4) {
        new.timeForCharge = player.timeForCharge + dt;
        if (new.timeForCharge >= 1.0) {
            new.charge = player.charge + 1;
            new.timeForCharge = 0.0;
        }
        else new.charge = player.charge;
    }
    else {
        new.charge = player.charge;
        new.timeForCharge = 0.0;
    }

    new.direction = player.direction;
    while (new.direction > 2 * M_PI || new.direction <= 0.0) {
        if (new.direction > 2 * M_PI)
            new.direction = new.direction - 2 * M_PI;
        else 
            new.direction = new.direction + 2 * M_PI;
    }

    /* Ajustando posição caso tenha excedido o tamanho máximo ou mínimo */
    while (new.posX < minX || new.posX > maxX) {
        if      (new.posX > maxX) new.posX = new.posX - maxX + minX;
        else if (new.posX < minX) new.posX = maxX - minX + new.posX;
    }

    while (new.posY < minY || new.posY > maxY) {
        if      (new.posY > maxY) new.posY = new.posY - maxY + minY;
        else if (new.posY < minY) new.posY = maxY - minY + new.posY;
    }

    return new;
}

void showShip (ship player, WINDOW *w) {
    int x = CENTERX + player.posX - 23;
    int y = CENTERY - player.posY - 23;
    int index = getIndexByOrientation (player.direction);
    
    SetMask (w, player.msk[index]);
    PutPic (w, player.img[index], 0, 0, 46, 46, x, y);
    UnSetMask (w);
}