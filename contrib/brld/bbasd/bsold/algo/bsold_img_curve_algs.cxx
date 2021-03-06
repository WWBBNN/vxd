// This is bbasd/bsold/bsold_img_curve_algs.cxx

#include "bsold_img_curve_algs.h"
#include <bsold/algo/bsold_curve_algs.h>

#include <vnl/vnl_math.h>
#include <vnl/vnl_vector_fixed.h>
#include <vil/vil_bilin_interp.h>
#include <bil/algo/bil_color_conversions.h>
#include <vcl_cmath.h>

double get_color_distance_of_curve_regions(bsold_interp_curve_2d_sptr curve, float region_width, 
                                            vil_image_view<float>& L, 
                                            vil_image_view<float>& A, 
                                            vil_image_view<float>& B, 
                                            double color_gamma)
{
  vcl_vector<vsol_point_2d_sptr > region_pts;                                                     
  // get points on either side of the curve                                                      // do not use the points right on the curve
                                                                                                 // when this parameter is false, the plus and minus region pts are reliably all the newly added ones
  bsold_curve_algs::sample_region_along_curve(*curve, region_pts, 0.3f, curve->length(), region_width, false);
  //create two histograms using bilinearly interpolated image values
  vnl_vector_fixed<double, 3> plus_mean((double)0.0f), minus_mean((double)0.0f);

  for(unsigned i = 0; i < region_pts.size()/2; ++i)
  {
    vnl_vector_fixed<double, 3> v;
    v[0] = vil_bilin_interp_safe(L, region_pts[i]->x(), region_pts[i]->y());
    v[1] = vil_bilin_interp_safe(A, region_pts[i]->x(), region_pts[i]->y());
    v[2] = vil_bilin_interp_safe(B, region_pts[i]->x(), region_pts[i]->y());
    plus_mean += v;
    
  }
  for(unsigned i = region_pts.size()/2; i < region_pts.size(); ++i)
  {
    vnl_vector_fixed<double, 3> v;
    v[0] = vil_bilin_interp_safe(L, region_pts[i]->x(), region_pts[i]->y());
    v[1] = vil_bilin_interp_safe(A, region_pts[i]->x(), region_pts[i]->y());
    v[2] = vil_bilin_interp_safe(B, region_pts[i]->x(), region_pts[i]->y());
    minus_mean += v;
  }
  plus_mean /= region_pts.size()/2;
  minus_mean /= region_pts.size()/2;

  return distance_LAB(plus_mean, minus_mean, color_gamma);
  

}

//function that gives the intensity difference around a curve
double get_intensity_distance_of_curve_regions(bsold_interp_curve_2d_sptr curve, float region_width, 
                                               vil_image_view<vxl_byte>& img, double intensity_gamma)                                               
{
  vcl_vector<vsol_point_2d_sptr > region_pts;     

  // get points on either side of the curve                                                      // do not use the points right on the curve
                                                                                                 // when this parameter is false, the plus and minus region pts are reliably all the newly added ones
  bsold_curve_algs::sample_region_along_curve(*curve, region_pts, 0.3f, curve->length(), region_width, false);
  //create two histograms using bilinearly interpolated image values
  double plus_mean = 0.0, minus_mean = 0.0;

  for(unsigned i = 0; i < region_pts.size()/2; i++)
  {
    double v = vil_bilin_interp_safe(img, region_pts[i]->x(), region_pts[i]->y());
    plus_mean += v;
  }

  for(unsigned i = region_pts.size()/2; i < region_pts.size(); i++)
  {
    double v = vil_bilin_interp_safe(img, region_pts[i]->x(), region_pts[i]->y());
    minus_mean += v;
  }

  plus_mean /= region_pts.size()/2;
  minus_mean /= region_pts.size()/2;

  return distance_intensity(plus_mean, minus_mean, intensity_gamma);
}



