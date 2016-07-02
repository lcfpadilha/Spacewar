/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       scenes.h
 *  Dependências:  xwc.h
 *
 ******************************************************************************/
#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef SCENES_H
#define SCENES_H

/* As funções abaixo mostram telas específicas do jogo, como são descritas
// abaixo:                                                                  */

/* Tela inicial. */
void showMainMenu (WINDOW *w);

/* Tela de pause. */
void showPause (WINDOW *w);

/* Tela de "PLAYER 1 WINS". */
void showPlayer1Wins (WINDOW *w);

/* Tela de "PLAYER 2 WINS." */
void showPlayer2Wins (WINDOW *w);

/* Tela exibida quando há um empate. */
void showTie (WINDOW *w);

#endif