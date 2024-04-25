#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED



#endif // RAL_H_INCLUDED
#include "RS.h"

#define MAX 143

//TOTEST nuevo localizar(le meti cambios rapidos, puede malir sal)

//TODO Cambiar el rebalse agregar contadores en alta y baja

//TOASK consultar por contador en las ultimas condiciones del localizar, consultar por los contadores en la baja y alta

//TESTED

typedef struct {
    vendedor vendedores[MAX];
    int cant;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, auxCont;
    int eExCant, eFrCant, aCant, bCant;
} ral;


//TESTED
void initRAL(ral *array) {
    int i;
    for (i = 0; i < MAX; i++) {
        array->vendedores[i].documento = 0;
    }
    array->cant = 0;
    array->eExMax=0;
    array->aMax=0;
    array->bMax=0;
    array->eFrMax=0;
    array->bMed=0;
    array->bCant=0;
    array->eFrMed=0;
    array->eExCant=0;
    array->eFrCant=0;
    array->aCant=0;
    array->aMed=0;
    array->eExMed=0;
}



//TESTED
int localizarRAL(ral *array, unsigned long dni, int *pos) {
    array->auxCont = 0;
    int i, k;
    k = 0;
    i = hashing(dni, MAX);
    int cont = 0;
    int n = 0;
    while (n < MAX && array->vendedores[(i) % MAX].documento != 0 &&
           array->vendedores[(i) % MAX].documento != dni) {
        array->auxCont++;
        if (cont == 0 && array->vendedores[(i) % MAX].documento == 1) {
            cont++;
            *pos = (i) % MAX;
        }
        n++;
        i++;
    }

    //Preguntar que hay si hay que sumar algo aca, creo que no
    if (n >= MAX) {
        if (cont == 0) {
            return 2;
        } else {
            return 0;
        }

    }else if (array->vendedores[(i) % MAX].documento == dni) {
        array->auxCont++;
        *pos = (i) % MAX;
        return 1;
    } else {
        array->auxCont++;
        if (cont == 0) {
            *pos = (i) % MAX;
        }
        return 0;
    }
}

//TESTED
int altaRAL(ral *array, vendedor x) {
    int pos;
    int auxloc;
    if ((auxloc = localizarRAL(array, x.documento, &pos)) == 1) {
        return 0;
    } else if (auxloc == 2) {
        return 2;
    } else {
        array->cant++;
        array->vendedores[pos] = x;
        array->aCant++;
        //preguntar que carajo hago aca con los costos (no hay corrimientos)
        return 1;
    }
}

//TESTED
int bajaRAL(ral *array, vendedor x) {
    int pos;
    int op;
    if (localizarRAL(array, x.documento, &pos) == 0|| strcmp(array->vendedores[pos].nombre, x.nombre) != 0 ||
        (strcmp(array->vendedores[pos].telefono, x.telefono) != 0) ||
        array->vendedores[pos].monto != x.monto || array->vendedores[pos].cantidad != x.cantidad ||
        strcmp(array->vendedores[pos].canal, x.canal) != 0) {
        return 0;
    } else {
            array->vendedores[pos].documento = 1;
            array->cant--;
            array->bCant++;
            //Preguntar lo mismo que en el alta
            return 1;
    }
}

vendedor evocacionRAL(ral *array, unsigned long dni, int *res) {
    int pos;
    vendedor auxvendedor;
    auxvendedor.documento = 0;
    *res = localizarRAL(array, dni, &pos);
    if (*res == 1) {
        array->eExMed +=array->auxCont;
        array->eExCant++;
        if (array->auxCont > array->eExMax) {
            array->eExMax = array->auxCont;
        }
        return array->vendedores[pos];
    } else {
        array->eFrMed +=array->auxCont;
        array->eFrCant++;
        if (array->auxCont > array->eFrMax) {
            array->eFrMax = array->auxCont;
        }
        return auxvendedor;
    }
}
