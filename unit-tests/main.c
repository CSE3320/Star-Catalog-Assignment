// MIT License
// 
// Copyright (c) 2020 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

UTEST( UtilityTests, angularDistance )
{
  double result = calculateAngularDistance( 8.70733, 1.484090, 9.94798, 2.447672 );
  ASSERT_TRUE( approxf( result, 1.570304, INT32 ) );
}

UTEST_MAIN();
