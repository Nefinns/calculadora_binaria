#include "operaciones.h"
#include <stdint.h>
#include <stdio.h>

// usamos un union para tener la memoria apuntada a un flotante
typedef union{
    uint32_t un;
    float fl;
} FloatConversion;

uint32_t restaF(uint32_t nu1, uint32_t nu2){
    // aplicamos un xor para cambiar el signo del bit haciendo  nu1 + (-nu2)
    nu2 ^= (1u << 31);

    // desplazamos para aislar el bit de signo (0 positivo, 1 negativo)
    uint32_t sigNu1 = (nu1 >> 31) & 1;
    uint32_t sigNu2 = (nu2 >> 31) & 1;

    // desplazamos los bits 23 veces para quedarnos con los 8 bits del exponente y enmascararlo
    int32_t  expNu1  = (nu1 >> 23) & 0xFF;
    int32_t  expNu2  = (nu2 >> 23) & 0xFF;

    // se usa el hexadecimal 0x7FFFFF para extraer los 23 bits de fraccion y el 0x800000 para encender el '1' implícito necesario para operaciones
    uint32_t mantNu1 = (nu1 & 0x7FFFFF) | 0x800000;
    uint32_t mantNu2 = (nu2 & 0x7FFFFF) | 0x800000;

    // en caso de que todo el numero sea cero, forzamos la mantisa a 0
    if ((nu1 & 0x7FFFFFFF) == 0) mantNu1 = 0;
    if ((nu2 & 0x7FFFFFFF) == 0) mantNu2 = 0;

    // asumimos por defecto que el exponente ganador será el de nu1
    uint32_t  expR = expNu1;

    // comparamos exponentes para saber cual es mayor desplazamos la mantisa del menor a la derecha (dividiendo) para alinear los puntos decimales.
    if (expNu1 > expNu2){
        int diferencia = expNu1 - expNu2;
        // si la diferencia es mayor a 24, limitamos para no empujar bits infinitamente al vacio
        if (diferencia > 24) diferencia = 24;
        mantNu2 >>= diferencia;
    } else if (expNu2 > expNu1) {
        int diferencia = expNu2 - expNu1;
        if (diferencia > 24) diferencia = 24;
        mantNu1 >>= diferencia;
        expR = expNu2; // si nu2 era mayor, corregimos el exponente resultante
    }

    uint32_t sigR;
    uint32_t mantR;

    if (sigNu1 == sigNu2) {
        // si tienen el mismo signo, el resultado conserva el signo y sumamos las mantisas
        sigR = sigNu1;
        mantR = mantNu1 + mantNu2;

        // normalizar si hubo acarreo (si la suma superó los 24 bits ocupando el bit 25)
        if (mantR & (1 << 24)) {
            mantR >>= 1;           // desplazamos la mantisa a la derecha para que quepa
            expR++;                // compensamos sumandole 1 al exponente
        }
    } else {
        // si son de distinto signo, restamos siempre la mantisa menor de la mayor para evitar negativos
        if (mantNu1 >= mantNu2) {
            sigR = sigNu1; // gana el signo de nu1 por ser mas grande
            mantR = mantNu1 - mantNu2;
        } else {
            sigR = sigNu2; // gana el signo de nu2
            mantR = mantNu2 - mantNu1;
        }
    }

    // normalizar por cancelación (cuando al restar numeros similares se llenan de ceros a la izquierda y se pierde el '1' implícito)
    if (mantR != 0) {
        // mientras no haya un '1' en la posicion 23 (0x800000), desplazamos a la izquierda y restamos al exponente
        while (!(mantR & 0x800000)) {
            mantR <<= 1;
            expR--;
        }
    } else {
        // si al restar dio exactamente cero, retornamos 0 para evitar ciclos infinitos
        return 0;
    }

    // empaquetar todo: movemos el signo al bit 31, el exponente al bit 23 y apagamos el '1' implícito de la mantisa
    return (sigR << 31) | ((expR & 0xFF) << 23) | (mantR & 0x7FFFFF);
}

void ejecucion(){
    FloatConversion n1, n2, res;

    printf(" Restador de Punto Flotante IEEE 754 \n\n");

    printf("Ingresa el primer numero: ");
    scanf("%f", &n1.fl);

    printf("Ingresa el segundo numero: ");
    scanf("%f", &n2.fl);

    res.un = restaF(n1.un, n2.un);

    printf("\n Resta de %.4f - %.4f:\n", n1.fl, n2.fl);
    printf("Resultado : %.4f\n", res.fl);

}
