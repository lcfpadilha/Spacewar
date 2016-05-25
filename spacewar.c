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

#define W 720  /* Largura da janela. */
#define H 480  /* Altura da janela. */

#define UP1    111
#define UP2    25
#define DOWN1  116
#define DOWN2  39
#define LEFT1  113
#define LEFT2  38
#define RIGHT1 114
#define RIGHT2 40

#define FALSE 0
#define TRUE 1

int main (int argc, char** argv) {
    /* Caso a biblioteca Xpm não esteja habilitada, o programa não funciona. */
    #ifdef NOXPM 
        printf ("Este programa só funciona com a biblioteca Xpm!")
    #else
    
    /* Declaração de variáveis */
    int numberOfProj, i, j, ret;
    float timeOfProj, t, T, spentTime;
    int up1Press = FALSE, down1Press = FALSE, left1Press = FALSE, right1Press = FALSE;
    int up2Press = FALSE, down2Press = FALSE, left2Press = FALSE, right2Press = FALSE;

    /* Declaração dos corpos que serão postos no espaço. */
    planet world;
    ship player1, player2;
    projectile *bullets;

    /* Declaração de variáveis que vão gerar as imagens. */
    WINDOW *w;
    PIC bg, bulletImg[16], bulletAux[16];
    MASK bulletMsk[16];

    /* Declaração de váriaveis para uso de controle */
    KeyCode kb;

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

    /* Inicialização do teclado */
    InitKBD(w);

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
    bullets = initProj (&numberOfProj, &timeOfProj);

    /* Inicialização das imagens dos projéteis. */
    initProjImage (bulletImg, bulletMsk, bulletAux, w);

    /* Tempo gasto até agora. */
    spentTime = 0.0;

    /* Simulando o espaço. */
    while (spentTime < T) {
        /* Verifica se alguma tecla foi pressionada */
        if (WCheckKBD(w)) {
            kb = WGetKey(w);
            if (kb == UP1) 
                up1Press =   !up1Press;
            
            else if (kb == DOWN1) 
                down1Press = !down1Press;
                
            else if (kb == LEFT1) 
                left1Press = !left1Press;
            
            else if (kb == RIGHT1) 
                right1Press = !right1Press;
            
            else if (kb == UP2) 
                up2Press = !up2Press;
            
            else if (kb == DOWN2) 
                down2Press = !down2Press;
            
            else if (kb == LEFT2) 
                left2Press = !left2Press;
            
            else if (kb == RIGHT2) 
                right2Press = !right2Press;
        }
        if (up1Press) {
            player1.aceY += 150 * sin (player1.direction);
            player1.aceX += 150 * cos (player1.direction);
        }
        
        if (down1Press) {
            player1.aceY -= 150 * sin (player1.direction);
            player1.aceX -= 150 * cos (player1.direction);
        }
        
        if (left1Press) 
            player1.direction += M_PI / 20;
        
        if (right1Press) 
            player1.direction -= M_PI / 20;
    
        if (up2Press) {
            player2.aceY += 150 * sin (player2.direction);
            player2.aceX += 150 * cos (player2.direction);
        }
    
        if (down2Press) {
            player2.aceY -= 150 * sin (player2.direction);
            player2.aceX -= 150 * cos (player2.direction);
        }

        if (left2Press)
            player2.direction += M_PI / 20;
        
        if (right2Press)
            player2.direction -= M_PI / 20;
        /* Calculando a aceleração da nave pĺayer1. */
        accelerateShipToWorld (&player1, world);
        accelerateShipToShip  (&player1, player2);

        /*Calculando a aceleração da nave player2. */
        accelerateShipToWorld (&player2, world);
        accelerateShipToShip  (&player2, player1);

        /* Calculando a aceleração dos projeteis, se eles (ainda) existirem. */
        if (bullets != NULL && spentTime < timeOfProj)
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
        else {
        	free (bullets);
        	bullets = NULL;
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
            bullets[i] = increaseTimeProjectile (bullets[i], W/2, -W/2, H/2, -H/2, t);
            
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
    if (spentTime >= timeOfProj) free (bullets);
    WDestroy(w);
    CloseGraph();

    #endif
    return EXIT_SUCCESS;
}
