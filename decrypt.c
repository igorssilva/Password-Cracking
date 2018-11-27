#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include <time.h>

int main(int argc, char *argv[])
{
    Key encrypted; // A senha criptografada.
    Key T[N];      // A tabela T.

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./decrypt [encrypted] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    encrypted = init_key((unsigned char *)argv[1]);
    // Exibe a senha encriptada.
    printf("   ");
    print_key(encrypted);
    printf("\n");

    // Lê a tabela T.
    unsigned char buffer[C + 1]; // Buffer temporário.
    for (int i = 0; i < N; i++)
    {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
    // Força bruta
    clock_t tic = clock();
    novo_(encrypted, T);
    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}