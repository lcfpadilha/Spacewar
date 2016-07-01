/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       ship.h
 *  Dependências:  getIndex.h xwc.h
 *  
 *  Tem uma estrutura de nave, é responsável pelas funções de aceleração e 
 *  incremento de tempo delas, além de exibi-las na tela.
 *
 ******************************************************************************/ 

#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef SHIP_H
#define SHIP_H

/* Cada nave é declarada como uma estrutura que possui os campos name (nome, de 
// até 10 caracteres), mass (massa), posX (coordenada x), posY (coordenada Y), 
// velX (velocidade na direção x), velY (análogo para Y), aceX (aceleração na 
// direção x), aceY, (análogo para Y), direction (ângulo formado pela direção 
// da nave e o eixo x em radianos), timeForCharge (tempo para recarga dos tiros),
// life(vida da nave) img, aux e msk (para a geração de imagens). As úlimas 3 são 
// vetores com 16 posições, onde cada posição representa um ângulo 
// (ver em img/player*). */
typedef struct {
    char name[10];
    float mass, posX, posY, velX, velY, aceX, aceY;
    float direction, timeForCharge, life;
    int charge, shield, superShoot;
    PIC img[16];
    PIC aux[16];
    MASK msk[16];
} ship;

#include "projectile.h"
#include "planet.h"
 
/* Inicializa a nave p identificada por playerID com as imagens na tela w */
void initPlayer (ship *p, int playerID, WINDOW *w);

/* Recebe um ponteiro para ship player e um planet world e 
// soma a aceleração atual de player (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por world. */
void accelerateShipToWorld (ship *player, planet world);

/* Recebe um ponteiro para ship player e um ship other e 
// soma a aceleração atual de player (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por other. */
void accelerateShipToShip (ship *player, ship other);

/* Recebe um ponteiro para ship player e um projectile b e 
// soma a aceleração atual de player (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por b. */
void accelerateShipToProj (ship *player, projectile b);

/* Função que detecta de uma nave colidiu-se com a outra. */
int hasCollidedShip (ship player, ship other);

/* Detecta se uma nave colidiu-se com o planeta. */
int hasCollidedPlanet (ship player, planet world);

/* Detecta se uma nave colidiu-se com um projétil. */
int hasCollidedProj (ship player, projectile bullet);

/* Esta função recebe uma ship player e um real dt. Devolve uma ship que 
// representa player logo apos a variação de tempo dt, de tal forma que
// suas coordenadas x e y variem entre minX e minY a maxX e maxY. */
ship increaseTimeShip (ship player, int maxX, int minX, 
                                    int maxY, int minY, float dt);

/* Essa função imprime a nave player na tela w. */
void showShip (ship player, WINDOW *w);

/* Exibe na janela o quanto de vida cada nave tem. */
void showShipLife (ship player1, ship player2, WINDOW *w);

/* Libera as imagens da nave player. */
void freeShip (ship player);

#endif
