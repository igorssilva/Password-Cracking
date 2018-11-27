#ifndef STRING_H
#define STRING_H
typedef struct string String;
typedef String *Item;

#define less(A, B) (compare(A, B) < 0)
#define less_from(A, B, d) (compare_from(A, B, d) < 0)
#define exch(A, B)  \
    {               \
        Item t = A; \
        A = B;      \
        B = t;      \
    }

int compare_from(String *s, String *t, int d);
int compare(String *s, String *t);

#endif