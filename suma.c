#include "operaciones.h"
#include <stdint.h>


/*Máscaras para usar DESPUÉS de desplazar (convenientes para cálculos)*/
#define EXP_FIELD_MASK  0xFFU       /* 8 bits de exponente*/
#define SIGN_FIELD_MASK 0x1U        /* 1 bit de signo*/
#define MANT_FIELD_MASK 0x7FFFFFU   /* 23 bits de mantisa*/

/*Declaración de constantes para las mascaras binarias siguiendo
el estandar IEEE 754*/
#define SIGN_MASK 0x80000000
#define EXP_MASK  0x7F800000
#define MANT_MASK 0x007FFFFF
#define HIDDEN_BIT 0x00800000
#define EXP_BIAS   127

float sumador_bits(float a,float b)
{
    /*Paso 1, representamos los floats como enteros por medio de
    union para poder usar los operadores de bits*/

    union FloatInt
    {
        uint32_t i;
        float f;
    };

    union FloatInt a_unido = {.f = a},b_unido = {.f = b};

    uint32_t bits_a = a_unido.i;
    uint32_t bits_b = b_unido.i;


    /*Paso 2, Extracción de componentes*/
    uint32_t sign_a = bits_a >>31;
    uint32_t exp_a = (bits_a >> 23) & EXP_FIELD_MASK;
    uint32_t mant_a = bits_a & MANT_FIELD_MASK;

    uint32_t sign_b = bits_b >>31;
    uint32_t exp_b = (bits_b >> 23) & EXP_FIELD_MASK;
    uint32_t mant_b = bits_b & MANT_FIELD_MASK;

    /*Restauración del bit omitido en la mantisa*/
    uint32_t mant_full_a = mant_a | HIDDEN_BIT;
    uint32_t mant_full_b = mant_b | HIDDEN_BIT;

    /*Alineación de mantisas según sus exponentes*/
    /*Calculo del exponente del resultado*/
    int32_t diferencia = exp_a - exp_b;
    int32_t exp_resultado = 0;

    if(exp_a > exp_b)
    {
        mant_full_b>>= diferencia;
        exp_resultado = exp_a;
    }

    else if (exp_b > exp_a)
    {
        mant_full_a>>=(-diferencia);
        exp_resultado = exp_b;
    }

    else
    {
        exp_resultado = exp_a;
    }

    /*Paso 4*/
    /*Suma binaria según signos iguales o diferentes*/
    uint32_t suma = 0;
    uint32_t sign_result = 0;

    if (sign_a == sign_b)
    {
        suma = mant_full_a + mant_full_b;
        sign_result = sign_a;
    }

    else
    {
        if (mant_full_a >= mant_full_b)
        {
            suma = mant_full_a - mant_full_b;
            sign_result = sign_a;
        }
        else
        {
            suma = mant_full_b - mant_full_a;
            sign_result = sign_b;
        }
    }

    /*Paso 5*/
    /*Normalización dependiendo de si hubo acarreo
    o el resultado es menor a lo esperado por el
    estandar IEEE 754 (solo debe haber un 1 a la izquierda
    del punto decimal)*/
    if (suma == 0)
    {
        return 0.0f;
    }
    else if (suma & (1<<24))
    {
        suma>>=1;
        exp_resultado++;
    }

    else if (!(suma & HIDDEN_BIT)&&suma!=0)
    {
     while(!(suma & HIDDEN_BIT))
    {
        suma<<=1;
        exp_resultado--;
    }
    }

    /*Paso 6 empaquetado y devolución a float*/
    uint32_t mant_final = suma & MANT_FIELD_MASK;

    uint32_t resultado = (sign_result<<31)|(exp_resultado<<23)|mant_final;

    union FloatInt resultado_unido = {.i = resultado};

    float resultado_decimal = resultado_unido.f;

    return resultado_decimal;
}

void mostrar_resultado_suma()
{
    float num1= 0,num2 = 0,result_suma = 0;

    printf("\nEste es un sumador binario de n%cmeros con punto decimal.\n",163);
    printf("Ingrese el primer n%cmero: ",163);
    scanf("%f",&num1);
    printf("\nIngrese el segundo n%cmero: ",163);
    scanf("%f",&num2);

    result_suma = sumador_bits(num1,num2);
    printf("\nEl resultado de la suma es: %.4f",result_suma);
}



