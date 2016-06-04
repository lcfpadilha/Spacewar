/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       controller.h
 *  Dependências:  ship.h xwc.h
 *
 ******************************************************************************/
#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <math.h>
#include "ship.h"

#define FALSE 0
#define TRUE  1

void initDetection (WINDOW *w);
void movePlayer (ship *player1, ship *player2, projectile *bullets, int *n, WINDOW *w, float t);
void quitDetection (WINDOW *w);
void enterCheck (WINDOW *w, int total);

#endif