/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       simulation.c
 *  Dependências:  planet.h ship.h projectile.h getIndex.h xwc.h
 * 
 *  Arquivo .c de simulation.h
 *
 ******************************************************************************/ 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "planet.h"
#include "ship.h"
#include "projectile.h"
#include "getIndex.h"
#include "simulation.h"

#define W 720            // Largura da janela.
#define H 480            // Altura da janela.
#define CENTERX 360      // Centro x da janela.
#define CENTERY 240      // Centro y da janela.
#define PI 3.14159265    // Pi.

/* Simula a física do jogo. */
void simulation (float spentTime, float t, float T, planet world, ship player1, 
                 ship player2, projectile bullets[], PIC bulletImg[], 
                 PIC bulletMsk[], int numberOfProj, float timeOfProj, WINDOW *w,
                 PIC bg) {

    int i, j;

    while (spentTime < T) {
        /* Calculando a aceleração da nave pĺayer1. */
        player1.aceX += accelerateShip (player1, world.mass, world.posX, 
                                        world.posY, 'x');
        player1.aceY += accelerateShip (player1, world.mass, world.posX, 
                                        world.posY, 'y');

        player1.aceX += accelerateShip (player1, player2.mass, player2.posX, 
                                        player2.posY, 'x');
        player1.aceY += accelerateShip (player1, player2.mass, player2.posX, 
                                        player2.posY, 'y');

        /*Calculando a aceleração da nave player2. */
        player2.aceX += accelerateShip (player2, world.mass, world.posX, 
                                        world.posY, 'x');
        player2.aceY += accelerateShip (player2, world.mass, world.posX, 
                                        world.posY, 'y');

        player2.aceX += accelerateShip (player2, player1.mass, player1.posX, 
                                        player1.posY, 'x');
        player2.aceY += accelerateShip (player2, player1.mass, player1.posX, 
                                        player1.posY, 'y');

        /* Calculando a aceleração dos projeteis, se eles (ainda) existirem. */
        if (spentTime < timeOfProj) {
            for (i = 0; i < numberOfProj; i++) {
                player1.aceX += accelerateShip (player1, bullets[i].mass, 
                                                bullets[i].posX, 
                                                bullets[i].posY, 'x');
                player1.aceY += accelerateShip (player1, bullets[i].mass, 
                                                bullets[i].posX, 
                                                bullets[i].posY, 'y');
            }
            
            for (i = 0; i < numberOfProj; i++) {
                player2.aceX += accelerateShip (player2, bullets[i].mass, 
                                                bullets[i].posX, 
                                                bullets[i].posY, 'x');
                player2.aceY += accelerateShip (player2, bullets[i].mass, 
                                                bullets[i].posX, 
                                                bullets[i].posY, 'y');
            }

            for (i = 0; i < numberOfProj; i++) {
                bullets[i].aceX += accelerateProjectile (bullets[i], world.mass,
                                                         world.posX, world.posY,
                                                         'x');
                bullets[i].aceY += accelerateProjectile (bullets[i], world.mass,
                                                         world.posX, world.posY,
                                                         'y');

                bullets[i].aceX += accelerateProjectile (bullets[i], 
                                                         player1.mass, 
                                                         player1.posX, 
                                                         player1.posY, 'x');
                bullets[i].aceY += accelerateProjectile (bullets[i], 
                                                         player1.mass, 
                                                         player1.posX, 
                                                         player1.posY, 'y');

                bullets[i].aceX += accelerateProjectile (bullets[i], 
                                                         player2.mass, 
                                                         player2.posX, 
                                                         player2.posY, 'x');
                bullets[i].aceY += accelerateProjectile (bullets[i], 
                                                         player2.mass, 
                                                         player2.posX, 
                                                         player2.posY, 'y');

                for (j = 0; j < numberOfProj; j++) {
                    if (i != j) {
                        bullets[i].aceX += accelerateProjectile (bullets[i], 
                                                                 bullets[j].mass, 
                                                                 bullets[j].posX, 
                                                                 bullets[j].posY,
                                                                 'x');
                        bullets[i].aceY += accelerateProjectile (bullets[i], 
                                                                 bullets[j].mass, 
                                                                 bullets[j].posX, 
                                                                 bullets[j].posY,
                                                                 'y');
                    }
                }
            }
        }

        /* Mudando a posição dos objetos e imprimindo a atualização. */
        player1 = increaseTimeShip (player1, W/2, -W/2, H/2, -H/2, t);
        player2 = increaseTimeShip (player2, W/2, -W/2, H/2, -H/2, t);

        /* Mostrando o cenário. */
        showScene (world, w, bg);

        /* Mostrando as naves na tela. */
        showShip (player1, w);
        showShip (player2, w);

        for (i = 0; spentTime < timeOfProj && i < numberOfProj; i++) {
            bullets[i] = increaseTimeProjectile (bullets[i], W/2, -W/2, H/2, 
                                                 -H/2, t);
            
            /* Mostrando os projeteis */
            showBullet (bullets[i], w, bulletImg, bulletMsk);
            bullets[i].aceX = bullets[i].aceY = 0.0;
        }
        player1.aceX = player1.aceY = 0.0;
        player2.aceX = player2.aceY = 0.0;

        /* Mostrando as coisas na tela por t segundos */
        usleep (t * 1000000);

        /* Aumentando o tempo que passou. */
        spentTime += t;
    }
}
