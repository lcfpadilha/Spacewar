/******************************************************************************
 *  Nomes: Gustavo Henrique Faustino Silva        Números USP: 9298260 
 *         Leonardo de Carvalho F. P. Aguilar                  9298295
 *         Luís Felipe de Melo Costa Silva                     9297961
 *
 *
 *  Arquivo:       scenes.c
 *  Dependências:  xwc.h
 *
 ******************************************************************************/
#include <stdio.h>
#include "xwc.h"

void showMainMenu (WINDOW *w) {
    PIC menu = ReadPic (w, "img/etc/spacewar.xpm", NULL);
    PutPic (w, menu, 0, 0, 720, 480, 0, 0);
    FreePic (menu);
}

void showPause (WINDOW *w) {
    PIC pause = ReadPic (w, "img/etc/pause.xpm", NULL);
    PIC msk = NewMask (w, 720, 480);
    PIC aux = ReadPic (w, "img/etc/pause_MASK.xpm", msk);
    SetMask (w, msk);
    PutPic (w, pause, 0, 0, 720, 480, 0, 0);
    UnSetMask (w);
    FreePic (pause);
    FreePic (msk);
    FreePic (aux);
}

void showPlayer1Wins (WINDOW *w) {
    PIC win = ReadPic (w, "img/etc/p1.xpm", NULL);
    PIC msk = NewMask (w, 720, 480);
    PIC aux = ReadPic (w, "img/etc/p1_MASK.xpm", msk);
    SetMask (w, msk);
    PutPic (w, win, 0, 0, 720, 480, 0, 0);
    UnSetMask (w);
    FreePic (win);
    FreePic (msk);
    FreePic (aux);
}

void showPlayer2Wins (WINDOW *w) {
    PIC win = ReadPic (w, "img/etc/p2.xpm", NULL);
    PIC msk = NewMask (w, 720, 480);
    PIC aux = ReadPic (w, "img/etc/p2_MASK.xpm", msk);
    SetMask (w, msk);
    PutPic (w, win, 0, 0, 720, 480, 0, 0);
    UnSetMask (w);
    FreePic (win);
    FreePic (msk);
    FreePic (aux);
}

void showTie (WINDOW *w) {
    PIC tie = ReadPic (w, "img/etc/tie.xpm", NULL);
    PIC msk = NewMask (w, 720, 480);
    PIC aux = ReadPic (w, "img/etc/tie_MASK.xpm", msk);
    SetMask (w, msk);
    PutPic (w, tie, 0, 0, 720, 480, 0, 0);
    UnSetMask (w);
    FreePic (tie);
    FreePic (msk);
    FreePic (aux);
}