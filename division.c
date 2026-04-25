#include <stdio.h>
#include <stdint.h>
#include "operaciones.h"

// Union para manipular bits del float
typedef union {
    float f;
    uint32_t i;
} FloatInt;

// Macros para extraer e inyectar las partes del formato IEEE 754
#define GET_SIGN(x) (((x) >> 31) & 1)
#define GET_EXP(x)  (((x) >> 23) & 0xFF)
#define GET_FRAC(x) ((x) & 0x7FFFFF)
#define PACK(s, e, f) (((s) << 31) | ((e) << 23) | (f))

// --- ALGORITMO DE DIVISIÓN DE PUNTO FLOTANTE ---
float float_division(float a, float b) {

    // Caso base: 0 dividido entre cualquier cosa es 0
    if (a == 0.0f) return 0.0f;

    FloatInt fa = {a}, fb = {b}, f_res;

    // 1. Extraer componentes (añadiendo el 1 implícito a la mantisa: 0x800000)
    uint32_t sign_a = GET_SIGN(fa.i), exp_a = GET_EXP(fa.i), man_a = GET_FRAC(fa.i) | 0x800000;
    uint32_t sign_b = GET_SIGN(fb.i), exp_b = GET_EXP(fb.i), man_b = GET_FRAC(fb.i) | 0x800000;

    // 2. Calcular Signo (XOR) y Exponente (Resta de exponentes + Bias)
    uint32_t sign_res = sign_a ^ sign_b;
    int32_t exp_res = (int32_t)exp_a - (int32_t)exp_b + 127;

    // 3. Dividir mantisas
    // Desplazamos man_a 23 bits a la izquierda antes de dividir para no perder los "decimales"
    uint64_t num = (uint64_t)man_a << 23;
    uint32_t frac_res = num / man_b;

    // 4. Normalizar
    // Revisamos el bit 23 para ver si el resultado es de la forma 1.xxxx o 0.1xxxx
    if (frac_res & (1 << 23)) {
        // Tiene forma 1.xxxx (El bit 23 es 1). Solo quitamos el 1 implícito.
        frac_res = frac_res & 0x7FFFFF;
    } else {
        // Tiene forma 0.1xxxx (El bit 23 es 0 y el 22 es 1).
        // Desplazamos 1 bit a la izquierda para normalizar y restamos 1 al exponente.
        frac_res = (frac_res << 1) & 0x7FFFFF;
        exp_res--;
    }

    // 5. Empaquetar todo de vuelta en un float
    f_res.i = PACK(sign_res, exp_res, frac_res);
    return f_res.f;
}

// Ejemplo de uso interactivo
void mostrar_division() {
    float x, y;

    printf("Ingresa el dividendo (numero a dividir): ");
    scanf("%f", &x);

    printf("Ingresa el divisor (entre cuanto lo vas a dividir): ");
    scanf("%f", &y);

    printf("\nEntradas:\nDecimal: %.4f / %.4f",x,y);
    printf("\nBinario (32 bits):");
    printf("\n[S: 1 bit] [Exponente: 8 bits] [Mantisa: 23 bits]\n");

    traducir_binario(x);
    printf(" / ");
    traducir_binario(y);

    printf("\n\nCalculando...\n");

    if(y == 0)
    {
        printf("\nError: No se puede dividir entre cero, intente con otro dato");
    }
    else
    {
    printf("\nResultado:\n\n%.4f en decimal\n\n",float_division(x, y));
    printf("[S: 1 bit] [Exponente: 8 bits] [Mantisa: 23 bits]\n");
    traducir_binario(float_division(x,y));
    printf(" en binario");
    }
}
