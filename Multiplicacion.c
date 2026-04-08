#include <stdio.h>
#include <stdint.h>
#include "operaciones.h"

typedef union {
    float f;
    uint32_t i;
} FloatInt;

#define GET_SIGN(x) (((x) >> 31) & 1)
#define GET_EXP(x)  (((x) >> 23) & 0xFF)
#define GET_FRAC(x) ((x) & 0x7FFFFF)
#define PACK(s, e, f) (((s) << 31) | ((e) << 23) | (f))

float float_multiplicacion(float a, float b) {
    if (a == 0.0f || b == 0.0f) return 0.0f;

    FloatInt fa = {a}, fb = {b}, f_res;

    uint32_t sign_a = GET_SIGN(fa.i), exp_a = GET_EXP(fa.i), man_a = GET_FRAC(fa.i) | 0x800000;
    uint32_t sign_b = GET_SIGN(fb.i), exp_b = GET_EXP(fb.i), man_b = GET_FRAC(fb.i) | 0x800000;

    uint32_t sign_res = sign_a ^ sign_b;
    int32_t exp_res = (int32_t)exp_a + (int32_t)exp_b - 127;

    uint64_t prod = (uint64_t)man_a * (uint64_t)man_b;
    uint32_t frac_res;

    if (prod & (1ULL << 47)) {
        frac_res = (prod >> 24) & 0x7FFFFF;
        exp_res++;
    } else {
        frac_res = (prod >> 23) & 0x7FFFFF;
    }

    f_res.i = PACK(sign_res, exp_res, frac_res);
    return f_res.f;
}

void mostrar_multiplicacion()
{
    // 1. Declarar las variables sin valores iniciales
    float x, y;

    // 2. Imprimir un mensaje en pantalla pidiendo el primer número
    printf("Ingresa el primer numero a multiplicar: ");

    // 3. Leer el valor ingresado y guardarlo en 'x'.
    // Nota el uso de "%f" para float y "&x" para pasar la dirección de la variable.
    scanf("%f", &x);

    // 4. Repetir el proceso para el segundo número
    printf("Ingresa el segundo numero a multiplicar: ");
    scanf("%f", &y);

    // 5. Llamar a la función y mostrar el resultado
    printf("\nCalculando...\n");
    printf("Resultado (Nuestro Algoritmo): %.2f * %.2f = %.2f\n", x, y, float_multiplicacion(x, y));

}

