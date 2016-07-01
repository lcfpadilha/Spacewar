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
#include <unistd.h>
#include "ship.h"
#include "planet.h"
#include "powerup.h"


typedef struct {
    int type;
    float posX, posY, velX, velY;
} POWERUP;

#define PU_RADIUS 7.5
#define LIFE_TIME 7.0
#define TIME_FOR_NEXT 4.5

/*******************     Variáveis globais privadas     *********************/
static float t;
static POWERUP *pu;

/***********************      Funções privadas      *************************/
static void selectPowerUp (ship *player, WINDOW *w) {
    PIC img;
    if (pu->type == 0) {
        img = ReadPic(w, "img/powerUps/foro.xpm", NULL);
        PutPic(w, img, 0, 0, 250, 180, 235, 150);
        player->shield = 1;
    }
    else if (pu->type == 1) {
        img = ReadPic(w, "img/powerUps/delacao.xpm", NULL);
        PutPic(w, img, 0, 0, 250, 167, 235, 156.5);
        player->superShot = 1;
    }
    else {
        img = ReadPic(w, "img/powerUps/triplex.xpm", NULL);
        PutPic(w, img, 0, 0, 250, 150, 235, 165);
        if (player->life < 100.0) player->life = 100.0;
    }
    sleep(2);
    FreePic (img);
} 

/***********************      Funções públicas      *************************/
void initPowerUp () {
    t = 0.0;
    pu = NULL;
}

void createPowerUp (planet world, float dt) {
    float ang;
    srand (time (NULL));
    t += dt;
    if (pu != NULL) {
        if (t > LIFE_TIME) {
            free (pu);
            pu = NULL;
            t = 0.0;
        }
        else {
            pu->posX = pu->posX + pu->velX * dt;
            pu->posY = pu->posY + pu->velY * dt;

            if (pu->posX > 360) pu->posX = pu->posX - 720;
            else if (pu->posX < -360) pu->posX = pu->posX + 720;

            if (pu->posY > 240) pu->posY = pu->posY - 480;
            else if (pu->posY < -240) pu->posY = pu->posY + 480;
        }
    }
    else {
        if (t > TIME_FOR_NEXT) {
            srand (time (NULL));
            pu = malloc (sizeof (POWERUP));
            pu->type = (int) (3 * (rand() / (float) RAND_MAX));
            pu->type = 1;
            ang = 2 * M_PI * rand() / (float) RAND_MAX;
            pu->posX = (world.radius + 20.0) * cos (ang);
            pu->posY = (world.radius + 20.0)* sin (ang);
            pu->velX = 20*cos(ang);
            pu->velY = 20*sin(ang);
            t = 0.0;
        }
    }
}

void checkPowerUpCollision (planet world, ship *player1, ship *player2, WINDOW *w) {
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
        dxP2 = player2->posX - pu->posX;
        dyP2 = player2->posY - pu->posY;
        if (sqrt (dxPlanet * dxPlanet + dyPlanet * dyPlanet) < world.radius + PU_RADIUS) {
            free(pu);
            pu = NULL;
            t = 0.0;
        }
        else if (sqrt (dxP1 * dxP1 + dyP1 * dyP1) < 23 + PU_RADIUS) {
            selectPowerUp (player1, w);
            free(pu);
            pu = NULL;
            t = 0.0;
        }
        else if (sqrt (dxP2 * dxP2 + dyP2 * dyP2) < 23 + PU_RADIUS) {
            selectPowerUp (player2, w);
            free(pu);
            pu = NULL;
            t = 0.0;
        }
    }
}

void showPowerUp (WINDOW *w) {
    int x;
    int y;
    if (pu != NULL) {
        x = 360 + pu->posX - PU_RADIUS;
        y = 240 - pu->posY - PU_RADIUS;
        if (pu->type == 0)
            WFillArc(w, x , y, 0, 360*64, 2 * PU_RADIUS, 2 * PU_RADIUS, WNamedColor("gold"));
        else if (pu->type == 1)
            WFillArc(w, x, y, 0, 360*64, 2 * PU_RADIUS, 2 * PU_RADIUS, WNamedColor("DimGrey"));
        else if (pu->type == 2)
            WFillArc(w, x, y, 0, 360*64, 2 * PU_RADIUS, 2 * PU_RADIUS, WNamedColor("light green"));
    }
}