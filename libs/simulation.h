/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       simulation.h
 *  Dependências:  planet.h ship.h projectile.h getIndex.h xwc.h
 * 
 *  Simula corpos no espaço, que são 1 planeta, 2 naves e numberOfProj 
 *  projéteis.
 *
 ******************************************************************************/ 

#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef SIMULATION_H
#define SIMULATION_H

/* Função responsável por simular a física do jogo. */
void simulation (float spentTime, float t, float T, planet world, ship player1, 
                 ship player2, projectile bullets[], PIC bulletImg[], 
                 PIC bulletMsk[], int numberOfProj, float timeOfProj, WINDOW *w,
                 PIC bg);

#endif
