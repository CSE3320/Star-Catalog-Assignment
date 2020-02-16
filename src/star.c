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
//

#include "star.h"
#include "utility.h"


void initStar( struct Star * Star,char * Name,
               double RAHours, double RAMinutes, double RASeconds, 
               double DMSHours, double DMSMinutes, double DMSSeconds )
{

};

void setStarPosition( struct Star * Star, double Latitude, double Longitude, struct tm Time ) 
{
   double JD       = J2000( JulianDate( Time ) );
   double LST      = getLocalSiderealTime( Longitude, JD );
   double HA       = getHourAngle( Star->RightAscension, LST );
   double Altitude = getAltitude( Latitude, Star->Declination, HA );
   double Azimuth  = getAzimuth( Latitude, Star->Declination, HA );
};

void printStarPosition( struct Star * Star )
{
   //printf("%s Azimuth: %f Altitude: %f\n", Star->Name, Star 
};

