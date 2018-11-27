#ifndef ST_H
#define ST_H

#include <stdbool.h>
#include "item.h"

// Create an empty symbol table.
void ST_init(int maxN);

// Put key-value pair into the table: a[key] = val; .
void ST_put(Key key, Value val);

// Value paired with key: a[key] .
Value ST_get(Key key);

// Is there a value paired with key?
bool ST_contains(Key key);

// Remove key (and its value) from table.
void ST_delete(Key key);

// Is the table empty?
bool ST_empty();

// Number of key-value pairs in the table.
int ST_size();

// Clean up the table memory.
void ST_finish();

// Smallest key.
Key ST_min();

// Largest key.
Key ST_max();

// Largest key less than or equal to key.
Key ST_floor(Key key);

// Smallest key greater than to equal to key.
Key ST_ceiling(Key key);

// Number of keys less than key.
int ST_rank(Key key);

// Delete smallest key.
void ST_delmin();

// Delete largest key.
void ST_delmax();

// Visit all the key-value pairs in the order of their keys.
void ST_traverse(void (*visit)(Key,Value));

// Visit keys between lo and hi, in sorted order.
void ST_traverse_interval(Key lo, Key hi, void (*visit)(Key,Value));

#endif
