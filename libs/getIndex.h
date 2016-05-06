/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:  getIndex.h
 *
 *  Possui a função getIndexbyOrientation.
 *
 ******************************************************************************/ 

#ifndef GETINDEX_H
#define GETINDEX_H

/* Essa função devolve o ângulo de um retângulo cujo cateto oposto é velY e 
// cateto adjacente é velY. Isso serve para escolha da imagem adequada à 
// velocidade do corpo. */
int getIndexByOrientation (double velX, double velY);

#endif
