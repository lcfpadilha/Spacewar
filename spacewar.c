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

void showMainMenu (WINDOW *w);

int main (int argc, char** argv) {
    /* Caso a biblioteca Xpm não esteja habilitada, o programa não funciona. */
    #ifdef NOXPM 
        printf ("Este programa só funciona com a biblioteca Xpm!")
    #else
    
    /* Declaração de variáveis */
    int numberOfProj, i, j, ret; 
    int changeIndex = FALSE, collideP1 = FALSE, collideP2 = FALSE;
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
    w = InitGraph (W, H, "Spacewar");

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

    /* Inicia as imagens de fundo e espera o usuário digitar enter */
    showMainMenu (w);
    enterCheck (w, 3);

    /* Simulando o espaço. */
    while (spentTime < T && !collideP1 && !collideP2) {
        /* Verifica se alguma tecla foi pressionada */
        movePlayer (&player1, &player2, bullets, &numberOfProj, w, t);

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
        i = 0;

        /* Mostrando todos os projéteis que ainda estão vivos */
        while (i < numberOfProj) {
            /* Deleta aqueles que nao existem mais */
            if (bullets[i].lifeTime <= 0 || projCollided (bullets[i], world)) 
                deleteBullet (bullets, numberOfProj--, i);
            else {
                changeIndex = TRUE;
                bullets[i] = increaseTimeProjectile (bullets[i], W/2, -W/2, H/2, -H/2, t);
                
                /* Se algum colidiu com alguma nave, deleta o projétil e ainda retira vida
                   da respectiva nave.                                                   */
                if (hasCollidedProj (player1, bullets[i])) {
                    player1.life -= 34;
                    if (player1.life <= 0)
                        collideP1 = TRUE;
                    deleteBullet (bullets, numberOfProj--, i);
                    changeIndex = FALSE;
                }
                else if (hasCollidedProj (player2, bullets[i])) {
                    player2.life -= 34;
                    if (player2.life <= 0)
                        collideP2 = TRUE;
                    deleteBullet (bullets, numberOfProj--, i);
                    changeIndex = FALSE;
                }

                /* Mostrando os projeteis */
                if (changeIndex) {
                    showBullet (bullets[i], w, bulletImg, bulletMsk);
                    bullets[i].aceX = bullets[i].aceY = 0.0;
                    i++;
                }
            }
        }
        showShipLife (player1, player2, w);

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
        printf("A nave 2 explodiu\n");
    quitDetection (w);
    /* Desalocando o espaço e fechando a janela. */
    free (bullets);
    bullets = NULL;
    WDestroy(w);
    CloseGraph();

    #endif
    return EXIT_SUCCESS;
}

void showMainMenu (WINDOW *w) {
    PIC menu = ReadPic (w, "img/etc/spacewar.xpm", NULL);
    PutPic (w, menu, 0, 0, 720, 480, 0, 0);
    FreePic (menu);
}
