#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

// Very basic implementation that assumes that
// keys are upper caps letters.

static Value *st; // The table.
static int N;    // Max number of elements.

// Basic hack.
// Only works if keys are upper caps letters.
#define h(A)        (A - 65)
#define inv_h(A)    (A + 65)

// Create an empty symbol table.
void ST_init(int maxN) {
    N = 26; // Only capital letters.
    st = malloc(N * sizeof(Value));
    for (int i = 0; i < N; i++) {
        st[i] = NULL_Value;
    }
}

// Put key-value pair into the table: st[key] = val; .
void ST_put(Key key, Value val) {
    st[h(key)] = val;
}

// Value paired with key: st[key] .
Value ST_get(Key key) {
    return st[h(key)];
}

// Is there a value paired with key?
bool ST_contains(Key key)
{ return ST_get(key) != NULL_Value; }

// Remove key (and its value) from table.
void ST_delete(Key key)
{ ST_put(key, NULL_Value); }

// Is the table empty?
bool ST_empty() {
    return ST_size() == 0;
}

// Number of key-value pairs in the table.
int ST_size() {
    int sz = 0;
    for (int i = 0; i < N; i++) {
        if (st[i] != NULL_Value) { sz++; }
    }
    return sz;
}

// Clean up the table memory.
void ST_finish() {
    free(st);
}

// Smallest key.
Key ST_min() {
    for (int i = 0; i < N; i++) {
        if (st[i] != NULL_Value) { return inv_h(i); }
    }
    return NULL_Key;
}

// Largest key.
Key ST_max() {
    for (int i = N-1; i >= 0; i--) {
        if (st[i] != NULL_Value) { return inv_h(i); }
    }
    return NULL_Key;
}

// Largest key less than or equal to key.
Key ST_floor(Key key) {
    for (int i = h(key); i >=0; i--) {
        if (st[i] != NULL_Value) { return inv_h(i); }
    }
    return NULL_Key;
}

// Smallest key greater than to equal to key.
Key ST_ceiling(Key key) {
    for (int i = 0; i < N; i++) {
        if (st[i] != NULL_Value) { return inv_h(i); }
    }
    return NULL_Key;
}

// Number of keys less than key.
int ST_rank(Key key) {
    int rk = 0;
    for (int i = h(key)-1; i >=0; i--) {
        if (st[i] != NULL_Value) { rk++; }
    }
    return rk;
}

// Delete smallest key.
void ST_delmin() {
    ST_delete(ST_min());
}

// Delete largest key.
void ST_delmax() {
    ST_delete(ST_max());
}

// Visit all the key-value pairs in the order of their keys.
void ST_traverse(void (*visit)(Key,Value)) {
    ST_traverse_interval('A', 'Z', visit);
}

// Visit keys between lo and hi, in sorted order.
void ST_traverse_interval(Key lo, Key hi, void (*visit)(Key,Value)) {
    for (int i = h(lo); i <= h(hi); i++) {
        if (st[i] != NULL_Value) {
            visit(inv_h(i), st[i]);
        }
    }
}
