/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       projectile.h
 *  Dependências:  planet.h ship.h
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

/* Cada bala é declarada como uma estrutura que possui os campos mass (massa), 
// posX (coordenada x), posY (coordenada Y), velX (velocidade na direção x), 
// velY (análogo para Y), aceX (aceleração na direção x), aceY, (análogo para 
// Y), lifeTime (tempo de vida), doubleDamage (booleano que verifica se o 
// projetil possui dano duplo) e playerID[10], que define quem a atirou. */
typedef struct {
    float mass, posX, posY, velX, velY, aceX, aceY;
    float lifeTime;
    int doubleDamage;
    char playerID[10];
} projectile;

#include "planet.h"
#include "ship.h"

/* Inicializa um vetor de projectiles.*/
projectile *initProj ();

/* Recebe um vetor de projectiles com 0..n - 1 elementos inicializados, e cria mais
// mais um projectile disparado por player na posição n do vetor .               */
void shoot (projectile *bullets, int n, ship player);

/* Libera o espaço ocupado por um projétil de índice index. */
void deleteBullet (projectile *bullets, int n, int index);

/* Recebe um ponteiro para projectile bullet e um planet world e 
// soma a aceleração atual de bullet (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por world. */
void accelerateProjToWorld (projectile *bullet, planet world);

/* Recebe um ponteiro para projectile bullet e um ship planet e 
// soma a aceleração atual de bullet (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por player. */
void accelerateProjToShip (projectile *bullet, ship player);

/* Recebe um ponteiro para projectile bullet e um projectile other e 
// soma a aceleração atual de bullet (tanto no eixo x quanto 
// no eixo y) com a aceleração gravitacional gerada por other. */
void accelerateProjToProj (projectile *bullet, projectile other);

/* Esta função recebe um projectile p e um float dt. Devolve um projectile que 
// representa p logo apos a variação de tempo dt.
*/
projectile increaseTimeProjectile (projectile p, int maxX, int minX, 
                                                 int maxY, int minY, float dt);

/* Detecta se um projétil colidiu com o planeta. */
int projCollided (projectile bullet, planet world);

/* Inicializa as 16 imagens dos projéteis e suas respectivas mascaras em
// bulletImg e bulletMsk com auxilio da bulletAux na janela w.           */
void initProjImage (PIC *bulletImg, PIC *bulletMsk, PIC *bulletAux, WINDOW *w);

/* Função que mostra a bala bullet na janela w usando as imagens do vetor 
// bulletImg e bulletMsk, supondo que eles possuem 16 imagens. */
void showBullet (projectile bullet, WINDOW *w, PIC bulletImg[], MASK bulletMsk[]);

/* Libera as imagens de bullets. */
void freeBulletImg (PIC bulletImg[], MASK bulletMsk[], PIC bulletAux[]);

#endif
