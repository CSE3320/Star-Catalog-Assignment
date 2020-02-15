#include <time.h>
#include <math.h>
#include "../src/utility.h"
#include "../src/star.h"
#include "utest.h"

// approxf - Licensed under MIT License
// Copyright (c) 2017 Elliot Chance, Izyumov Konstantin and Christophe Kamphaus.
// https://github.com/elliotchance/c2go
#define INT64 52 - 4
#define INT32 23 - 4

static int approxf(double actual, double expected, int bits) 
{
    // We do not handle infinities or NaN.
    if (isinf(actual) || isinf(expected) || isnan(actual) || isnan(expected)) {
        return 0;
    }
    // If we expect zero (a common case) we have a fixed epsilon from actual. If
    // allowed to continue the epsilon calculated would be zero and we would be
    // doing an exact match which is what we want to avoid.
    if (expected == 0.0) {
        return fabs(actual) < (1 / pow(2, bits));
    }
    // The epsilon is calculated based on significant bits of the actual value.
    // The amount of bits used depends on the original size of the float (in
    // terms of bits) subtracting a few to allow for very slight rounding
    // errors.
    double epsilon = fabs(expected / pow(2, bits));
    // The numbers are considered equal if the absolute difference between them
    // is less than the relative epsilon.
    return fabs(actual - expected) <= epsilon;
}

UTEST( UtilityTests, deg2dms )
{
  int deg = 0;
  int min = 0;
  int sec = 0;

  deg2dms( 180.166944, &deg, &min, &sec );
  ASSERT_TRUE( deg == 180 );
  ASSERT_TRUE( min == 10 );
  ASSERT_TRUE( sec == 1 );
};

UTEST( UtilityTests, dms2deg )
{
  float result = dms2deg( 180, 10, 1 );

  ASSERT_TRUE( approxf( 180.166944, result, INT32 ) );
}

UTEST_MAIN();
