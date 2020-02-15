#include <time.h>
#include <math.h>
#include "utility.h"
#include "star.h"

int main()
{
  time_t rawtime;
  struct tm * timeinfo;

  setenv("TZ", "CST6CDT", 1);
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  printf("%f\n", JulianDate( *timeinfo ) );
  printf("%f\n", J2000(JulianDate( *timeinfo ) ) );
  printf("%f\n", LST( -97.6, J2000( JulianDate( *timeinfo ) ) ) );
  printf("%f\n", dms2deg( 180, 10, 1 ) );

  int d, m, s;

  deg2dms( 180.166944, &d, &m, &s );

  printf("%d %d %d \n", d,m,s );
}

