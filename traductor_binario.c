#include "operaciones.h"
#include <stdio.h>
#include <stdlib.h>
void traducir_binario(float f)
{
    uint32_t bit_actual = 0;
    union
    {
        float fl;
        uint32_t in;
    }u;

    u.fl = f;

    for(int i = 31; i>=0;i--)
    {
        bit_actual = (u.in >> i & 1);
        printf("%d",bit_actual);

        if(i == 31 || i == 23) printf(" ");
    }
}
