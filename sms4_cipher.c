#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "keyg.h"
#include "sms4_cipher.h"

uint32_t input_text[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};

void encryption(plaintext *pointer, uint32_t input_text[4]){

        pointer->X[0] = input_text[0];
        pointer->X[1] = input_text[1];
        pointer->X[2] = input_text[2];
        pointer->X[3] = input_text[3];

        for(int i = 0; i < NUM_TEXT; i++){

            uint32_t aux = pointer->X[i + 1] ^ pointer->X[i + 2] ^ pointer->X[i + 3] ^ keysch.rkey[i];

            pointer->X[i + 4] = pointer->X[i] ^ linear_s(Sbox_s(aux));


        }

        input_text[0] = pointer->X[35];                                  //Reverse last round (a0, a1, a2, a3) -> (a3, a2, a1, a0)
        input_text[1] = pointer->X[34];
        input_text[2] = pointer->X[33];
        input_text[3] = pointer->X[32];
}
uint32_t linear_s(uint32_t pointer){                                     //Linear Sustitution V_{2}^32 not L'

        pointer = pointer ^ cyclic_shift(pointer, 2) ^ cyclic_shift(pointer, 10) ^ cyclic_shift(pointer, 18) ^ cyclic_shift(pointer, 24);
        return pointer;
}

void decryption(plaintext *pointer, uint32_t input_text[4]){

        pointer->X[0] = input_text[0];
        pointer->X[1] = input_text[1];
        pointer->X[2] = input_text[2];
        pointer->X[3] = input_text[3];

        for(int i = 0; i < NUM_TEXT; i++){

            uint32_t aux = pointer->X[i + 1] ^ pointer->X[i + 2] ^ pointer->X[i + 3] ^ keysch.rkey[31 - i];

            pointer->X[i + 4] = pointer->X[i] ^ linear_s(Sbox_s(aux));


        }

        input_text[0] = pointer->X[35];                                  //Reverse last round (a0, a1, a2, a3) -> (a3, a2, a1, a0)
        input_text[1] = pointer->X[34];
        input_text[2] = pointer->X[33];
        input_text[3] = pointer->X[32];
}
