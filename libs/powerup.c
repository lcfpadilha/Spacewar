/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       powerup.c
 *  Dependências:  ship.h xwc.h
 *
 ******************************************************************************/
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "planet.h"
#include "powerup.h"


typedef struct {
    int type;
    float posX, posY, velX, velY;
} POWERUP;
#define PURADIUS 7.5

/*******************     Variáveis globais privadas     *********************/
static float t;
static POWERUP *pu;

void initPowerUp () {
    t = 0.0;
    pu = NULL;
}

void createPowerUp (planet world, float dt) {
    float ang;
    srand (time (NULL));
    if (pu != NULL) {
        pu->posX = pu->posX + pu->velX * dt;
        pu->posY = pu->posY + pu->velY * dt;

        if (pu->posX > 360) pu->posX = pu->posX - 720;
        else if (pu->posX < -360) pu->posX = pu->posX + 720;

        if (pu->posY > 240) pu->posY = pu->posY - 480;
        else if (pu->posY < -240) pu->posY = pu->posY + 480;
    }
    else {
        t += dt;
        if (t > 2.5) {
            srand (time (NULL));
            pu = malloc (sizeof (POWERUP));
            pu->type = (int) (3 * (rand() / (float) RAND_MAX));
            ang = 2 * M_PI * rand() / (float) RAND_MAX;
            pu->posX = (world.radius + 20.0) * cos (ang);
            pu->posY = (world.radius + 20.0)* sin (ang);
            pu->velX = 20*cos(ang);
            pu->velY = 20*sin(ang);
            t = 0.0;
        }
    }
}

void checkPowerUpCollision (planet world, ship &player1, ship &player2) {
    float dxPlanet;
    float dyPlanet;
    float dxP1;
    float dyP1;
    float dxP2;
    float dyP2;
    if (pu != NULL) {
        dxPlanet = world.posX - pu->posX;
        dyPlanet = world.posY - pu->posY;
        dxP1 = player1->posX - pu->posX;
        dyP1 = player1->posY - pu->posY;
        dxP2 = player1->posX - pu->posX;
        dyP2 = player1->posY - pu->posY;
        if (sqrt (dxPlanet * dxPlanet + dyPlanet * dyPlanet) < world.radius + PURADIUS) {
            free(pu);
            pu = NULL;
        }
        else if (sqrt (dxP1 * dxP1 + dyP1 * dyP1) < 23 + PURADIUS) {
            printf("COLISAO COM PLAYER 1\n");
            free(pu);
            pu = NULL;
        }
        else if (sqrt (dxP2 * dxP2 + dyP2 * dyP2) < 23 + PURADIUS) {
            printf("COLISAO COM PLAYER 2\n");
            free(pu);
            pu = NULL;
        }
    }
}

void showPowerUp (WINDOW *w) {
    if (pu != NULL) {
        if (pu->type == 0)
            WFillArc(w, 360 + pu->posX, 240 - pu->posY, 0, 360*64, 2 * PURADIUS, 2 * PURADIUS, WNamedColor("gold"));
        else if (pu->type == 1)
            WFillArc(w, 360 + pu->posX, 240 - pu->posY, 0, 360*64, 2 * PURADIUS, 2 * PURADIUS, WNamedColor("DimGrey"));
        else if (pu->type == 2)
            WFillArc(w, 360 + pu->posX, 240 - pu->posY, 0, 360*64, 2 * PURADIUS, 2 * PURADIUS, WNamedColor("light green"));
    }
}