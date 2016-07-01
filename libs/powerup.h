/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       powerup.h
 *  Dependências:  ship.h xwc.h
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

void initPowerUp ();

void createPowerUp (planet world, float dt);

void checkPowerUpCollision (planet world, ship player1, ship player2);

void showPowerUp (WINDOW *w);

#endif