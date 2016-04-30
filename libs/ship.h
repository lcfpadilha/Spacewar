/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
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
// direção x), aceY, (análogo para Y), img, aux e msk (para a geração de 
// imagens). As úlimas 3 são vetores com 16 posições, onde cada posição 
// representa um ângulo (ver em img/player*). */
typedef struct {
    char name[10];
    float mass, posX, posY, velX, velY, aceX, aceY;
    PIC img[16];
    PIC aux[16];
    MASK msk[16];
} ship;

/* Esta função recebe uma ship s, os reais mass, posX, posY e um char de comando
   c. Devolve a aceleração gravitacional de s, no eixo dado por c (ou x ou y) em
   relação a um corpo localizado na posicao x = posX e na posicao y = posY com 
   uma massa mass. 
*/
float accelerateShip (ship s, float mass, float posX, float posY, char c);

/* Esta função recebe uma ship player e um real dt. Devolve uma ship que 
   representa player logo apos a variação de tempo dt.
*/
ship increaseTimeShip (ship player, int maxX, int minX, 
                                    int maxY, int minY, float dt);

/* Essa função imprime a nave player na tela w. */
void showShip (ship player, WINDOW *w);

#endif
