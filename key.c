#include <stdio.h>
#include "key.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
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
        printf("%c", ALPHABET[(unsigned char)(k.digit[i])]);
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
        if (k.digit[i] < 0)
            printf("%d", k.digit[i]);
        else
        {
            printf("%c", ALPHABET[(unsigned char)(k.digit[i])]);
        }
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

    int i;
    for (i = 0; i < N; i++)
    {
        int b = bit(k, i);

        if (b)
        {
            sum = add(sum, T[i]);

            /*   printf("%2d   ", i); // Para teste.
            print_key(T[i]);     // Para teste.
            printf("sum: ");
            print_key(sum); // Para teste.
            printf("\n");*/
        }
    }

    return sum;
}

int compareK(Key a, Key b)
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

bool equal(Key a, Key b)
{

    for (int i = 0; i < C; i++)
    {
        if (a.digit[i] != b.digit[i])
        {
            return false;
        }
    }

    return true;
}

void dec_forca_bruta(Key encrypted, Key T[N])
{
    Key k;
    static Key a;

    // Senha para incrementar 1

    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = subset_sum(k, T);
        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
}

/*Key subset_sum_custom(Key k, Key T[N], Node *root)
{
    Key sum = {{0}};
    for (int i = 0; i < C; i++)
    {
        unsigned char letra = k.digit[i];
        Key val = ST_get(root, letra);
        if (!equal(val, NULL_Value))
        {
            for (int j = 0; j < B; j++)
                if ((item >> (B - 1 - j % B)) & 1)
                {
                    sumIn = add(sumIn, T[j]);
                    printf("%2d ", j); // Para teste.
                    print_key(T[j]);   // Para teste.
                }
        }
        sum = add(sum, val);
    }
    return sum;
}*/

void dec_symbol_table_new(Key encrypted, Key T[N])
{
    /*  Key k = {{0}};
    Key a = {{0}};

    // Senha para incrementar 1

    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);
    Node *root = ST_init();
    root = ST_put(root, NULL_Key, NULL_Value);
    for (double i = 0; i < tam; i++)
    {
        Value passwordEncrypted = subset_sum_tree(k, T, root);
        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
    ST_finish(root);*/
}

void dec_symbol_table(Key encrypted, Key T[N])
{

    /*  Key k={{0}};
    Key a;
    // Senha base



    // Key symbol_table[R];
    // Arvore de simbolos
    Node *root = ST_init();
    for (int j = 0; j < R; j++)
    {
        Key sum = {{0}};
        unsigned char letra = ALPHABET[j];
        for (int i = 0; i < B; i++)
        {
            if ((letra >> (B - 1 - i % B)) & 1)
            {
                sum = add(sum, T[i]);
            }
        }
        root = ST_put(root, letra, sum);
    }
    //root = ST_put(root, k, val);

    // Senha para somar
    for (int i = 0; i < C; i++)
    {
        a.digit[i] = 0;
    }
    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key val = subset_sum_custom(k, T, root);

        // Key keyAchou = ST_floor(root, k);
        //   Key valAchou = ST_get(root, keyAchou);

        if (equal(encrypted, val))
        {
            print_key_char(k);
        }

        k = add(k, a);
    }*/

    /*  Key k;
    Node *root = ST_init();
    root = dec_symbol_table_rec(T, k, R, 0, root);
    printf("tamanho arvore: %d\n", ST_size(root));
    k = ST_get(root, encrypted);
    print_key_char(k);
     while (compare(k, NULL_Value) != 0)
    {
        print_key_char(k);
        root = ST_delete(root, k);
        k = ST_get(root, encrypted);
    }*/

    //ST_finish(root);
}

/*void teste_symbol_table_rec(Key encrypted, Key map[N], Key sum_atual, Key prefix, int pos, Node *root)
{
    // Base case: pos is 0,
    // print prefix
    if (pos == C)
    {
         if(equal(prefix, init_key("passw"))){
            
            print_key_char(prefix);
        }
        // Key passwordEncrypted = subset_sum(prefix, map);
        if (equal(encrypted, sum_atual))
        {
            print_key_char(prefix);
        }
        return;
    }

    // One by one add all characters
    // from set and recursively
    // call for pos equals to pos-1
    for (int i = 0; i < R; ++i)
    {

        // Next character of input added
        prefix.digit[pos] = i;

        int ini = ((pos * (B - 1)) + B);
        for (int j = ini; j < N; j++)
        {
            if (bit(prefix, j))
            {
                sum_atual = add(sum_atual, map[j]);
                // printf("%2d ", i); // Para teste.
                // print_key(T[i]);   // Para teste.
            }
        }

        // k is increased, because
        // we have added a new character
        teste_symbol_table_rec(encrypted, map, sum_atual, prefix, pos + 1, root);
    }
}*/

void teste_symbol_table(Key encrypted, Key T[N])
{

    /* static Key pass;
    static Key sum_atual;
    Node *root = ST_init();
    teste_symbol_table_rec(encrypted, T, sum_atual, pass, 0, root);*/
}

int bit_l(unsigned char k, int i)
{
    return (k >> (B - 1 - i % B)) & 1;
}
void novo_(Key encrypted, Key T[N])
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
    // Senha para incrementar 1

    a.digit[C - 1] = 1;
    double tam = pow(R, C);

    //Key ***lista = malloc(sizeof(*lista) * R);

    Key lista[R][C];
    for (int l = 1; l < R; l++)
    {
        for (int p = 0; p <= C; p++)
        {

            Key sum;
            for (int z = 0; z < C; z++)
            {
                k.digit[z] = 0;
            }
            for (int b = 0; b < B; b++)
            {
                int bitt = bit_l(l, b);
                if (bitt)
                {
                    sum = add(sum, T[b + (p * B)]);
                }
            }

            lista[l][p] = sum;
            print_key(lista[l][p]);
        }
    }
    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = lista[(k.digit[0])][0];
        for (int j = 1; j < C; j++)
        {
            //Key *temp = (lista[k.digit[j]][j]);
            passwordEncrypted = add(passwordEncrypted, lista[k.digit[j]][j]);
        }
        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
}