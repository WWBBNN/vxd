// This is basic/bild/pro/bild_monotone_process.h
#ifndef bild_monotone_process_h_
#define bild_monotone_process_h_

//:
// \file
// \brief Process that converts an image into monotone (grey-scale)
// \author Based on original code by  Matt Leotta (@lems.brown.edu)
// \date 12/21/04
//
// \verbatim
//  Modifications
// \endverbatim

#include <vcl_vector.h>
#include <vcl_string.h>
#include <dbpro/dbpro_process.h>
#include <dbpro/dbpro_process_factory.h>

//: Process that converts an image into monotone (grey-scale)
class bild_monotone_process : public dbpro_filter
{
public:
  //: Constructor
  bild_monotone_process(float rw, float gw, float bw)
   : rw_(rw), gw_(gw), bw_(bw) {}
  //: Destructor
  virtual ~bild_monotone_process() {}

  class factory : public dbpro_process_factory
  {
   public:
    //: Return the default set of parameters for the process
    virtual dbpro_parameters_sptr default_params() const;

    //: Construct a process from a set of parameters
    virtual dbpro_process_sptr create(const dbpro_parameters_sptr& params) const;

    //: The name of the process
    virtual vcl_string name() const { return "Convert to Monotone"; }

    virtual ~factory() {}
  };

  //: Execute this process
  dbpro_signal execute();

 private:
  //: The weights for combining color channels
  float rw_, gw_, bw_;
};

#endif // bild_monotone_process_h_
