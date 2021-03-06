// This is bbasd/buld/buld_solar_position.h
#ifndef buld_solar_position_h_
#define buld_solar_position_h_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma interface
#endif
//:
// \file
// \brief  Compute position of the sun given time, date, and location
//
//  The equations used here are based on :
//
//   Carruthers D, Uloth C and Roy G. G., 1990, 
//     An Evaluation of Formulae for Solar Declination and the Equation of Time,
//     Research Report No RR17, School of Architecture,
//     the University of Western Australia, Jan.
//
//
// \author Based on original code by  Matt Leotta (Brown)
// \date   October 28, 2005
//
// \verbatim
//  Modifications
// \endverbatim
//

//:  Compute position of the sun given time, date, and location
// \param day day of the year [1, 366]
// \param utc_hour time of day in hours UTC (GMT)
// \param lat latitude in degrees
// \param lng longitude in degrees
// \retval alt altitude in radians from the horizon
// \retval az azimuth in radians from North
void buld_solar_position(int day, double utc_hour, 
                         double lat, double lng,
                         double& alt, double& az);



#endif // buld_solar_position_h_
