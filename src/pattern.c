
#include "pattern.h"
#include <math.h>

void pattern_CreateStripePattern(Pattern* pattern, Color* col1, Color* col2)
{
    pattern->type = STRIPES;
    pattern->c1 = *col1;
    pattern->c2 = *col2;
}

void pattern_StripeAt(Pattern* pattern, Tuple4d* point, Color* result)
{
    double x = floor((double)(*point)[0]);
    if (((int)x) % 2 == 0) 
    {
        *result = pattern->c1;
    }
    else
    {
        *result = pattern->c2;
    }
}