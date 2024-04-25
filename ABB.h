#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED



#endif // ABB_H_INCLUDED
#include "LSOB.h"

//TOTEST

//TESTED

typedef struct node {
    vendedor vipd;
    struct node *hi;
    struct node *hd;
} nodoabb;

typedef struct {
    nodoabb *raiz;
    nodoabb *pos;
    nodoabb *padre;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, auxCont;
    int eExCant, eFrCant, aCant, bCant;
} arbol;


//TESTED
void limpiarabb(nodoabb *raiz){
    if(raiz==NULL){

    }
    else{
        limpiarabb(raiz->hi);
        limpiarabb(raiz->hd);
        free(raiz);
    }
}


//TESTED
void initabb(arbol *abb) {
    abb->padre = NULL;
    abb->raiz = NULL;
    abb->pos = NULL;
    abb->eExMax = 0;
    abb->aMax = 0;
    abb->bMax = 0;
    abb->eFrMax = 0;
    abb->bMed = 0;
    abb->bCant = 0;
    abb->eFrMed = 0;
    abb->eExCant = 0;
    abb->eFrCant = 0;
    abb->aCant = 0;
    abb->aMed = 0;
    abb->eExMed = 0;
}


void resetabb(arbol *abb) {
    abb->padre = NULL;
    abb->pos = NULL;
}

int localizarabb(unsigned long doc, arbol *abb) {
    abb->auxCont=0;
    nodoabb *auxpos, *ant;
    auxpos = abb->raiz;
    ant = abb->raiz;

    while (auxpos != NULL && doc != auxpos->vipd.documento) {
        abb->auxCont++;

        //preguntar si la condicion del while cuenta como celda consultada SI CUENTA
        ant = auxpos;
        if (doc > auxpos->vipd.documento) {
            auxpos = auxpos->hd;
        } else {
            auxpos = auxpos->hi;
        }
    }
    abb->padre = ant;
    abb->pos = auxpos;
    if (auxpos == NULL) {
        return 0;
    } else {
        abb->auxCont++;
        return 1;
    }
}

int altaabb(arbol *abb, vendedor x) {
    abb->auxCont = 0;
    nodoabb *auxnptr;
    if (abb->raiz == NULL) {
        //Preguntar si el malloc cuenta como actualizacion de punteros RESPUESTA no cuenta
        auxnptr = malloc(sizeof(nodoabb));
        if (auxnptr == NULL) {
            return 2;
        }
        auxnptr->hi = NULL;
        auxnptr->hd = NULL;
        //preguntar si la copia del dato cuenta en el alta RESPUESTA No cuenta
        auxnptr->vipd = x;
        abb->raiz = auxnptr;
        abb->auxCont++;
        if (abb->auxCont > abb->aMax) {
            abb->aMax = abb->auxCont;
        }
        abb->aMed += abb->auxCont;
        abb->aCant++;

        return 1;
    } else if (localizarabb(x.documento, abb) == 0) {
        abb->auxCont = 0;
        auxnptr = malloc(sizeof(nodoabb));
        if (auxnptr == NULL) {
            return 2;
        }
        auxnptr->hi = NULL;
        auxnptr->hd = NULL;
        auxnptr->vipd = x;
        if (x.documento > abb->padre->vipd.documento) {
            abb->padre->hd = auxnptr;
        } else {
            abb->padre->hi = auxnptr;
        }
        abb->auxCont++;
        if (abb->auxCont > abb->aMax) {
            abb->aMax = abb->auxCont;
        }
        abb->aMed = abb->aMed + abb->auxCont;
        abb->aCant++;
        return 1;
    } else {
        return 0;
    }
}


//TESTED

int bajaabb(arbol *abb, vendedor x) {
    int op, auxres;
    auxres = localizarabb(x.documento, abb);
    nodoabb *aux = abb->pos;
    if  (auxres == 0 || strcmp(aux->vipd.nombre, x.nombre) != 0 ||
         (strcmp(aux->vipd.telefono, x.telefono) != 0) ||
         aux->vipd.monto != x.monto || aux->vipd.cantidad != x.cantidad ||
         strcmp(aux->vipd.canal, x.canal) != 0){
        return 0;
    }

        /**/
    //confirmar
    else {
        abb->auxCont = 0;

        if (abb->pos->hd != NULL) {
            if (abb->pos->hi != NULL) {
                //Caso con dos hijos
                //Preguntar si estas actualizaciones cuentan como actualizaciones


                nodoabb *auxpos = abb->pos->hi;
                nodoabb *auxposp = abb->pos;

                while (auxpos->hd != NULL) {
                    auxposp = auxpos;
                    auxpos = auxpos->hd;
                }
                abb->pos->vipd = auxpos->vipd;
                abb->auxCont +=(float) 1.5;
                if (abb->pos == auxposp) {
                    //Caso reemplazo es HI de pos
                    auxposp->hi = auxpos->hi;
                } else {
                    auxposp->hd = auxpos->hi;
                }


                abb->auxCont++;
                abb->bMed +=abb->auxCont;
                abb->bCant++;
                if (abb->auxCont > abb->bMax) {
                    abb->bMax = abb->auxCont;
                }
                free(auxpos);
                return 1;
            } else {
                //Caso con un hd != NULL, hi NULL

                if (abb->raiz == abb->pos) {
                    abb->raiz = abb->pos->hd;

                } else if (abb->pos == abb->padre->hi) {
                    abb->padre->hi = abb->pos->hd;
                    rs->aux = rs->arrlv[j].acc;
                    rs->auxCont++;
                } else {
                    abb->padre->hd = abb->pos->hd;

                }
                abb->auxCont++;
                abb->bMed +=abb->auxCont;
                abb->bCant++;
                if (abb->auxCont > abb->bMax) {
                    abb->bMax = abb->auxCont;
                }
                free(abb->pos);
                return 1;
            }
        } else {
            if (abb->raiz == abb->pos) {
                abb->raiz = abb->pos->hi;
            }
             else {
                if (abb->pos == abb->padre->hi) {
                    abb->padre->hi = abb->pos->hi;
                } else {
                    abb->padre->hd = abb->pos->hi;
                }
             }
            abb->auxCont++;
            abb->bMed +=abb->auxCont;
            abb->bCant++;
            if (abb->auxCont > abb->bMax) {
                abb->bMax = abb->auxCont;
            }
            free(abb->pos);
            return 1;
        }
    }
}


vendedor evocacionabb(arbol *abb, unsigned long x, int *auxres) {
    vendedor auxvendedor;
    auxvendedor.documento = 100000000;
    *auxres = localizarabb(x, abb);

    if (*auxres == 1) {
        abb->eExMed +=abb->auxCont;
        abb->eExCant++;
        if (abb->auxCont > abb->eExMax) {
            abb->eExMax = abb->auxCont;
        }
        return abb->pos->vipd;

    } else {
        abb->eFrMed +=abb->auxCont;
        abb->eFrCant++;
        if (abb->auxCont > abb->eFrMax) {
            abb->eFrMax = abb->auxCont;
        }
        return auxvendedor;
    }
}

void preordenabb(nodoabb *nodo, int *i) {
    if (nodo == NULL) {
    } else {

        printf("nodo %d\n", *i);
        muestraPantalla(nodo->vipd);
        (*i)++;
        if (nodo->hi != NULL) {
            printf("\n DNI hijo izquierdo: %lu\n", nodo->hi->vipd.documento);
        } else {
            printf("\n El nodo no tiene hijo izquierdo. \n");
        }
        if (nodo->hd != NULL) {
            printf("\n DNI hijo derecho: %lu\n", nodo->hd->vipd.documento);
        } else {
            printf("\n El nodo no tiene hijo derecho.\n");
        }
        getchar();
        preordenabb(nodo->hi, i);
        preordenabb(nodo->hd, i);
    }

}
