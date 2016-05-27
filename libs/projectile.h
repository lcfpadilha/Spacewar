/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
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
    float lifeTime;
} projectile;

#include "planet.h"
#include "ship.h"

/* Recebe um ponteiro para n, um ponteiro para t e retorna um vetor de
   projectile com n elementos com os valores recebidos da entrada padrão.*/
projectile *initProj (int *n);

/* Recebe um vetor de projectiles com 0..n - 1 elementos inicializados, e cria mais
   mais um projectile na posição n do vetor e com valor de posX = x, posY = y
   velX = vx + 100 e velY = vy + 100.                                         */
void shoot (projectile *bullets, int n, float x, float y, float dirX, float dirY);

void deleteBullet (projectile *bullets, int n, int index);

/* Recebe um ponteiro para projectile bullet e um planet world e 
   soma a aceleração atual de bullet (tanto no eixo x quanto 
   no eixo y) com a aceleração gravitacional gerada por world. */
void accelerateProjToWorld (projectile *bullet, planet world);

/* Recebe um ponteiro para projectile bullet e um ship planet e 
   soma a aceleração atual de bullet (tanto no eixo x quanto 
   no eixo y) com a aceleração gravitacional gerada por player. */
void accelerateProjToShip (projectile *bullet, ship player);

/* Recebe um ponteiro para projectile bullet e um projectile other e 
   soma a aceleração atual de bullet (tanto no eixo x quanto 
   no eixo y) com a aceleração gravitacional gerada por other. */
void accelerateProjToProj (projectile *bullet, projectile other);

/* Esta função recebe um projectile p e um float dt. Devolve um projectile que 
   representa p logo apos a variação de tempo dt.
*/
projectile increaseTimeProjectile (projectile p, int maxX, int minX, 
                                                 int maxY, int minY, float dt);

/* Função que mostra a bala bullet na janela w usando as imagens do vetor 
// bulletImg e bulletMsk, supondo que eles possuem 16 imagens. */
void showBullet (projectile bullet, WINDOW *w, PIC bulletImg[], MASK bulletMsk[]);

/* Inicializa as 16 imagens dos projéteis e suas respectivas mascaras em
   bulletImg e bulletMsk com auxilio da bulletAux na janela w.           */
void initProjImage (PIC *bulletImg, PIC *bulletMsk, PIC *bulletAux, WINDOW *w);

#endif
