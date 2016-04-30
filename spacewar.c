/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       spacewar.c
 *  Compilação:    make
 *  Dependências:  planet.h ship.h projectile.h simulation.h xwc.h
 *  Execução:      ./spacewar t < entrada.txt
 * 
 *  Recebe as informações sobre um certo número de corpos no espaço (planeta, 
 *  naves e projéteis), e calcula as forças resultantes em cada corpo a cada t 
 *  instantes de um total de T instantes (t <= T), gerando imagens referentes 
 *  a esse processo.
 *
 ******************************************************************************/      
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libs/planet.h"
#include "libs/ship.h"
#include "libs/projectile.h"
#include "libs/simulation.h"

#define W 720  // Largura da janela.
#define H 480  // Altura da janela.

typedef struct {
    planet world;
    ship player1, player2;
    int numberOfProj;
    projectile *bullets;
} objects;

int main (int argc, char** argv) {
    /* Caso a biblioteca Xpm não esteja habilitada, o programa não funciona. */
    #ifdef NOXPM 
        printf ("Este programa só funciona com a biblioteca Xpm!")
    #else
    
    /* Declaração de variáveis */
    int numberOfProj, i, j;
    float timeOfProj, t, T, spentTime;

    /* Declaração dos corpos que serão postos no espaço. */
    planet world;
    ship player1, player2;
    projectile *bullets;

    /* Declaração de variáveis que vão gerar as imagens. */
    WINDOW *w;
    PIC bg, bulletImg[16], bulletAux[16];
    MASK bulletMsk[16];

    /* Inicialização de variáveis relacionadas à física do jogo */
    world.radius = world.mass = world.posX = world.posY = 0;
    player1.mass = player1.posX = player1.posY = 0;
    player1.velX = player1.velY = player1.aceX = player1.aceY = 0;
    player2.mass = player2.posX = player2.posY = 0;
    player2.velX = player2.velY = player2.aceX = player2.aceY = 0;

    /* Parâmetro de intervalo de atualização. */
    t = atof (argv[1]);

    /* Inicialização da janela e o background */
    w = InitGraph (W, H, "Space");
    bg = ReadPic (w, "img/scenery/space.xpm",  NULL);

    /* Inicialização do planeta */
    initPlanet (&world, w);

    /* Tempo total de simulação. */
    scanf ("%f", &T);

    /* Inicialização da primeira nave. */
    initPlayer (&player1, 1, w);

    /* Inicialização da segunda nave. */
    initPlayer (&player2, 2, w);

    /* Inicialização dos projéteis. */
    bullets = initProj (&numberOfProj, &timeOfProj);

    /* Inicialização das imagens dos projéteis. */
    initProjImage (bulletImg, bulletMsk, bulletAux, w);

    /* Tempo gasto até agora. */
    spentTime = 0.0;

    /* Simulando o espaço. */
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

    /* Desalocando o espaço e fechando a janela. */
    free (bullets);
    WDestroy(w);
    CloseGraph();

    #endif
    return EXIT_SUCCESS;
}
