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
#include "libs/controller.h"
#include "libs/scenes.h"
#include "libs/ship.h"
#include "libs/planet.h"
#include "libs/powerup.h"
#include "libs/projectile.h"

#define W 720  /* Largura da janela. */
#define H 480  /* Altura da janela. */

int main (int argc, char** argv) {
    /* Caso a biblioteca Xpm não esteja habilitada, o programa não funciona. */
    #ifdef NOXPM 
        printf ("Este programa só funciona com a biblioteca Xpm!")
    #else
    
    /* Declaração de variáveis */
    int numberOfProj, i, j, dmg; 
    int changeIndex = FALSE, collideP1 = FALSE, collideP2 = FALSE;
    float t;

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
    t = 0.01666667;

    /* Inicialização da janela */
    w = InitGraph (W, H, "Spacewar");

    /* Inicialização da controller */
    initDetection (w);

    /* Inicialização da imagem de fundo */
    bg = ReadPic (w, "img/scenery/space.xpm",  NULL);

    /* Inicialização do planeta */
    initPlanet (&world, w);

    /* Inicialização da primeira nave. */
    initPlayer (&player1, 1, w);

    /* Inicialização da segunda nave. */
    initPlayer (&player2, 2, w);

    /* Inicialização dos power Ups*/
    initPowerUp ();

    /* Inicialização dos projéteis. */
    bullets = initProj ();
    numberOfProj = 0;

    /* Inicialização das imagens dos projéteis. */
    initProjImage (bulletImg, bulletMsk, bulletAux, w);

    /* Inicia as imagens de fundo e espera o usuário digitar enter */
    showMainMenu (w);
    enterCheck (w, 3);

    /* Simulando o espaço. */
    while (!collideP1 && !collideP2) {
        /* Verifica se alguma tecla foi pressionada */
        movePlayer (&player1, &player2, bullets, &numberOfProj, w, t);
        
        /* Cria um powerUp ou movimenta o já existente */
        createPowerUp (world, t);

        /* Calculando a aceleração da nave pĺayer1. */
        accelerateShipToWorld (&player1, world);
        accelerateShipToShip  (&player1, player2);

        /*Calculando a aceleração da nave player2. */
        accelerateShipToWorld (&player2, world);
        accelerateShipToShip  (&player2, player1);

        /* Calculando a aceleração dos projeteis ativos. */
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
        
        /* Mostrando o powerUp se houver e checando colisão. */
        showPowerUp (w);
        checkPowerUpCollision (world, &player1, &player2, w);

        i = 0;
        
        /* Mostrando todos os projéteis que ainda estão vivos */
        while (i < numberOfProj) {
            /* Deleta aqueles que nao existem mais */
            if (bullets[i].lifeTime <= 0 || projCollided (bullets[i], world)) 
                deleteBullet (bullets, numberOfProj--, i);
            else {
                changeIndex = TRUE;
                bullets[i] = increaseTimeProjectile (bullets[i], W/2, -W/2, H/2, -H/2, t);
                if (bullets[i].doubleDamage)
                    dmg = 68;
                else
                    dmg = 34;
                /* Se algum colidiu com alguma nave, deleta o projétil e nao anda o índice,
                  pois bullets[i] vai ser diferente e ainda retira vida da respectiva nave.*/
                if (hasCollidedProj (player1, bullets[i])) {
                    if (!player1.shield) {
                        player1.life -= dmg;
                        if (player1.life <= 0)
                            collideP1 = TRUE;
                    }
                    deleteBullet (bullets, numberOfProj--, i);
                    changeIndex = FALSE;
                }
                else if (hasCollidedProj (player2, bullets[i])) {
                    if (!player2.shield) {
                        player2.life -= dmg;
                        if (player2.life <= 0)
                            collideP2 = TRUE;
                    }
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
        /* Mostra a vida das naves na parte superior da tela */
        showShipLife (player1, player2, w);

        player1.aceX = player1.aceY = 0.0;
        player2.aceX = player2.aceY = 0.0;

        /* Verifica colisão das naves. */
        if (hasCollidedShip (player1, player2)) 
            collideP1 = collideP2 = TRUE;
        else if (hasCollidedPlanet (player1, world)) 
            collideP1 = TRUE;
        else if (hasCollidedPlanet (player2, world)) 
            collideP2 = TRUE;

        /* Mostrando as coisas na tela por t segundos */
        usleep (t * 1000000);
    }
    /* Escolhe a cena de fim de jogo. */
    if (collideP1 && collideP2)
        showTie (w);
    else if (collideP1)
        showPlayer2Wins (w);
    else if (collideP2)
        showPlayer1Wins (w);

    /* Para sair o usuário deve digitar ESC. */
    quitDetection (w);

    /* Desalocando o espaço e fechando a janela. */
    FreePic (bg);
    freeShip (player1);
    freeShip (player2);
    freeBulletImg (bulletImg, bulletMsk, bulletAux);
    free (bullets);
    bullets = NULL;
    WDestroy(w);
    CloseGraph();

    #endif
    return EXIT_SUCCESS;
}