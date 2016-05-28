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
#include "libs/error.h"
#include "libs/planet.h"
#include "libs/ship.h"
#include "libs/projectile.h"
#include "libs/controller.h"

#define W 720  /* Largura da janela. */
#define H 480  /* Altura da janela. */


int main (int argc, char** argv) {
    /* Caso a biblioteca Xpm não esteja habilitada, o programa não funciona. */
    #ifdef NOXPM 
        printf ("Este programa só funciona com a biblioteca Xpm!")
    #else
    
    /* Declaração de variáveis */
    int numberOfProj, i, j, ret, collideP1 = FALSE, collideP2 = FALSE;
    float t, T, spentTime;

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

    /* Inicialização da janela */
    w = InitGraph (W, H, "Space");

    /* Inicialização da controller */
    initDetection (w);

    /* Inicialização da imagem de fundo */
    bg = ReadPic (w, "img/scenery/space.xpm",  NULL);

    /* Inicialização do planeta */
    initPlanet (&world, w);

    /* Tempo total de simulação. */
    ret = scanf ("%f", &T);

    hasError (ret != 1);

    /* Inicialização da primeira nave. */
    initPlayer (&player1, 1, w);

    /* Inicialização da segunda nave. */
    initPlayer (&player2, 2, w);

    /* Inicialização dos projéteis. */
    bullets = initProj (&numberOfProj);

    /* Inicialização das imagens dos projéteis. */
    initProjImage (bulletImg, bulletMsk, bulletAux, w);

    /* Tempo gasto até agora. */
    spentTime = 0.0;

    /* Simulando o espaço. */
    while (spentTime < T && !collideP1 && !collideP2) {
        /* Verifica se alguma tecla foi pressionada */
        movePlayer (&player1, &player2, bullets, &numberOfProj, w);

        /* Calculando a aceleração da nave pĺayer1. */
        accelerateShipToWorld (&player1, world);
        accelerateShipToShip  (&player1, player2);

        /*Calculando a aceleração da nave player2. */
        accelerateShipToWorld (&player2, world);
        accelerateShipToShip  (&player2, player1);

        /* Calculando a aceleração dos projeteis, se eles (ainda) existirem. */
        for (i = 0; i < numberOfProj; i++) {
            accelerateShipToProj (&player1, bullets[i]);
            accelerateShipToProj (&player2, bullets[i]);

            accelerateProjToWorld (&bullets[i], world);
            accelerateProjToShip  (&bullets[i], player1);
            accelerateProjToShip  (&bullets[i], player2);

            for (j = 0; j < numberOfProj; j++)
                if (i != j)
                    accelerateProjToProj (&bullets[i], bullets[j]);
        }
        /* Mudando a posição dos objetos e imprimindo a atualização. */
        player1 = increaseTimeShip (player1, W/2, -W/2, H/2, -H/2, t);
        player2 = increaseTimeShip (player2, W/2, -W/2, H/2, -H/2, t);
        
        /* Mostrando o cenário. */
        showScene (world, w, bg);

        /* Mostrando as naves na tela. */
        showShip (player1, w);
        showShip (player2, w);

        for (i = 0; i < numberOfProj; i++) {
            if (bullets[i].lifeTime > 0) {
                bullets[i] = increaseTimeProjectile (bullets[i], W/2, -W/2, H/2, -H/2, t);
                
                if (projCollided (bullets[i], world))
                    deleteBullet (bullets, numberOfProj--, i);
                if (hasCollidedProj (player1, bullets[i])) 
                    collideP1 = TRUE;
                else if (hasCollidedProj (player2, bullets[i])) 
                    collideP2 = TRUE;

                /* Mostrando os projeteis */
                showBullet (bullets[i], w, bulletImg, bulletMsk);
                bullets[i].aceX = bullets[i].aceY = 0.0;
            }
            else deleteBullet (bullets, numberOfProj--, i);
        }

        player1.aceX = player1.aceY = 0.0;
        player2.aceX = player2.aceY = 0.0;

        /* Verifica colisão das naves e exibe na saída padrão o resultado. */
        if (hasCollidedShip (player1, player2)) 
            collideP1 = collideP2 = TRUE;
        else if (hasCollidedPlanet (player1, world)) 
            collideP1 = TRUE;
        else if (hasCollidedPlanet (player2, world)) 
            collideP2 = TRUE;

        /* Mostrando as coisas na tela por t segundos */
        usleep (t * 1000000);

        /* Aumentando o tempo que passou. */
        spentTime += t;
    }
    if (collideP1 && collideP2)
        printf ("As duas naves colidiram, empate :(\n");
    else if (collideP1)
        printf("A nave 1 explodiu!\n");
    else if (collideP2)
        printf("A nave 2 exploriu\n");
    quitDetection (w);
    /* Desalocando o espaço e fechando a janela. */
    free (bullets);
    WDestroy(w);
    CloseGraph();

    #endif
    return EXIT_SUCCESS;
}
