#include <stdint.h>


typedef union{
    
    uint32_t un;
    float fl;

} FloatConversion;


uint32_t restaF(uint32_t nu1, uint32_t nu2){

    nu2 ^= (1u << 31);

    uint32_t sign_a = (nu1 >> 31) & 1;
    uint32_t sign_b = (nu2 >> 31) & 1;
    int32_t  exp_a  = (nu1 >> 23) & 0xFF;
    int32_t  exp_b  = (nu2 >> 23) & 0xFF;

}
