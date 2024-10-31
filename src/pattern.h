
#ifndef PATTERN_H
#define PATTERN_H

#include "color.h"
#include "vecmath.h"

typedef struct 
{
    Color c1;
    Color c2;
} StripePattern;

typedef enum {NONE=0, STRIPES=1} PatternType;

typedef struct
{
    PatternType type;
    Color c1;
    Color c2;
} Pattern;

void pattern_CreateStripePattern(Pattern* pattern, Color* color1, Color* color2);
void pattern_StripeAt(Pattern* pattern, Tuple4d* point, Color* result);
#endif // PATTERN_H
