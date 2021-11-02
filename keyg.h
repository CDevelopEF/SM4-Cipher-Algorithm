#ifndef KEYG_H_INCLUDED
#define KEYG_H_INCLUDED
#include <inttypes.h>

#define ROUND_LENGHT 32
#define NUM_KEY 35

//prototipos de funcion


typedef struct sms4_key{

    uint32_t rkey[ROUND_LENGHT];
    uint32_t K_param[NUM_KEY];

}sms4_key;

sms4_key keysch;

uint32_t linear_sustitution(uint32_t pointer);
uint32_t cyclic_shift(uint32_t vector, const int rotation);
void     key_generation(sms4_key *pointer);
uint32_t Sbox_s(uint32_t vector);

extern const uint32_t FK[4];
extern const uint32_t CK[32];
extern const uint32_t MK[4];
extern const uint8_t  Sbox[256];

#endif // KEYG_H_INCLUDED
