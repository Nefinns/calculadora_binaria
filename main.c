#include <stdio.h>
#include "operaciones.h"

typedef union {
    uint32_t un;
    float fl;
} FloatConversion;

int main() {
    FloatConversion n1, n2, res;

    printf(" Restador de Punto Flotante IEEE 754 \n\n");
    
    printf("Ingresa el primer numero: ");
    scanf("%f", &n1.fl);
    
    printf("Ingresa el segundo numero: ");
    scanf("%f", &n2.fl);

    res.un = restaF(n1.un, n2.un);

    printf("\n Resta de %f - %f:\n", n1.fl, n2.fl);
    printf("Resultado : %f\n", res.fl);
    
    return 0;
}