/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       controller.h
 *  Dependências:  ship.h xwc.h math.h
 *
 ******************************************************************************/
#include <stdio.h>
#include <math.h>
#include "controller.h"
#include "ship.h"

#define ACC1   25
#define RIGHT1 40
#define LEFT1  38
#define FIRE1  39

#define ACC2   111
#define FIRE2  116
#define LEFT2  113
#define RIGHT2 114

#define ENTER 36
#define QUIT   9

/* Variáveis privadas */
static int acc1Press, fire1Press, left1Press, right1Press;
static int acc2Press, fire2Press, left2Press, right2Press; 
static float time, timeP1, timeP2;

void initDetection (WINDOW *w) {
    InitKBD(w);
    acc1Press = fire1Press = left1Press = right1Press = FALSE;
    acc2Press = fire2Press = left2Press = right2Press = FALSE;
    time = 0.0;
    timeP1 = time - 0.2;
    timeP2 = time - 0.2;
}

void movePlayer (ship *player1, ship *player2, projectile *bullets, int *n, WINDOW *w, float t) {
    KeyCode kb;
    time += t;
    if (WCheckKBD(w)) {
        kb = WGetKey(w);
        if (kb == ACC1) 
            acc1Press =   !acc1Press;
        
        else if (kb == FIRE1) 
            fire1Press = !fire1Press;
            
        else if (kb == LEFT1) 
            left1Press = !left1Press;
        
        else if (kb == RIGHT1) 
            right1Press = !right1Press;
        
        else if (kb == ACC2) 
            acc2Press = !acc2Press;
        
        else if (kb == FIRE2) 
            fire2Press = !fire2Press;
        
        else if (kb == LEFT2) 
            left2Press = !left2Press;
        
        else if (kb == RIGHT2) 
            right2Press = !right2Press;
        else if (kb == ENTER)
            enterCheck (w, 3);
    }

    if (acc1Press) {
        player1->aceY += 180 * sin (player1->direction);
        player1->aceX += 180 * cos (player1->direction);
    }
    
    if (fire1Press && time - timeP1 > 0.2 && player1->charge > 0) {
        shoot (bullets, *n, *player1);
        *n = *n + 1;
        player1->charge--;
        timeP1 = time;
    }
    
    if (left1Press) 
        player1->direction += M_PI / 20;
    
    if (right1Press) 
        player1->direction -= M_PI / 20;

    if (acc2Press) {
        player2->aceY += 180 * sin (player2->direction);
        player2->aceX += 180 * cos (player2->direction);
    }
    if (fire2Press && time - timeP2 > 0.2 && player2->charge > 0) {
        shoot (bullets, *n, *player2);
        *n = *n + 1;
        player2->charge--;
        timeP2 = time;
    }

    if (left2Press)
        player2->direction += M_PI / 20;
    
    if (right2Press)
        player2->direction -= M_PI / 20;
}

void quitDetection (WINDOW *w) {
    while (1)
        if (WCheckKBD(w) && WGetKey(w) == QUIT)
            break;
}

void enterCheck (WINDOW *w, int total) {
    int cont = 0;
    while (1) { 
        if (WCheckKBD(w) && WGetKey(w) == ENTER) {
            cont++;
            if (cont == total) break;
        }
    }
}