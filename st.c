#include "st.h"
#include <stdlib.h>
#include <stdio.h>



bool ST_contains(Key key)
{
    return ST_get(key) != NULL_Value;
}
