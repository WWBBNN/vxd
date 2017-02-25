// This is brl/vidpro1/process/vidpro1_frame_diff_process.cxx

//:
// \file

#include "vidpro1_frame_diff_process.h"
#include <vidpro1/storage/vidpro1_image_storage.h>
#include <vidpro1/storage/vidpro1_image_storage_sptr.h>
#include <vil/vil_image_resource.h>
#include <vil/vil_new.h>
#include <vil/vil_image_view.h>
#include <vil/vil_convert.h>
#include <vil/vil_math.h>


//: Constructor
vidpro1_frame_diff_process::vidpro1_frame_diff_process()
{
}


//: Destructor
vidpro1_frame_diff_process::~vidpro1_frame_diff_process()
{
}


//: Clone the process
bpro1d_process* 
vidpro1_frame_diff_process::clone() const
{
  return new vidpro1_frame_diff_process(*this);
}


//: Return the name of this process
vcl_string
vidpro1_frame_diff_process::name()
{
  return "Frame Difference";
}


//: Return the number of input frame for this process
int
vidpro1_frame_diff_process::input_frames()
{
  return 2;
}


//: Return the number of output frames for this process
int
vidpro1_frame_diff_process::output_frames()
{
  return 1;
}


//: Provide a vector of required input types
vcl_vector< vcl_string > vidpro1_frame_diff_process::get_input_type()
{
  vcl_vector< vcl_string > to_return;
  to_return.push_back( "image" );
  return to_return;
}


//: Provide a vector of output types
vcl_vector< vcl_string > vidpro1_frame_diff_process::get_output_type()
{  
  vcl_vector<vcl_string > to_return;
  to_return.push_back( "image" );
  return to_return;
}


//: Execute the process
bool
vidpro1_frame_diff_process::execute()
{
  if ( input_data_.size() != 2 ){
    vcl_cout << "In vidpro1_frame_diff_process::execute() - "
             << "not exactly two input images \n";
    return false;
  }
  clear_output();

  // get image from the storage class
  vidpro1_image_storage_sptr frame_image1, frame_image2;
  frame_image1.vertical_cast(input_data_[1][0]);
  frame_image2.vertical_cast(input_data_[0][0]);

  vil_image_resource_sptr image1_sptr = frame_image1->get_image();
  vil_image_resource_sptr image2_sptr = frame_image2->get_image();

  vil_image_view<vxl_byte> image1, image2, grey_img1, grey_img2;
  image1 = image1_sptr->get_view();
  image2 = image2_sptr->get_view();

  // Convert to greyscale images if needed
  if( image1.nplanes() == 3 ) {
    vil_convert_planes_to_grey( image1 , grey_img1 );
  }
  else if ( image1.nplanes() == 1 ) {
    grey_img1 = image1;
  } else {
    vcl_cerr << "Returning false. image1.nplanes(): " << image1.nplanes() << vcl_endl;
    return false;
  }

  if( image2.nplanes() == 3 ) {
    vil_convert_planes_to_grey( image2 , grey_img2 );
  }
  else if ( image2.nplanes() == 1 ) {
    grey_img2 = image2;
  } else {
    vcl_cerr << "Returning false. image2.nplanes(): " << image2.nplanes() << vcl_endl;
    return false;
  }

  vil_image_view<vxl_byte> diff_img;
  vil_math_image_abs_difference(grey_img2, grey_img1, diff_img);

  // create the output storage class
  vidpro1_image_storage_sptr output_storage = vidpro1_image_storage_new();
  output_storage->set_image(vil_new_image_resource_of_view(diff_img));

  output_data_[0].push_back(output_storage);
  return true;  
}
    


bool
vidpro1_frame_diff_process::finish()
{
  return true;
}




