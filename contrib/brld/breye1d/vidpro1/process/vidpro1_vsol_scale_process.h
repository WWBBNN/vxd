// This is bmvgd/vpgld/algo/pro/vidpro1_vsol_scale_process.h
#ifndef vidpro1_vsol_scale_process_h_
#define vidpro1_vsol_scale_process_h_

//:
// \file
// \brief A process that scales vsol objects
// \author Based on original code by Matt Leotta
// \date 8/26/05
//
// \verbatim
//  Modifications
// \endverbatim


#include <vcl_vector.h>
#include <vcl_string.h>
#include <bpro1/bpro1_process.h>

#include <bpro1/bpro1_parameters.h>


class vidpro1_vsol_scale_process : public bpro1_process
{
public:

  vidpro1_vsol_scale_process();
  ~vidpro1_vsol_scale_process(){}

  //: Clone the process
  virtual bpro1_process* clone() const;
  
  vcl_string name();

  int input_frames();
  int output_frames();
  
  vcl_vector< vcl_string > get_input_type();
  vcl_vector< vcl_string > get_output_type();

  bool execute();
  bool finish();


};

#endif // vidpro1_vsol_scale_process_h_
