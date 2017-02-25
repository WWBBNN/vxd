// This is bbasd/bgld/algo/bild_gradient_color.h

#ifndef bild_gradient_color_h_
#define bild_gradient_color_h_

//:
// \file
// \brief Circular arc - a curve segment with constant curvature, 
// internally represented by two end points and a signed curvature
// 
// \author Based on original code by  Nhon Trinh ( @lems.brown.edu)
// \date 08/17/2005
//
// \verbatim
//  Modifications:
//       Nhon Trinh   08/17/2005    Initial version
// \endverbatim


//#include <vcl_iostream.h>
//#include <vcl_cmath.h>
//#include <vgl/vgl_point_2d.h>


#include <vil/vil_image_view.h>

//: Compute the gradient of a color image by taking the strongest component among three planes
bool bild_gradient_rgb_Linf(const vil_image_view<double >& src, 
                          vil_image_view<double >& Gx,
                          vil_image_view<double >& Gy);


#endif // bbasd/bgld/algo/bild_gradient_color.h

