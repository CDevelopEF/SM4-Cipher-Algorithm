#ifndef SMS4_CIPHER_H_INCLUDED
#define SMS4_CIPHER_H_INCLUDED

#include <inttypes.h>

#define NUM_TEXT 35


extern uint32_t input_text[4];
typedef struct plaintext{

uint32_t X[NUM_TEXT];

}plaintext;
plaintext x_text; //estructura que contiene las X segun estandar de 0 a 35


void encryption(plaintext *pointer, uint32_t input_text[4]);
void decryption(plaintext *pointer, uint32_t input_text[4]);
uint32_t linear_s(uint32_t pointer);

#endif // SMS4_CIPHER_H_INCLUDED
