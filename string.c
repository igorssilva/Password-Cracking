#include "string.h"

struct string
{
    char *c;
    int len;
};

int compare_from(String *s, String *t, int d)
{
    int min = s->len < t->len ? s->len : t->len;
    for (int i = d; i < min; i++)
    {
        if (s->c[i] < t->c[i])
        {
            return -1;
        }
        if (s->c[i] > t->c[i])
        {
            return 1;
        }
    }
    return s->len - t->len;
}

int compare(String *s, String *t)
{
    return compare_from(s, t, 0);
}
