// This is brl/vidpro1/process/vidpro1_grey_image_process.h
#ifndef vidpro1_grey_image_process_h_
#define vidpro1_grey_image_process_h_

//:
// \file
// \brief Process that converts an image into grey-scale
// \author Based on original code by Matt Leotta
// \date 12/16/03
//
// \verbatim
//  Modifications
// \endverbatim

#include <vcl_vector.h>
#include <vcl_string.h>
#include <bpro1d/bpro1d_process.h>

class vidpro1_grey_image_process : public bpro1d_process {

public:

  vidpro1_grey_image_process();
  virtual ~vidpro1_grey_image_process();

  //: Clone the process
  virtual bpro1d_process* clone() const;

  vcl_string name();

  vcl_vector< vcl_string > get_input_type();
  vcl_vector< vcl_string > get_output_type();

  int input_frames();
  int output_frames();

  bool execute();
  bool finish();
  
protected:

private:

};

#endif // vidpro1_grey_image_process_h_
