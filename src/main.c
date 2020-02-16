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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include "utility.h"
#include "star.h"

#define NUM_STARS 119614

struct Star star_array[ NUM_STARS ];

const int MAX_FILE_NAME_SIZE = 255;

void showHelp()
{
  printf("Use: StarCatalog [options]\n");
  printf("Where options are:\n");
  printf("-o <file>   Set output file. (default=output.csv)\n");
  printf("-mon        Set the month. 1 .. 12\n");
  printf("-day        Set the day. 1 .. 31\n");
  printf("-year       Set the year. 1900 .. \n");
  printf("-hour       Set the hour. 1..24\n");
  printf("-min        Set the minute. 1..60\n");
  printf("-lon        Set the longitude\n");
  printf("-lat        Set the latitude\n");
  printf("-h          Show this help\n");
  printf("\nFor example:\n");
  printf("./bin/StarCatalog -mon 2 -day 17 -year 2020 -hour 21 -min 30 -lon -97.5 -o 2020Feb17.csv\n");
}


int main( int argc, char * argv[] )
{
  FILE *fp;
  size_t star_count = 0;

  int hourFound  = 0;
  int minFound   = 0;
  int dayFound   = 0;
  int monthFound = 0;
  int yearFound  = 0;
  int lonFound   = 0;
  int latFound   = 0;

  int hour    = 0;
  int min     = 0;
  int day     = 0;
  int month   = 0;
  int year    = 0;
  double lon  = 0;
  double lat  = 0;

  char * outputFile = NULL;

  int n;

  for( n = 1; n < argc; n++ )          
  {
    if( strcmp(argv[n], "-help" ) == 0 )
    {
      showHelp();
      exit(0);
    }
    if( strcmp(argv[n], "-mon" ) == 0 )
    {
      monthFound = 1;
      month = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-day" ) == 0 )
    {
      dayFound = 1;
      day = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-year" ) == 0 )
    {
      yearFound = 1;
      year = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-hour" ) == 0 )
    {
      hourFound = 1;
      hour = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-min" ) == 0 )
    {
      minFound = 1;
      min = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-lon" ) == 0 )
    {
      lonFound = 1;
      lon = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-lat" ) == 0 )
    {
      latFound = 1;
      lat = atoi( argv[n+1] );
    }
    if( strcmp(argv[n], "-o" ) == 0 )
    {
      outputFile = ( char * ) malloc( MAX_FILE_NAME_SIZE );
      memset( outputFile, 0, MAX_FILE_NAME_SIZE );
      strncpy( outputFile, argv[n+1], strlen( argv[n+1] ) );
    }
  }

  if( !hourFound )   
  {
     printf("You must provide the hour with -hour\n");
     showHelp();
     exit(0);
  }

  if( !minFound )   
  {
     printf("You must provide the minute with -min\n");
     showHelp();
     exit(0);
  }

  if( !dayFound )   
  {
     printf("You must provide the day with -day\n");
     showHelp();
     exit(0);
  }

  if( !monthFound )   
  {
     printf("You must provide the month with -mon\n");
     showHelp();
     exit(0);
  }

  if( !yearFound )   
  {
     printf("You must provide the year with -year\n");
     showHelp();
     exit(0);
  }

  if( !lonFound )   
  {
     printf("You must provide the longitude with -lon\n");
     showHelp();
     exit(0);
  }

  if( !latFound )   
  {
     printf("You must provide the latitude with -lat\n");
     showHelp();
     exit(0);
  }

  fp = fopen("../data/hipparcos.csv", "r");

  if (fp == NULL) {
    fprintf(stderr, "Error reading file\n");
    return 1;
  }

  while (fscanf(fp, "%d,%lf,%lf,%lf,%lf", &star_array[star_count].Name, 
                                          &star_array[star_count].RightAscension,
                                          &star_array[star_count].Declination,
                                          &star_array[star_count].Magnitude,
                                          &star_array[star_count].AbsoluteMagnitude) == 5 ) 
  {
    star_count++;
  }


  fclose(fp);

  assert( star_count == NUM_STARS );

  struct tm tm_val;
  tm_val.tm_hour = hour - 1;
  tm_val.tm_min  = min - 1;
  tm_val.tm_sec  = 0;

  struct tm timeinfo = {};
  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon  = month - 1;
  timeinfo.tm_mday = day;

  mktime(&timeinfo);
  tm_val.tm_yday   = timeinfo.tm_yday;
  
  double LST = getLocalSiderealTime( lon, J2000( JulianDate( tm_val ) ) );

  for( n = 0; n < NUM_STARS; n++ )
  {
    double HourAngle = getHourAngle( star_array[n].RightAscension, LST );
    star_array[n].Altitude = getAltitude( lat, star_array[n].Declination, HourAngle );
    star_array[n].Azimuth  = getAzimuth ( lat, star_array[n].Declination, HourAngle );
  }

}

