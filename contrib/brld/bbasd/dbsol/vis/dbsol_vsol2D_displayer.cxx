// This is basic/dbsol/vis/dbsol_vsol2D_displayer.cxx

#include "dbsol_vsol2D_displayer.h"
#include <bvis1/bvis1_displayer.h>
#include <bvis1/bvis1_mapper.h>
#include <vidpro1/storage/vidpro1_vsol2D_storage.h>
#include <dbsol/vis/dbsol2D_tableau.h>
#include <vgui/vgui_style.h>

//: Create a tableau if the storage object is of type vsol2D
vgui_tableau_sptr
dbsol_vsol2D_displayer::make_tableau( bpro1_storage_sptr storage) const
{
  // Return a NULL tableau if the types don't match
  if( storage->type() != this->type() )
    return NULL;

  // Cast the storage object into an vsol2D storage object
  vidpro1_vsol2D_storage_sptr vsol2D_storage;
  vsol2D_storage.vertical_cast(storage);
  // Create a new dbsol2D tableau
  dbsol2D_tableau_sptr vsol2D_tab;
  vsol2D_tab = dbsol2D_tableau_new();
  vcl_vector< vcl_string > names = vsol2D_storage->groups();
  //the old way without attributes
  if(!vsol2D_storage->attributes_defined()||!mapper_)
    {
      vcl_vector<vgui_style_sptr> style_vector;
      style_vector.push_back(vgui_style::new_style(1,0,0, 3.0, 3.0));
      style_vector.push_back(vgui_style::new_style(0,1,0, 3.0, 3.0));
      style_vector.push_back(vgui_style::new_style(0,0,1, 3.0, 3.0));
      for(unsigned int i=0; i < names.size(); ++i ) 
      {
        vsol2D_tab->set_current_grouping( names[i] );
        vsol2D_tab->add_spatial_objects(vsol2D_storage->data_named( names[i] ),
                                        style_vector[i%3] );
      }
    }
  else
    //the new way with attributes
    for(unsigned int i=0; i < names.size(); ++i ) 
      {
        vsol2D_tab->set_current_grouping( names[i] );

        vcl_vector<double> attrs = vsol2D_storage->attributes_named( names[i]);

        vcl_vector<vsol_spatial_object_2d_sptr> data = 
          vsol2D_storage->data_named( names[i]);

        vcl_vector<double>::iterator ait = attrs.begin();
        vcl_vector<vsol_spatial_object_2d_sptr>::iterator sit=data.begin();
        for(;(sit != data.end()&&ait!=attrs.end());++sit, ++ait)
          vsol2D_tab->add_spatial_object(*sit, mapper_->style(*ait));
      }
  vsol2D_tab->set_current_grouping( "default" );
  return vsol2D_tab;
}
  
