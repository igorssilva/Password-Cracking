/**********************************************************************
 *  Criptografa uma senha usando o algoritmo de soma de subconjunto.
 *
 *  Compilação:   $ gcc -Wall key.c encrypt.c -o encrypt
 *  Execução:     $ ./encrypt password < in/rand8.txt
 *                   vbskbezp
 *
 *  Nota: lembre-se de sempre ajustar a macro C em key.h antes de
 *  compilar e executar com uma senha de tamanho específico.
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include "ST.h"

int main(int argc, char *argv[])
{
    Key password;  // A senha fornecida pelo usuário.
    Key encrypted; // A senha criptografada.
    Key T[N];      // A tabela T.

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    password = init_key((unsigned char *)argv[1]);
    // Exibe a senha informada.
    printf("   ");
    print_key(password);
    printf("\n");

    // Lê a tabela T.
    unsigned char buffer[C + 1]; // Buffer temporário.
    for (int i = 0; i < N; i++)
    {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }

    // Calcula a soma de subconjunto.
    encrypted = subset_sum(password, T);

    // Exibe o resultado.
    printf("\n   ");
    print_key(encrypted);
    printf("\n");

    Key lista[R][C];
    for (int l = 0; l < R; l++)
    {
        for (int p = 0; p <= C; p++)
        {

            Key sum = {{0}};
            for (int b = 0; b < B; b++)
            {
                int bitt = bit_l(l, b);
                if (bitt)
                {
                    sum = add(sum, T[b + (p * B)]);
                }
            }

            lista[l][p] = sum;
        }
    }

    Key teste = lista[password.digit[0]][0];
    printf("letra: %c", ALPHABET[password.digit[0]]);
    printf("\n");
    print_key(teste);
    printf("\n");
    for (int i = 1; i < C; i++)
    {
        teste = add(teste, lista[password.digit[i]][i]);
        printf("letra: %c", ALPHABET[password.digit[i]]);
        printf("\n");
        print_key(teste);
        printf("\n");
    }

    printf("\n");
    print_key(teste);
    printf("\n");
    return 0;
}
