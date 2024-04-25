#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED



#endif // LSO_H_INCLUDED
#define MAXLSO 111

#include "Vendedor.h"

//TODO Modificar baja con "pertenece"

//TOASK preguntar por la suma de mas en localizar

//TESTED

typedef struct {
    vendedor list[MAXLSO];
    int contador;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, auxCont;
    int eExCant, eFrCant, aCant, bCant;
} lso;


//TESTED
void initlso(lso *lista){
    int i;
    for ( i = 1; i <MAXLSO ; ++i) {
        lista->list[i].documento=0;
    }
    lista->list[0].documento=100000000;
    lista->contador=0;
    lista->eExMax=0;
    lista->aMax=0;
    lista->bMax=0;
    lista->eFrMax=0;
    lista->bMed=0;
    lista->bCant=0;
    lista->eFrMed=0;
    lista->eExCant=0;
    lista->eFrCant=0;
    lista->aCant=0;
    lista->aMed=0;
    lista->eExMed=0;
}

int localizar(lso *lista, unsigned long x/*documento, in*/, int *pos/*posicion, out*/ ) {
    int i = 0;
    lista->auxCont = 0;
    while (lista->list[i].documento < x) {
        lista->auxCont++;
        i++;
    }
    *pos = i;
    lista->auxCont++;
    if (lista->list[i].documento == x) {
        //éxito
        return 1;
    } else {

    }
    //fracaso
    return 0;
}


int altalso(lso *lista, vendedor x/*in*/) {
    int pos;
    if (localizar(lista, x.documento, &pos) == 1) {
        return 0;
    } else {
        lista->auxCont = 0;
        int i;
        for ( i = lista->contador; i >= pos; i--) {
            lista->list[i + 1] = lista->list[i];
            lista->auxCont += 1.5;
        }
        lista->list[pos] = x;
        lista->contador++;
        lista->aMed +=lista->auxCont;
        lista->aCant++;
        if (lista->auxCont > lista->aMax) {
            lista->aMax = lista->auxCont;
        }
        return 1;
    }
}

//TESTED
int bajalso(lso *lista, vendedor x) {
    int pos, op, i;
    if (localizar(lista, x.documento, &pos) == 0 || strcmp(lista->list[pos].nombre, x.nombre) != 0 ||
        (strcmp(lista->list[pos].telefono, x.telefono) != 0) ||
        lista->list[pos].monto != x.monto || lista->list[pos].cantidad != x.cantidad ||
        strcmp(lista->list[pos].canal, x.canal) != 0) {
        return 0;
    }
    else {
        lista->auxCont = 0;
        i = pos;
        while (i < lista->contador) {
            lista->list[i] = lista->list[i + 1];
            i++;
            lista->auxCont += 1.5;
        }
        lista->contador--;
        lista->bMed +=lista->auxCont;
        lista->bCant++;
        if (lista->auxCont > lista->bMax) {
            lista->bMax = lista->auxCont;
        }
        return 1;
    }
}


vendedor evocacionlso(lso *lista, unsigned long doc, int *res) {
    int pos;
    vendedor auxvend;
    auxvend.documento = 100000000;
    if (localizar(lista, doc, &pos) == 1) {
        *res = 1;
        lista->eExMed +=lista->auxCont;
        lista->eExCant++;
        if (lista->auxCont > lista->eExMax) {
            lista->eExMax = lista->auxCont;
        }
        return lista->list[pos];
    } else {
        *res = 0;
        lista->eFrMed +=lista->auxCont;
        lista->eFrCant++;
        if (lista->auxCont > lista->eFrMax) {
            lista->eFrMax = lista->auxCont;
        }
        return auxvend;
    }
}
