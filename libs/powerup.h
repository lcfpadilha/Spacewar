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

/* Cria um powerUp ou atualiza as posições do powerUp já existente. */
void createPowerUp (planet world, float dt);

/* Verifica se há colisão do powerUp ativo com algum dos objetos. */
void checkPowerUpCollision (planet world, ship *player1, ship *player2, WINDOW *w);

/* Mostra o powerUp que está ativo (se houver algum ativo). */
void showPowerUp (WINDOW *w);

#endif