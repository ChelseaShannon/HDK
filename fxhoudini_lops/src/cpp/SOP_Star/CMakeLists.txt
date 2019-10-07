set( library_name SOP_Star )
project( HDK_Project )

add_library( ${library_name} SHARED
    SOP_Star.C
    SOP_Star.h
)


list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )

# Code generation for the embedded DS file in SOP_Star.C.
houdini_generate_proto_headers( FILES SOP_Star.C )

houdini_configure_target( ${library_name} INSTDIR ${CMAKE_INSTALL_PREFIX}/houdini/dso)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)