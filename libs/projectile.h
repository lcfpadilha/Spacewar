/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       projectile.h
 *  Dependências:  getIndex.h xwc.h
 * 
 *  Tem uma estrutura de bala, é responsável pelas funções de aceleração e 
 *  incremento de tempo delas, além de exibi-las na tela.
 *
 ******************************************************************************/ 

#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Cada bala é declarada como uma estrutura que possui os campos name (nome, de 
// até 10 caracteres), mass (massa), posX (coordenada x), posY (coordenada Y), 
// velX (velocidade na direção x), velY (análogo para Y), aceX (aceleração na 
// direção x), aceY, (análogo para Y). */
typedef struct {
    float mass, posX, posY, velX, velY, aceX, aceY;
} projectile;

/* Esta função recebe um projetile p, os reais mass, posX, posY e um char de 
   comando c. Devolve a aceleração gravitacional de p, no eixo dado por c
   (ou x ou y) em relação a um corpo localizado na posicao x = posX e na posicao
   y = posY com uma massa mass.
*/
float accelerateProjectile (projectile p, float mass, float posX, float posY, 
                            char c);

/* Esta função recebe um projectile p e um float dt. Devolve um projectile que 
   representa p logo apos a variação de tempo dt.
*/
projectile increaseTimeProjectile (projectile p, int maxX, int minX, 
                                                 int maxY, int minY, float dt);

/* Função que mostra a bala bullet na janela w usando as imagens do vetor 
// bulletImg e bulletMsk, supondo que eles possuem 16 imagens. */
void showBullet (projectile bullet, WINDOW *w, PIC bulletImg[], MASK bulletMsk[]);

#endif
