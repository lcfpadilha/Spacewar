/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298960 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       planet.h
 *  Dependências:  xwc.h
 * 
 *  Tem uma estrutura de planeta, e é responsável por exibi-lo na tela.
 *
 ******************************************************************************/ 

#ifndef XWC_H
    #define XWC_H
    #include "xwc.h"
#endif

#ifndef PLANET_H
#define PLANET_H

/* O planeta é declarado com uma estrutura que possui os campos radius (raio), 
// mass (massa), posX (coordenada x), posY (coordenada Y), img, aux e msk (para
// a geração de imagens). */
typedef struct {
    float radius, mass, posX, posY;
    PIC img, aux;
    MASK msk;
} planet;

/* Função que imprime o planeta e o background na tela w.*/
void showScene (planet world, WINDOW *w, PIC bg);

/* Inicializa o planeta apontado por world, com as imagens na tela w*/
void initPlanet (planet *world, WINDOW *w);

#endif 
