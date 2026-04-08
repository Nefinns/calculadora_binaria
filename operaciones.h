#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED
#include <stdint.h>
/*Suma*/
float sumador_bits(float a,float b);
void mostrar_resultado_suma();

/*Resta*/
uint32_t restaF(uint32_t nu1, uint32_t nu2);
void ejecucion();

/*Multiplicación*/
float float_multiplicacion(float a,float b);
void mostrar_multiplicacion();

/*Division*/
float float_division(float a, float b);
void mostrar_division();

#endif // OPERACIONES_H_INCLUDED
