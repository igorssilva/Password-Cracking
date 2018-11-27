#include <stdio.h>
#include "key.h"
#include "ST.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[])
{
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (s[i] == ALPHABET[j])
            {
                k.digit[i] = j;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("  ");
    for (int i = 0; i < C; i++)
    {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++)
    {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key k, int i)
{
    return (k.digit[i / B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b)
{
    Key c = {{0}};
    int carry = 0;
    for (int i = C - 1; i >= 0; i--)
    {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum % R;
        carry = sum >= R;
    }
    return c;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N])
{
    Key sum = {{0}};
    for (int i = 0; i < N; i++)
    {
        if (bit(k, i))
        {
            sum = add(sum, T[i]);
            //printf("%2d ", i); // Para teste.
            // print_key(T[i]);   // Para teste.
        }
    }
    return sum;
}

int compare(Key a, Key b)
{

    for (int i = 0; i < C; i++)
    {
        if (a.digit[i] < b.digit[i])
        {
            return -1;
        }
        if (a.digit[i] > b.digit[i])
        {
            return 1;
        }
    }

    return 0;
}

void dec_forca_bruta_rec(Key set[N], Key prefix, int n, int k, Key encrypted)
{

    // Base case: k is C,
    // print prefix
    if (k == C)
    {
        Key passwordEncrypted = subset_sum(prefix, set);
        if (compare(encrypted, passwordEncrypted) == 0)
        {
            print_key_char(prefix);
        }
        return;
    }

    // One by one add all characters
    // from set and recursively
    // call for k equals to k+eu n1
    for (int i = 0; i < n; ++i)
    {

        // Next character of input added
        prefix.digit[k] = i;

        // k is increased, because
        // we have added a new character
        dec_forca_bruta_rec(set, prefix, n, k + 1, encrypted);
    }
}

void dec_forca_bruta(Key encrypted, Key T[N])
{
    Key k;
    Key a;
    for (int i = 0; i < C; i++)
    {
        k.digit[i] = 0;
    } 
    for (int i = 0; i < C; i++)
    {
        a.digit[i] = 0;
    }
    a.digit[C] = 1;
    double tam = pow(R, C);
    for (double i = 0; i < tam; i++)
    {
            print_key(k);
        Key passwordEncrypted = subset_sum(k, T);
        if (compare(encrypted, passwordEncrypted) == 0)
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
    //dec_forca_bruta_rec(T, k, R, 0, encrypted);
}

Node *dec_symbol_table_rec(Key set[N], Key prefix, int n, int k, Node *root)
{

    // Base case: k is C,
    // print prefix
    if (k == C)
    {
        Key passwordEncrypted = subset_sum(prefix, set);

        root = ST_put(root, passwordEncrypted, prefix);

        return root;
    }

    // One by one add all characters
    // from set and recursively
    // call for k equals to k-1
    for (int i = 0; i < n; ++i)
    {

        // Next character of input added
        prefix.digit[k] = i;
        //prefix = add(prefix, set[i]);

        // k is decreased, because
        // we have added a new character
        root = dec_symbol_table_rec(set, prefix, n, k + 1, root);
    }

    return root;
}

void dec_symbol_table(Key encrypted, Key T[N])
{
    Key k;
    Node *root = ST_init();
    root = dec_symbol_table_rec(T, k, R, 0, root);
    printf("tamanho arvore: %d\n", ST_size(root));
    k = ST_get(root, encrypted);
    print_key_char(k);
    /* while (compare(k, NULL_Value) != 0)
    {
        print_key_char(k);
        root = ST_delete(root, k);
        k = ST_get(root, encrypted);
    }*/

    ST_finish(root);
}
