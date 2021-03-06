# gel/vgel/CMakeLists.txt

## doxygen_add_library(contrib/gel/vgel
##   DEPENDS contrib/gel/vtol contrib/oxl/mvl
##   PACKAGE contrib/gel
##   DESCRIPTION "Kanade-Lucas_Tomasi feature tracker"
##   )

add_subdirectory(kl)

set(vgel_sources
 vgel_kl.cxx              vgel_kl.h
 vgel_kl_params.cxx       vgel_kl_params.h
)
aux_source_directory(Templates vgel_sources)

if(VXL_BUILD_OXL)
set(vgel_sources ${vgel_sources}
 vgel_multi_view_data.hxx vgel_multi_view_data.h
 vgel_multi_view_data_vertex_sptr.h
)
endif()

add_library(vgel ${vgel_sources})
#install_targets(/lib vgel)
#INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/gel/vgel ${vgel_sources})

include_directories(${VXL_OXL_INCLUDE_DIR})
target_link_libraries(vgel mvl)

target_link_libraries(vgel vgel_kl vtol vil vil1 vbl)

if( BUILD_TESTING )
  add_subdirectory(tests)
endif()

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif ()
