#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

struct node
{
    unsigned char key; // Sorted by key.
    Value val;         // Associated data.
    Node *l, *r;       // Left and r subtrees.
    int size;          // Number of nodes in subtree.
};

static Node *create_node(unsigned char key, Value val)
{
    Node *n = malloc(sizeof *n);
    n->key = key;
    n->val = val;
    n->l = n->r = NULL;
    n->size = 1;
    return n;
}

Node *ST_init()
{
    return NULL;
}

static void rec_finish(Node *n)
{
    if (n == NULL)
    {
        return;
    }
    rec_finish(n->l);
    rec_finish(n->r);
    free(n);
}

void ST_finish(Node *root)
{
    rec_finish(root);
}

static int size(Node *n);

// Retorna o maior dos dois itens
int max(int a, int b)
{
    return (a > b) ? a : b;
}
// Função para rotacionar a arvore a direita na subarvore com raiz em y
Node *rightRotate(Node *y)
{
    Node *x = y->l;
    Node *T2 = x->r;

    // rotaciona
    x->r = y;
    y->l = T2;

    // atualiza as alturas
    y->size = max(size(y->l), size(y->r)) + 1;
    x->size = max(size(x->l), size(x->r)) + 1;

    return x;
}

// Função para rotacionar a arvore a esquerda na subarvore com raiz em x
Node *leftRotate(Node *x)
{
    Node *y = x->r;
    Node *T2 = y->l;

    // rotaciona
    y->l = x;
    x->r = T2;

    // Atualiza as alturas
    x->size = max(size(x->l), size(x->r)) + 1;
    y->size = max(size(y->l), size(y->r)) + 1;

    return y;
}

// retorna o fator de balanço da arvore
int getBalance(Node *n)
{
    if (n == NULL)
        return 0;
    return size(n->l) - size(n->r);
}

int compare(unsigned char a, unsigned char b)
{
    return a - b;
}

static Node *rec_put(Node *n, unsigned char key, Value val)
{
    if (n == NULL)
    {
        return create_node(key, val);
    }

    int cmp = compare(key, n->key);
    /* percore a arvore em pre ordem */
    if (cmp < 0)
    {
        n->l = rec_put(n->l, key, val);
    }
    else if (cmp > 0)
    {
        n->r = rec_put(n->r, key, val);
    }

    /* Atualiza a altura do nó ancestral */
    n->size = max(size(n->l), size(n->r)) + 1;

    /* Pega o fator de balanço da arvore pra ver se a inserção desbalanceou a arvore */
    int balance = getBalance(n);

    // se o no esta desbalanceado
    // Desbalanceada a esquerda duas vezes, rotaciona uma vez para a direita
    if (balance > 1 && compare(key, n->l->key) < 0)
        return rightRotate(n);

    // Desbalanceada a direita duas vezes, rotaciona uma vez para a esquerda
    if (balance < -1 && compare(key, n->r->key) > 0)
        return leftRotate(n);

    // Desbalanceada a esquerda e depois a direita, rotaciona a subarvore da esquerda para a esquerda e subarvore atual a direita
    if (balance > 1 && compare(key, n->l->key) > 0)
    {
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }

    //  Desbalanceada a direita e depois a esquerda, rotaciona a subarvore da direita para a direita e subarvore atual para esquerda
    if (balance < -1 && compare(key, n->r->key) < 0)
    {
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }
    return n;
}

Node *ST_put(Node *root, unsigned char key, Value val)
{
    return rec_put(root, key, val);
}

static Value rec_get(Node *n, unsigned char key)
{
    if (n == NULL)
    {
        return NULL_Value;
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        return rec_get(n->l, key);
    }
    else if (cmp > 0)
    {
        return rec_get(n->r, key);
    }
    else /*cmp == 0*/
    {
        return n->val;
    }
}
static Value rec_get_level(Node *n, unsigned char key, int level)
{
    if (n == NULL)
    {
        return NULL_Value;
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        return rec_get(n->l, key);
    }
    else if (cmp > 0)
    {
        return rec_get(n->r, key);
    }
    else /*cmp == 0*/
    {
        return n->val;
    }
}

Value ST_get(Node *root, unsigned char key)
{
    return rec_get(root, key);
}
Value ST_get_level(Node *root, unsigned char key, int level)
{
    return rec_get_level(root, key, level);
}

static void rec_traverse(Node *n, void (*visit)(unsigned char, Value))
{
    if (n == NULL)
    {
        return;
    }
    rec_traverse(n->l, visit);
    visit(n->key, n->val);
    rec_traverse(n->r, visit);
}

void ST_traverse(Node *root, void (*visit)(unsigned char, Value))
{
    rec_traverse(root, visit);
}

Value subset_sum_tree(Key k, Key T[N], Node *root)
{
    Value sum = {{0}};
    Node *n = root;
    for (int i = 0; i < N; i++)
    {
        int b = bit(k, i);
        if (b == 1)
        {
            if (n->r == NULL)
            {
                sum = add(sum, T[i]);
                n->r = create_node(1, sum);
            }
            else
            {
                sum = n->r->val;
            }
            n = n->r;
        }
        else
        {
            if (n->l == NULL)
            {
                n->l = create_node(0, sum);
            }
            n = n->l;
        }
    }
    return sum;
}

// ----------------------------------------------------------------------------
// New from BST1

bool ST_contains(Node *root, unsigned char key)
{
    return compareK(ST_get(root, key), NULL_Value) != 0;
}

static int size(Node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        return n->size;
    }
}

int ST_size(Node *root)
{
    return size(root);
}

bool ST_empty(Node *root)
{
    return ST_size(root) == 0;
}

static Node *rec_min(Node *n)
{
    if (n->l == NULL)
    {
        return n;
    }
    else
    {
        return rec_min(n->l);
    }
}

unsigned char ST_min(Node *root)
{
    return rec_min(root)->key;
}

static Node *rec_max(Node *n)
{
    if (n->r == NULL)
    {
        return n;
    }
    else
    {
        return rec_max(n->r);
    }
}

unsigned char ST_max(Node *root)
{
    return rec_max(root)->key;
}

static Node *rec_floor(Node *n, unsigned char key)
{
    if (n == NULL)
    {
        return NULL;
    }
    int cmp = compare(key, n->key);
    if (cmp == 0)
    {
        return n;
    }
    if (cmp < 0)
    {
        return rec_floor(n->l, key);
    }
    Node *t = rec_floor(n->r, key);
    if (t != NULL)
    {
        return t;
    }
    else
    {
        return n;
    }
}

unsigned char ST_floor(Node *root, unsigned char key)
{
    Node *n = rec_floor(root, key);
    if (n == NULL)
    {
        return NULL_Key;
    }
    else
    {
        return n->key;
    }
}

static Node *rec_ceiling(Node *n, unsigned char key)
{
    if (n == NULL)
    {
        return NULL;
    }
    int cmp = compare(key, n->key);
    if (cmp == 0)
    {
        return n;
    }
    if (cmp < 0)
    {
        Node *t = rec_ceiling(n->l, key);
        if (t != NULL)
        {
            return t;
        }
        else
        {
            return n;
        }
    }
    return rec_ceiling(n->r, key);
}

unsigned char ST_ceiling(Node *root, unsigned char key)
{
    Node *n = rec_ceiling(root, key);
    if (n == NULL)
    {
        return NULL_Key;
    }
    else
    {
        return n->key;
    }
}

static int rec_rank(Node *n, unsigned char key)
{
    if (n == NULL)
    {
        return 0;
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        return rec_rank(n->l, key);
    }
    else if (cmp > 0)
    {
        return 1 + size(n->l) + rec_rank(n->r, key);
    }
    else /*cmp == 0*/
    {
        return size(n->l);
    }
}

int ST_rank(Node *root, unsigned char key)
{
    return rec_rank(root, key);
}

static Node *rec_delmin(Node *n, bool del)
{
    if (n->l == NULL)
    {
        Node *r = n->r;
        if (del)
            free(n);
        return r;
    }
    n->l = rec_delmin(n->l, del);
    n->size = size(n->l) + size(n->r) + 1;
    return n;
}

Node *ST_delmin(Node *root)
{
    return rec_delmin(root, true);
}

static Node *rec_delmax(Node *n)
{
    if (n->r == NULL)
    {
        Node *l = n->l;
        free(n);
        return l;
    }
    n->r = rec_delmax(n->r);
    n->size = size(n->l) + size(n->r) + 1;
    return n;
}

Node *ST_delmax(Node *root)
{
    return rec_delmax(root);
}

static Node *rec_delete(Node *n, unsigned char key)
{
    if (n == NULL)
    {
        return NULL;
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        n->l = rec_delete(n->l, key);
    }
    else if (cmp > 0)
    {
        n->r = rec_delete(n->r, key);
    }
    else /*cmp == 0*/
    {
        if (n->r == NULL)
        {
            Node *l = n->l;
            free(n);
            return l;
        }
        if (n->l == NULL)
        {
            Node *r = n->r;
            free(n);
            return r;
        }
        Node *t = n;
        n = rec_min(t->r);
        n->r = rec_delmin(t->r, false);
        n->l = t->l;
        free(t);
    }
    n->size = size(n->l) + size(n->r) + 1;
    return n;
}

Node *ST_delete(Node *root, unsigned char key)
{
    return rec_delete(root, key);
}
