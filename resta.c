#include <stdint.h>

// usamos 
typedef union{
    
    uint32_t un;
    float fl;

} FloatConversion;


uint32_t restaF(uint32_t nu1, uint32_t nu2){
// aplicamos un xor para cambiar el signo del bit haciendo  nu1 + (-nu2)
    nu2 ^= (1u << 31);

// desplazamos el bit de signo para poder cambiarlo de positivo a negativo y viceverza
    uint32_t sigNu1 = (nu1 >> 31) & 1;
    uint32_t sigNu2 = (nu2 >> 31) & 1;
// desplazamos los bits 23 veces para quedarnos con los 8 bits del exponente  y enmascararlo
    int32_t  expNu1  = (nu1 >> 23) & 0xFF;
    int32_t  expNu2  = (nu2 >> 23) & 0xFF;
// se usa el hexadecimal 0x7FFFFF para tener los 23 bits  y el 0x800000 se usa para operaciones 
    uint32_t mantNu1 = (nu1 & 0x7FFFFF) | 0x800000;
    uint32_t mantNu2 = (nu2 & 0x7FFFFF) | 0x800000;
// en caso de que sea cero 
    if ((nu1 & 0x7FFFFFFF) == 0) mantNu1 = 0;
    if ((nu2 & 0x7FFFFFFF) == 0) mantNu2 = 0;

    uint32_t  expR = expNu1;

    if (expNu1 > expNu2){
    int diferencia = expNu1 - expNu2;
        if (diferencia > 24) diferencia = 24; 
        mantNu2 >>= diferencia;
    } else if (expNu2 > expNu1) {
        int diferencia = expNu2 - expNu1;
        if (diferencia > 24) diferencia = 24;
        mantNu1 >>= diferencia;
        expR = expNu2;
    }
        



}
