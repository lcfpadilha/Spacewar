/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:   getIndex.c
 *
 *  Arquivo .c de getIndex.h
 *
 ******************************************************************************/ 

#include <math.h>
#include <stdio.h>
#include "getIndex.h"


int getIndexByOrientation (double orientation) {
    double angle = orientation * 180.0 / M_PI;
    
    return (int) angle / 22.5;
}

int getBulletIndexByOrientation (double velX, double velY) {
    double angle = atan (velY / velX) * 180.0 / M_PI;

    if (velX > 0 && velY >= 0)
        return (int) angle / 22.5;
    else if (velX < 0 && velY >= 0) 
        return (int) (180 + angle) / 22.5;
    else if (velX < 0 && velY < 0) 
        return (int) (180 + angle) / 22.5;
    else if (velX > 0 && velY < 0) 
        return (int) (360 + angle) / 22.5;
    else if (velX == 0 && velY > 0)
        return 4;
    else
        return 12;
}
