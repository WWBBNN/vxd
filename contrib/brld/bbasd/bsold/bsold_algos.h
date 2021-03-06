// This is bsold/bsold_algos.h
#ifndef bsold_algos_h
#define bsold_algos_h

//:
// \file
// \brief Miscellaneous vsol algorithms
// This is essentially a namespace for static methods;
// there is no public constructor
//
// \author Based on original code by  Nhon Trinh (@lems.brown.edu)
// \date Oct 30, 2006
//
// \verbatim
//  Modifications 
// \endverbatim

#include <vcl_vector.h>
//#include <vsol/vsol_spatial_object_2d_sptr.h>
#include <vsol/vsol_point_2d_sptr.h>
//#include <vsol/vsol_polygon_2d_sptr.h>
#include <vsol/vsol_polyline_2d_sptr.h>
#include <vsol/vsol_polygon_2d_sptr.h>


class bsold_algos
{
public:
  ~bsold_algos(){};

  //: Break a polyline into two pieces, each is a polyline
  // Require: cut_position is a vertex on polyline
  static vcl_vector<vsol_polyline_2d_sptr > cut_polyline(
    const vsol_polyline_2d_sptr& polyline,
    const vsol_point_2d_sptr& cut_position);

  static vsol_polyline_2d_sptr polyline_from_polygon(
    const vsol_polygon_2d_sptr& polygon,
    const vsol_point_2d_sptr& cut_position = 0);

  static vsol_polygon_2d_sptr polygon_from_polyline(
    const vsol_polyline_2d_sptr& polyline);

  //: find the closest point on a polyline
  static vsol_point_2d_sptr closest_point(const vsol_point_2d_sptr& p,
    const vsol_polyline_2d_sptr& polyline,
    double & d);

private:
  bsold_algos(){}

};


#endif // bsold_algos_h
