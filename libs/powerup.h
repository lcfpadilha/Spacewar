/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       powerup.h
 *  Dependências:  ship.h xwc.h planet.h
 *  
 ******************************************************************************/
#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef POWERUP_H
#define POWERUP_H

#include "ship.h"
#include "planet.h"

/* Inicia as variaveis relacionadas aos powerUps. */
void initPowerUp ();

/* Cria um powerUp aleatório próximo ao planet world ou atualiza as posições do
// powerUp já existentes dado que o tempo passado foi de dt. */
void createPowerUp (planet world, float dt);

/* Verifica se há colisão do powerUp atual no jogo com algum dos objetos, se um ship
// colidiu, atualiza os dados dela dependendo do tipo do powerUp. */
void checkPowerUpCollision (planet world, ship *player1, ship *player2, WINDOW *w);

/* Mostra o powerUp que está no jogo (se houver algum ativo), na janela w. */
void showPowerUp (WINDOW *w);

#endif