#include "module.h"
#include <stdio.h>

typedef struct tiedot
{
    char aSukunimi[LEN];
    int iYhteensa;
    struct tiedot *pSeuraava;
    struct tiedot *pEdellinen;
} TIEDOT;

typedef struct lista
{
    TIEDOT *pAlku;
    TIEDOT *pLoppu;
} LISTA;

void lue()
{
}

void kirjoita()
{
}

void tulosta()
{
}