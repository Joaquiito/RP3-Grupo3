#include <stdio.h>
#include <ctype.h>
#include "RAL.h"

//TOTEST
//done ponele que todo



void inicio() {
    int op = 0;
    int auxop = 0;
    int auxres;
    int auxi;
    int i;
    int auxlectura;
    vendedor auxvendedor;
    char auxchar;
    unsigned long auxdocumento;
    FILE *f1;
    arbol abb;
    rs ReSe;
    lso lso1;
    lsob lsob1;
    ral ReAbLin;
    initlso(&lso1);
    initlsob(&lsob1);
    initabb(&abb);
    initRAL(&ReAbLin);
    init(&ReSe);

    while (op != 3) {
        printf("        Bienvenido al sistema! Que operacion desea hacer? \n\n\n");
        printf("<1>         Mostrar Estructuras. \n\n");
        printf("<2>         Comparar estructuras.  \n\n");
        printf("<3>         Salir.\n\n");
        do {
            printf("Ingrese una operacion: ");
            scanf("%d", &op);
        } while (0 >= op || op > 3);
        switch (op) {

            case 1:
                printf("       Que estructura desea revisar? \n\n\n");
                printf("<1>         LSO. \n\n");
                printf("<2>         LSOBB.  \n\n");
                printf("<3>         ABB.  \n\n");
                printf("<4>         RS.  \n\n");
                printf("<5>         RAL.  \n\n");
                printf("<6>         Volver al menu. \n\n");
                printf("<7>         Salir. \n\n");
                do {
                    printf("Ingrese una operacion: \n");
                    scanf("%d", &auxop);
                } while (0 >= auxop || auxop > 7);

                getchar();
                switch (auxop) {

                    //indice muestra lso

                    case 1:
                        if (lso1.contador != 0) {
                            for ( i = 0; i < lso1.contador; i++) {
                                muestraPantalla(lso1.list[i]);
                                getchar();
                            }
                        } else {
                            printf("La lista esta vacia.\n");
                        }
                        break;

                        //Indice muestra lsob

                    case 2:
                        if (lsob1.contador != 0) {
                            for (i = 0; i < lsob1.contador; i++) {
                                muestraPantalla(lsob1.list[i]);
                                getchar();
                            }
                        } else {
                            printf("La lista esta vacia.\n");
                        }
                        break;

                        //indice Muestra abb

                    case 3:

                        if (abb.raiz == NULL) {
                            printf("El arbol esta vacio.\n");
                        } else {
                            auxi = 0;
                            preordenabb(abb.raiz, &auxi);
                        }
                        break;

                        //Indice Muestra rebalse separado
                    case 4:
                        if (ReSe.contador != 0) {
                            for ( i = 0; i < MLV; i++) {
                                printf("\n Lista %d\n", i + 1);
                                ReSe.cur = ReSe.arrlv[i].acc;
                                ReSe.aux = ReSe.arrlv[i].acc;
                                if (ReSe.cur == NULL) {
                                    printf("\n La lista esta vacia.\n");
                                } else {
                                    do {
                                        muestraPantalla(ReSe.cur->vipd);
                                        getchar();
                                        ReSe.aux = ReSe.cur;
                                        ReSe.cur = ReSe.cur->next;
                                    } while (ReSe.cur != NULL);
                                }
                            }
                        } else {
                            printf("La estructura esta vacia. \n");
                        }
                        break;


                        //indice  Muestra Rebalse lineal
                    case 5:
                        if (ReAbLin.cant != 0) {
                            for ( i = 0; i < MAX; i++) {
                                printf("Celda: %d\n", i);
                                if (ReAbLin.vendedores[i].documento == 0) {
                                    printf("\n\nCELDA VIRGEN. \n\n");
                                } else if (ReAbLin.vendedores[i].documento == 1) {
                                    printf("\n\nCELDA VACIA. \n\n");
                                } else {
                                    muestraPantalla(ReAbLin.vendedores[i]);
                                }
                                getchar();
                            }
                        } else {
                            printf("La estructura esta vacia. \n");
                        }
                        break;
                    case 7:
                        op = 3;
                        break;
                }


                break;


            case 2:
                //TOTEST

                if ((f1 = fopen("Operaciones.txt", "r")) == NULL) {
                    printf("El archivo no pudo ser arbierto, por favor intentelo de nuevo mas tarde\n");
                } else {
                    limpiarabb(abb.raiz);
                    limpiars(&ReSe);
                    initabb(&abb);
                    init(&ReSe);
                    initRAL(&ReAbLin);
                    initlso(&lso1);
                    initlsob(&lsob1);

                    while ((feof(f1) == 0)) {
                        fscanf(f1, "%d", &auxlectura);
                        fscanf(f1, "%c", &auxchar);

                        //indice altas
                        if (auxlectura == 1) {
                            //Documento
                            fscanf(f1, "%lu", &auxvendedor.documento);
                            fscanf(f1, "%c", &auxchar);

                            //Nombre
                            /*https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf*/
                            /*usamos una funcion que permite espacios y tiene proteccion de buffer.*/
                            fgets(auxvendedor.nombre, 51, f1);
                            /*https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input*/
                            /*strtok limpia el caracter\n*/
                            strtok(auxvendedor.nombre, "\n");
                            for (i = 0; i < strlen(auxvendedor.nombre); i++) {
                                auxvendedor.nombre[i] = (char) toupper(auxvendedor.nombre[i]);
                            }

                            //Telefono
                            /*https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf*/
                            /*usamos una funcion que permite espacios y tiene proteccion de buffer.*/
                            fgets(auxvendedor.telefono, 17, f1);
                            /*https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input*/
                            /*strtok limpia el caracter\n*/
                            strtok(auxvendedor.telefono, "\n");

                            //Monto
                            fscanf(f1, "%f", &auxvendedor.monto);
                            fscanf(f1, "%c", &auxchar);

                            //Cantidad
                            fscanf(f1, "%d", &auxvendedor.cantidad);
                            fscanf(f1, "%c", &auxchar);

                            //Canal venta
                            fgets(auxvendedor.canal, 21, f1);
                            strtok(auxvendedor.canal, "\n");
                            for (i = 0; i < strlen(auxvendedor.canal); i++) {
                                auxvendedor.canal[i] = (char) toupper(auxvendedor.canal[i]);
                            }

                            //Altas
                            if (lso1.contador < MAXLSO - 1) {
                                altalso(&lso1, auxvendedor);
                            }
                            if (lsob1.contador < MAXLSO - 1) {
                                altalsob(&lsob1, auxvendedor);
                            }
                            altaabb(&abb, auxvendedor);
                            altars(&ReSe, auxvendedor);
                            if (ReAbLin.cant < MAX) {
                                altaRAL(&ReAbLin, auxvendedor);
                            }


                        }

                            //indice bajas

                        else if (auxlectura == 2) {
                            //Documento
                            fscanf(f1, "%lu", &auxvendedor.documento);
                            fscanf(f1, "%c", &auxchar);

                            //Nombre
                            /*https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf*/
                            /*usamos una funcion que permite espacios y tiene proteccion de buffer.*/
                            fgets(auxvendedor.nombre, 51, f1);
                            /*https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input*/
                            /*strtok limpia el caracter\n*/
                            strtok(auxvendedor.nombre, "\n");
                            for (i = 0; i < strlen(auxvendedor.nombre); i++) {
                                auxvendedor.nombre[i] = (char) toupper(auxvendedor.nombre[i]);
                            }

                            //Telefono
                            /*https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf*/
                            /*usamos una funcion que permite espacios y tiene proteccion de buffer.*/
                            fgets(auxvendedor.telefono, 17, f1);
                            /*https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input*/
                            /*strtok limpia el caracter\n*/
                            strtok(auxvendedor.telefono, "\n");

                            //Monto
                            fscanf(f1, "%f", &auxvendedor.monto);
                            fscanf(f1, "%c", &auxchar);

                            //Cantidad
                            fscanf(f1, "%d", &auxvendedor.cantidad);
                            fscanf(f1, "%c", &auxchar);

                            //Canal venta
                            fgets(auxvendedor.canal, 21, f1);
                            strtok(auxvendedor.canal, "\n");
                            for (i = 0; i < strlen(auxvendedor.canal); i++) {
                                auxvendedor.canal[i] = (char) toupper(auxvendedor.canal[i]);
                            }

                            //Bajas
                            if(lso1.contador!=0){
                                bajalso(&lso1, auxvendedor);
                            }
                            if(lsob1.contador!=0) {
                                bajalsob(&lsob1, auxvendedor);
                            }
                            if(abb.raiz!=NULL){
                            bajaabb(&abb, auxvendedor);
                            }
                            if(ReSe.contador!=0){
                            bajars(&ReSe, auxvendedor);
                            }
                            if(ReAbLin.cant!=0) {
                                bajaRAL(&ReAbLin, auxvendedor);
                            }
                        }


                            //indice evocaciones

                        else {
                            //Documento
                            fscanf(f1, "%lu", &auxvendedor.documento);
                            fscanf(f1, "%c", &auxchar);

                            if (lso1.contador != 0) {
                                evocacionlso(&lso1, auxvendedor.documento, &auxres);
                            }
                            else{
                                lso1.eFrCant++;
                            }
                            if (lsob1.contador != 0) {
                                evocacionlsob(&lsob1, auxvendedor.documento, &auxres);
                            }
                            else{
                                lsob1.eFrCant++;
                            }
                            if (abb.raiz != NULL) {
                                evocacionabb(&abb, auxvendedor.documento, &auxres);
                            }
                            else{
                                abb.eFrCant++;
                            }
                            if (ReSe.contador != 0) {
                                evocacionrs(&ReSe, auxvendedor.documento, &auxres);
                            }
                            else{
                                ReSe.eFrCant++;
                            }
                            if (ReAbLin.cant != 0) {
                                evocacionRAL(&ReAbLin, auxvendedor.documento, &auxres);
                            }
                            else{
                                ReAbLin.eFrCant++;
                            }
                        }
                    }
                    fclose(f1);
                    //indice ifs que evitan la division por cero
                    if (abb.bCant == 0)
                        abb.bCant = 1;
                    if (abb.aCant == 0)
                        abb.aCant = 1;
                    if (abb.eExCant == 0)
                        abb.eExCant = 1;
                    if (abb.eFrCant == 0)
                        abb.eFrCant = 1;
                    if (ReSe.bCant == 0)
                        ReSe.bCant = 1;
                    if (ReSe.aCant == 0)
                        ReSe.aCant = 1;
                    if (ReSe.eExCant == 0)
                        ReSe.eExCant = 1;
                    if (ReSe.eFrCant == 0)
                        ReSe.eFrCant = 1;
                    if (lso1.bCant == 0)
                        lso1.bCant = 1;
                    if (lso1.aCant == 0)
                        lso1.aCant = 1;
                    if (lso1.eExCant == 0)
                        lso1.eExCant = 1;
                    if (lso1.eFrCant == 0)
                        lso1.eFrCant = 1;
                    if (lsob1.bCant == 0)
                        lsob1.bCant = 1;
                    if (lsob1.aCant == 0)
                        lsob1.aCant = 1;
                    if (lsob1.eExCant == 0)
                        lsob1.eExCant = 1;
                    if (lsob1.eFrCant == 0)
                        lsob1.eFrCant = 1;
                    if (ReAbLin.bCant == 0)
                        ReAbLin.bCant = 1;
                    if (ReAbLin.aCant == 0)
                        ReAbLin.aCant = 1;
                    if (ReAbLin.eExCant == 0)
                        ReAbLin.eExCant = 1;
                    if (ReAbLin.eFrCant == 0)
                        ReAbLin.eFrCant = 1;


                    /*De acuerdo a nuestras observaciones el rebalse separado es la mejor estructura ya que mantiene costos bajos para todas
                    las operaciones por lo que si asumimos que en las estructuras se pueden dar todas las operaciones con la misma probabilidad
                    el rebalse separado es la que obtiene en mejor comportamiento*/

                    printf("\t\t LSO  \t\t LSOBT \t\t ABB \t\t RS \t\t RAL\n\n");
                    printf("EExMax \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", lso1.eExMax, lsob1.eExMax,
                           abb.eExMax, ReSe.eExMax, ReAbLin.eExMax);
                    printf("EExMed \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n",
                           (float) (lso1.eExMed / lso1.eExCant), (float) (lsob1.eExMed / lsob1.eExCant),
                           (float) (abb.eExMed / abb.eExCant), (float) (ReSe.eExMed / ReSe.eExCant),
                           (float) (ReAbLin.eExMed / ReAbLin.eExCant));
                    printf("EFrMax \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", lso1.eFrMax, lsob1.eFrMax,
                           abb.eFrMax, ReSe.eFrMax, ReAbLin.eFrMax);
                    printf("EFrMed \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n",
                           (float) (lso1.eFrMed / lso1.eFrCant), (float) (lsob1.eFrMed / lsob1.eFrCant),
                           (float) (abb.eFrMed / abb.eFrCant), (float) (ReSe.eFrMed / ReSe.eFrCant),
                           (float) (ReAbLin.eFrMed / ReAbLin.eFrCant));
                    printf("AMax \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", lso1.aMax, lsob1.aMax, abb.aMax,
                           ReSe.aMax, ReAbLin.aMax);
                    printf("AMed \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", (float) (lso1.aMed / lso1.aCant),
                           (float) (lsob1.aMed / lsob1.aCant), (float) (abb.aMed / abb.aCant),
                           (float) (ReSe.aMed / ReSe.aCant), (float) (ReAbLin.aMed / ReAbLin.aCant));
                    printf("BMax \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", lso1.bMax, lsob1.bMax, abb.bMax,
                           ReSe.bMax, ReAbLin.bMax);
                    printf("BMed \t\t %.2f \t\t%.2f \t\t   %.2f \t %.2f \t\t %.2f \n\n", (float) (lso1.bMed / lso1.bCant),
                           (float) (lsob1.bMed / lsob1.bCant), (float) (abb.bMed / abb.bCant),
                           (float) (ReSe.bMed / ReSe.bCant), (float) (ReAbLin.bMed / ReAbLin.bCant));
                    printf("De acuerdo a nuestras observaciones el rebalse separado es la mejor estructura ya que mantiene costos bajos para todas las operaciones por lo que si asumimos que en las estructuras se pueden dar todas las operaciones con la misma probabilidad el rebalse separado es la que obtiene en mejor comportamiento \n\n");
                }
                break;
        }
    }
}


int main() {
    inicio();
    return 0;
}


