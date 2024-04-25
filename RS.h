#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED



#endif // RS_H_INCLUDED
#define MLV 60

#include "LV.h"

//TOTEST cuidado con la linea comentada en la baja

//TESTED

typedef struct {
    lista arrlv[MLV];
    nodolv *cur;
    nodolv *aux;
    int contador;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, auxCont;
    int eExCant, eFrCant, aCant, bCant;
} rs;

int hashing(unsigned long dni, int m) {
    char x[8];
    int longitud, i;
    int contador = 0;
    sprintf(x, "%lu", dni);
    longitud = strlen(x);

    for (i = 0; i < longitud; i++)
        contador += ((int) x[i]) * (i + 1);
    return (contador % m);
}

//TESTED
void limpiars(rs *rs){
    int i;
    for ( i = 0; i < MLV; ++i) {
        if(rs->arrlv[i].acc==NULL){

        }
        else{
            rs->cur=rs->arrlv[i].acc->next;
            rs->aux=rs->arrlv[i].acc;
            while (rs->cur!=NULL){
                rs->aux->next=rs->cur->next;
                free(rs->cur);
                rs->cur=rs->aux->next;
            }
            free(rs->aux);
            rs->arrlv[i].acc=NULL;
        }
    }
}

void init(rs *rs) {
    int i;
    for ( i = 0; i < MLV; i++) {
        initlv(&rs->arrlv[i]);
    }
    rs->contador = 0;
    rs->eExMax = 0;
    rs->aMax = 0;
    rs->bMax = 0;
    rs->eFrMax = 0;
    rs->bMed = 0;
    rs->bCant = 0;
    rs->eFrMed = 0;
    rs->eExCant = 0;
    rs->eFrCant = 0;
    rs->aCant = 0;
    rs->aMed = 0;
    rs->eExMed = 0;
}

int localizarrs(rs *rs, unsigned long doc, int *j) {
    rs->auxCont = 0;
    *j = hashing(doc, MLV);
    rs->auxCont++;
    if (rs->arrlv[*j].acc == NULL) {

        return 0;
    }
    rs->cur = rs->arrlv[*j].acc;
    rs->aux = rs->arrlv[*j].acc;
    while (rs->cur->next != NULL && rs->cur->vipd.documento != doc) {
        rs->auxCont++;
        rs->aux = rs->cur;
        rs->cur = rs->cur->next;

    }
    rs->auxCont++;
    if (rs->cur->vipd.documento == doc) {
        return 1;
    } else {
        return 0;
    }
}

int altars(rs *rs, vendedor x) {

    int j;
    if (localizarrs(rs, x.documento, &j) == 0) {
        nodolv *l = (nodolv *) malloc(sizeof(nodolv));
        if (l == NULL) {
            return 2;
        }
        rs->auxCont = 0;
        rs->contador++;
        l->vipd = x;
        l->next = rs->arrlv[j].acc;
        rs->auxCont++;
        rs->arrlv[j].acc = l;
        rs->auxCont++;
        rs->aMed += rs->auxCont;
        rs->aCant++;
        if (rs->auxCont > rs->aMax) {
            rs->aMax = rs->auxCont;
        }
        return 1;

    } else return 0;
}

//TESTED
int bajars(rs *rs, vendedor x) {

    int op;
    int j;
    if (localizarrs(rs, x.documento, &j) == 0 || strcmp(rs->cur->vipd.nombre, x.nombre) != 0 ||
        (strcmp(rs->cur->vipd.telefono, x.telefono) != 0) ||
        rs->cur->vipd.monto != x.monto || rs->cur->vipd.cantidad != x.cantidad ||
        strcmp(rs->cur->vipd.canal, x.canal) != 0) {
        return 0;
    } else {
        rs->auxCont = 0;
        rs->contador--;
        if (rs->cur == rs->arrlv[j].acc) {
            rs->arrlv[j].acc = rs->arrlv[j].acc->next;
            rs->auxCont++;
            free(rs->cur);

        } else {
            rs->aux->next = rs->cur->next;
            rs->auxCont++;
            free(rs->cur);
        }
        rs->bMed+=rs->auxCont;
        rs->bCant++;
        if (rs->auxCont > rs->bMax) {
            rs->bMax = rs->auxCont;
        }
        return 1;
    }
}

vendedor evocacionrs(rs *rs, unsigned long doc, int *res) {
    vendedor auxvendedor;
    auxvendedor.documento = 100000000;
    int j;
    *res = localizarrs(rs, doc, &j);
    if (*res == 1) {
        rs->eExMed += rs->auxCont;
        rs->eExCant++;
        if (rs->auxCont > rs->eExMax) {
            rs->eExMax = rs->auxCont;
        }
        return rs->cur->vipd;
    } else {
        rs->eFrMed += rs->auxCont;
        rs->eFrCant++;
        if (rs->auxCont > rs->eFrMax) {
            rs->eFrMax = rs->auxCont;
        }
        return auxvendedor;
    }
}

