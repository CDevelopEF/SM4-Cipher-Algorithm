#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/stat.h>
#include "keyg.h"
#include "sms4_cipher.h"

void state(void);
void completamiento(uint32_t *const, int);
int descompletamiento(uint32_t *);

int main(int args, char *argv[])
{
        FILE *in;
        FILE *out;
        struct stat stat1;
        int nb, rest;

        key_generation(&keysch);

        stat(argv[2], &stat1);

        printf("El archivo tiene %lu bytes\n", stat1.st_size);

        if((args > 2 && strcmp(argv[1], "c") == 0)){
            printf("Cifrando. . . . . . . . . . . . . . .\n");
            in  = fopen(argv[2], "rb");
            out = fopen(argv[3], "wb");

            nb = stat1.st_size / 16;
            rest = stat1.st_size%16;

            for(int i =0; i < nb; i++){

                fread(&input_text,sizeof(input_text), 1 , in);

                encryption(&x_text, input_text);

                fwrite(&input_text, sizeof(input_text), 1, out);

            }

            if (rest > 0){
                 fread(&input_text,sizeof(input_text), 1 , in);

                completamiento(input_text,rest);
                encryption(&x_text, input_text);

                fwrite(&input_text, sizeof(input_text), 1, out);
            }

            fclose(in);
            fclose(out);
            printf("El texto a sido Cifrado correctamente\n");
            }

            else if((args > 2 && strcmp(argv[1], "d") == 0)){
                printf("Decifrando. . . . . . . . . . . . . . .\n");
                in  = fopen(argv[2], "rb");
                out = fopen(argv[3], "wb");

                nb = stat1.st_size / 16;

            for(int i =0; i < nb-1; i++){

                fread(&input_text,sizeof(input_text), 1 , in);

                decryption(&x_text, input_text);

                fwrite(&input_text, sizeof(input_text), 1, out);

            }
            fread(&input_text,sizeof(input_text), 1 , in);

            decryption(&x_text, input_text);

            fwrite(&input_text, descompletamiento(input_text), 1, out);

            fclose(in);
            fclose(out);
            printf("El texto a sido Decifrado correctamente\n");

            }

        return 0;
}

void Test_SMS4_KeySchedule(){
    for(int i = 0; i < 32; i++){

        printf("\nrk[%i]=%x  x[%i]=%x\n", i , keysch.rkey[i], i, x_text.X[i + 4 ] );
    }
    printf("\n\t\t Text Cipher \n");
    printf(   "\t\t ###########\n");
    printf("\t%x %x %x %x", input_text[0],input_text[1],input_text[2],input_text[3]);


}

void completamiento(uint32_t *const texto, int rest){
    int a1 = rest/4, a2 = rest%4;
    uint32_t comp[4] = {0x00000000,
                        0x000000ff,
                        0x0000ffff,
                        0x00ffffff};
    texto[a1]= texto[a1]&comp[a2];
    a1++;
    for(int i = a1; i < 4; i++){
        texto[i] = 0;
    }
}

int descompletamiento(uint32_t *texto){
    int rest = 0;
    uint32_t comp[4] = {
                        0xff000000,
                        0x00ff0000,
                        0x0000ff00,
                        0x000000ff};

    for(int i = 3; i >= 0; i--){

        for(int j = 0; j < 4; j++){

            if(( texto[i] & comp[j]) == 0x00000000){

                rest++;
            }
            else{
                break;
            }
        }
    }
    return (16 - rest);
}
