/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       error.c
 *  Dependências:  stdio.h e stdlib.h
 *  
 *  Arquivo .c de error contendo a função hasError.
 *
 ******************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>

void hasError (int i) {
    if (i) {
        printf ("Erro de leitura, saindo da simulação!\n");
        exit (0);
    }
}
