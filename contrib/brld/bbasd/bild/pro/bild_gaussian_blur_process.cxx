// This is basic/bild/pro/bild_gaussian_blur_process.cxx

//:
// \file

#include "bild_gaussian_blur_process.h"

#include <bprod/bprod_parameters.h>
#include <bprod/bprod_storage.h>

#include <vil/vil_image_view.h>
#include <vil/vil_image_resource.h>
#include <vil/vil_new.h>
#include <vil/algo/vil_gauss_filter.h>


//: Return the default set of parameters for the process
bprod_parameters_sptr
bild_gaussian_blur_process::factory::default_params() const
{
  bprod_parameters_sptr p = new bprod_parameters();
  if(p->add("Gaussian Blur Sigma" , "sigma" , 1.0f ))
    return p;

  vcl_cerr << "ERROR: Adding parameters in " __FILE__ << vcl_endl;
  return NULL;
}


//: Construct a process from a set of parameters
bprod_process_sptr
bild_gaussian_blur_process::factory::create(const bprod_parameters_sptr& params) const
{
  float sigma=0;
  if( !params->get_value( "sigma" , sigma ) ){
    return NULL;
  }

  return new bild_gaussian_blur_process(sigma);
}


//: Run the process on the current frame
bprod_signal
bild_gaussian_blur_process::execute()
{
  assert(input_type_id(0) == typeid(vil_image_resource_sptr));
  vil_image_resource_sptr in_img = input<vil_image_resource_sptr>(0);

  vil_image_view< vxl_byte > image_view = in_img->get_view();

  vil_image_resource_sptr out_img = vil_new_image_resource( in_img->ni() ,
                                                            in_img->nj() ,
                                                            in_img->nplanes() ,
                                                            in_img->pixel_format() );

  vil_image_view< vxl_byte > output_view = out_img->get_view();

  vil_gauss_filter_5tap_params params( sigma_ );
  vil_gauss_filter_5tap( image_view , output_view , params );


  output(0,out_img);

  return BPROD_VALID;
}




