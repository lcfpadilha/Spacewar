/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       powerup.c
 *  Funções de manipulação e controle dos power Ups do jogo.
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

#define PU_RADIUS 7.5     /* raio da imagem do power Up             */
#define LIFE_TIME 7.0     /* tempo que o power up fica na tela      */
#define TIME_FOR_NEXT 4.5 /* tempo de espera para o próximo power Up*/

/*******************     Variáveis globais privadas     *********************/
static float t;     /* tempo transcorrido desde a criação/deleção do PWRUP. */
static POWERUP *pu; /* PWRUP atual. */

/***********************      Funções privadas      *************************/
static void selectPowerUp (ship *player, WINDOW *w) {
    PIC info, infoAux, img;
    MASK infoMASK;
    /* Power Up Foro Privilegiado */
    if (pu->type == 0) {
        img      = ReadPic (w, "img/powerUps/foro.xpm", NULL);
        infoMASK = NewMask (w, 720, 480);
        info     = ReadPic (w, "img/powerUps/foroInfo.xpm", NULL);
        infoAux  = ReadPic (w, "img/powerUps/foroInfo_MASK.xpm", infoMASK);

        PutPic(w, img, 0, 0, 250, 180, 235, 110);

        SetMask (w, infoMASK);
        PutPic (w, info, 0, 0, 720, 480, 0, 0);
        UnSetMask (w);

        player->shield = 1;
    }
    /* Power Up Delacao Premiada */
    else if (pu->type == 1) {
        img      = ReadPic(w, "img/powerUps/delacao.xpm", NULL);
        infoMASK = NewMask (w, 720, 480);
        info     = ReadPic (w, "img/powerUps/delacaoInfo.xpm", NULL);
        infoAux  = ReadPic (w, "img/powerUps/delacaoInfo_MASK.xpm", infoMASK);

        PutPic(w, img, 0, 0, 250, 167, 235, 116.5);

        SetMask (w, infoMASK);
        PutPic (w, info, 0, 0, 720, 480, 0, 0);
        UnSetMask (w);

        player->superShot = 1;
    }
    /* Power Up Triplex No Guaruja */
    else {
        img      = ReadPic(w, "img/powerUps/triplex.xpm", NULL);
        infoMASK = NewMask (w, 720, 480);
        info     = ReadPic (w, "img/powerUps/triplexInfo.xpm", NULL);
        infoAux  = ReadPic (w, "img/powerUps/triplexInfo_MASK.xpm", infoMASK);

        PutPic(w, img, 0, 0, 250, 150, 235, 125);

        SetMask (w, infoMASK);
        PutPic (w, info, 0, 0, 720, 480, 0, 0);
        UnSetMask (w);

        if (player->life < 100.0) player->life = 100.0;
    }
    sleep(5);
    FreePic (img);
    FreePic (info);
    FreePic (infoAux);
    FreePic (infoMASK);
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