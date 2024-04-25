#ifndef LSOB_H_INCLUDED
#define LSOB_H_INCLUDED



#endif // LSOB_H_INCLUDED
#include "LSO.h"


//TESTED

typedef struct {
    vendedor list[MAXLSO - 1];
    int contador;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, auxCont;
    int eExCant, eFrCant, aCant, bCant;
    int auxarr[MAXLSO];
} lsob;

//TESTED
void initlsob(lsob *lista) {
    int i;
    for ( i = 0; i < MAXLSO - 1; ++i) {
        lista->list[i].documento = 0;
    }
    lista->contador = 0;
    lista->eExMax = 0;
    lista->aMax = 0;
    lista->bMax = 0;
    lista->eFrMax = 0;
    lista->bMed = 0;
    lista->bCant = 0;
    lista->eFrMed = 0;
    lista->eExCant = 0;
    lista->eFrCant = 0;
    lista->aCant = 0;
    lista->aMed = 0;
    lista->eExMed = 0;
}


int localizarbb(lsob *lista, unsigned long long x, int *pos) {
    lista->auxCont = 0;
    if (lista->contador != 0) {
        int li, ls, j, i = 0;
        li = 0;
        ls = lista->contador - 1;
        for (j = 0; j < MAXLSO - 1; j++) {
            lista->auxarr[j] = 0;
        }
        while ((li) < ls) {
            i = (li + ls) / 2;
            if (lista->auxarr[i] == 0) {
                lista->auxCont++;
                lista->auxarr[i] = 1;
            }
            if (lista->list[i].documento >= x) {
                ls = i;
            } else {
                li = i + 1;
            }
        }
        if (lista->auxarr[li] == 0) {
            lista->auxCont++;
            lista->auxarr[li] = 1;
        }
        if (lista->list[li].documento < x && lista->contador != 0) {
            *pos = li + 1;
        } else {
            *pos = li;
        }

        if (lista->list[li].documento == x) {
            return 1;
        } else {
            return 0;
        }
    }
    else{
        return 0;
    }
}

//TESTED
int altalsob(lsob *lista, vendedor x/*in*/) {

    int pos;
    if (localizarbb(lista, x.documento, &pos) == 1) {
        return 0;
    } else {
        lista->auxCont = 0;
        int i;
        for ( i = lista->contador; i > pos; i--) {
            lista->list[i] = lista->list[i - 1];
            lista->auxCont += 1.5;
        }
        lista->list[pos] = x;
        lista->contador++;
        lista->aMed += lista->auxCont;
        lista->aCant++;
        if (lista->auxCont > lista->aMax) {
            lista->aMax = lista->auxCont;
        }
        return 1;
    }
}

//TESTED
int bajalsob(lsob *lista, vendedor x) {
    int pos, op, i;
    if (localizarbb(lista, x.documento, &pos) == 0 || strcmp(lista->list[pos].nombre, x.nombre) != 0 ||
        (strcmp(lista->list[pos].telefono, x.telefono) != 0) ||
        lista->list[pos].monto != x.monto || lista->list[pos].cantidad != x.cantidad ||
        strcmp(lista->list[pos].canal, x.canal) != 0) {
        return 0;
    } else {
        lista->auxCont = 0;
        i = pos;
        while (i < lista->contador - 1) {
            lista->list[i] = lista->list[i + 1];
            i++;
            lista->auxCont += 1.5;
        }
        lista->contador--;
        lista->bMed += lista->auxCont;
        lista->bCant++;
        if (lista->auxCont > lista->bMax) {
            lista->bMax = lista->auxCont;
        }
    }
}


//TESTED
vendedor evocacionlsob(lsob *lista, unsigned long doc, int *res) {
    int pos;
    vendedor auxvend;
    auxvend.documento = 100000000;
    if (localizarbb(lista, doc, &pos) == 1) {
        *res = 1;
        lista->eExMed += lista->auxCont;
        lista->eExCant++;
        if (lista->auxCont > lista->eExMax) {
            lista->eExMax = lista->auxCont;
        }
        return lista->list[pos];
    } else {
        *res = 0;
        lista->eFrMed += lista->auxCont;
        lista->eFrCant++;
        if (lista->auxCont > lista->eFrMax) {
            lista->eFrMax = lista->auxCont;
        }
        return auxvend;
    }
}
