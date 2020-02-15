#ifndef __UTILITY_H__
#define __UTILITY_H__


#include <time.h>
#include <math.h>

double hms2deg( double Hours, double Minutes, double Seconds ); 

double dms2deg(double Degrees, double Minutes, double Seconds );

void   deg2dms( double DecimalDegrees, int *Degrees, int *Minutes, int *Seconds );

double JulianDate( struct tm tm_val );

double J2000( double JD );

double LST( double lon, double J2000 );

double HourAngle( double RightAscension, double LocalSideRealTime );

double getAltitude( double Latitude, double Declination, double HourAngle );

double getAzimuth( double Latitude, double Declination, double HourAngle );

#endif
