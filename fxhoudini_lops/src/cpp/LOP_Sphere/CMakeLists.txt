set( library_name LOP_Sphere )
project( HDK_Project )

# Add a library and its source files.
add_library( ${library_name} SHARED
LOP_Sphere.C
LOP_Sphere.h
)

houdini_configure_target( ${library_name} INSTDIR ${CMAKE_INSTALL_PREFIX}/houdini/dso)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)
