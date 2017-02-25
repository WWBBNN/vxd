// This is brcv/mvg/becld/becld_episeg.h
#ifndef becld_episeg_h_
#define becld_episeg_h_
//:
// \file
// \brief A segment of a 2D curve with added epipolar parameterization
// \author Based on original code by  Matt Leotta, (@lems.brown.edu)
// \date 7/13/04
//
// \verbatim
//  Modifications
//  2004-07-16  Dave Pacheco  Added curve pointer, methods.
// \endverbatim

#include <vbl/vbl_ref_count.h>
#include <vgl/vgl_point_2d.h>
#include <vsol/vsol_digital_curve_2d_sptr.h>
#include "becld_epipole.h"
#include "becld_epipole_sptr.h"
#include "becld_episeg_sptr.h"


//: A segment of a 2D curve with added epipolar parameterization
// Each segment points to a section of a 2D curve such that the
// epipolar parameterization is monotonic in epipolar angle
// over that section.  Each segment is also a link in a doubly-linked
// list covering the underlying curve.
class becld_episeg : public vbl_ref_count
{
 public:
  friend class becld_episeg_from_curve_converter;

  //: Constructor
  becld_episeg();
  becld_episeg(const becld_epipole_sptr& epipole,
              const vsol_digital_curve_2d_sptr& curve,
              double min_index,
              double max_index);
  //: Destructor
  ~becld_episeg();

  //: Return the epipolar distance at the given angle 
  double dist(double angle) const;
  //: Return the index into the underlying curve at angle
  double index(double angle) const;
  //: Return the point at \p angle
  vgl_point_2d<double> point(double angle) const;

  //: Return the angle for the point at the given index
  double angle(double index) const;
  
  //: Return the epipole
  becld_epipole_sptr epipole() const { return epipole_; }
  //: Get the curve
  vsol_digital_curve_2d_sptr curve() const { return curve_; }
  //: Lower angle bound
  double min_angle() const;
  //: Upper angle bound
  double max_angle() const;
  //: Lower distance bound
  double min_dist() const;
  //: Upper distance bound
  double max_dist() const;
  //: Lower index bound (of the underlying curve)
  double min_index() const;
  //: Upper index bound
  double max_index() const;

  //: Return a smart pointer to the next episeg along the curve
  becld_episeg_sptr next() const { return next_seg_; }
  //: Return a smart pointer to the previous episeg along the curve
  becld_episeg_sptr prev() const { return prev_seg_; }

 private:
  //: Indicates that angle increases with curve index
  bool dir_positive_;
  //: The epipole 
  becld_epipole_sptr epipole_;
  //: Pointer to the curve
  vsol_digital_curve_2d_sptr curve_;
  //: Pointer to the next segment in the linked list
  becld_episeg* next_seg_;
  //: Pointer to the previous segment in the linked list
  becld_episeg* prev_seg_;
  //: Lower distance bound
  double min_dist_;
  //: Upper distance bound
  double max_dist_;
  //: Lower index bound (of the underlying curve)
  double min_index_;
  //: Upper index bound
  double max_index_;

  //: Compute upper/lower bounds
  void compute_bounds();
  //: Binary search to find the index
  int index_search(double angle, int lower, int upper) const;
};

#endif // becld_episeg_h_
