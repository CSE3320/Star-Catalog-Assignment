#ifndef __STAR_H__
#define __STAR_H__


struct Star
{
  char * Name;
  double RightAscension;
  double Declination;
  double Azimuth;
  double Altitude;

};

void init( struct Star * star, char * name, 
           double raHours, double raMinutes, double raSeconds, 
           double dmsHours, double dmsMinutes, double dmsSeconds );

#endif
