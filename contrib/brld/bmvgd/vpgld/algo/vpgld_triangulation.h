// This is dvpgl_triangulation.h
#ifndef dvpgl_triangulation_h
#define dvpgl_triangulation_h
//:
//\file
//\brief Algorithms for multiview triangulation
//
// Other triangulation algorithms should go in here, such as triangulate_3d_point in
// vpgl_proj_camera, and this file should become vpgl_triangulation in vpgl.
//
//\author Ricardo Fabbri (rfabbri), Brown University  (rfabbri.github.io)
//\date 04/16/2009 04:52:51 AM EDT
//

#include <vgl/vgl_fwd.h>
#include <vpgl/vpgl_proj_camera.h>


// Optimal 2-view triangulation by Kanatani and students, BMVC08. The difference to the conventional
// svd approach is more significant for cameras in projective reconstructions, as well as in cases
// where one camera is closer to the 3D point than the other.

vgl_point_3d<double>
triangulate_3d_point_optimal_kanatani_fast(
    const vgl_point_2d<double> &pt_img0,
    const vgl_point_2d<double> &pt_img1,
    const vpgl_proj_camera<double> &cam0,
    const vpgl_proj_camera<double> &cam1);

// This one gives exaclty the same result as the _fast version above in our experiments, but is much
// slower
vgl_point_3d<double>
triangulate_3d_point_optimal_kanatani(
    const vgl_point_2d<double> &pt_img0,
    const vgl_point_2d<double> &pt_img1,
    const vpgl_proj_camera<double> &cam0,
    const vpgl_proj_camera<double> &cam1);


#endif // dvpgl_triangulation_h
