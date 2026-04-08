#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "operaciones.h"

int main()
{
    int opc = 0;
    bool bandera = true;

    while(bandera){
    printf("---Men%c de la calculadora Binaria---",163);
    printf("\nIngrese una opci%cn:\n1.Suma\n2.Resta\n3.Multiplicaci%cn\n4.Divisi%cn\n5.Salir",162,162,162);
    printf("\nElecci%cn: ",162);

    if(scanf("%d",&opc)==0)
    {
        printf("Opci%cn no v%clida, ingrese un n%cmero\n",162,160,163);
        while (getchar() != '\n');
        system("pause");
        system("cls");
        continue;
    }

    else {

    switch (opc)
    {
        case 1: mostrar_resultado_suma();
                printf("\n");
                system("pause");
                system("cls");
                break;

        case 2: ejecucion();
                printf("\n");
                system("pause");
                system("cls");
                break;

        case 3: mostrar_multiplicacion();
                printf("\n");
                system("pause");
                system("cls");
                break;

        case 4: mostrar_division();
                printf("\n");
                system("pause");
                system("cls");
                break;

        case 5: bandera = false;
                printf("Saliendo del pograma...\n");
                system("pause");
                system("cls");
                break;

        default: printf("\nOpci%cn no v%clida, intentelo de nuevo\n",162,160);
                 system("pause");
                 system("cls");
                 break;
    }
      }
        }
    return 0;
}
