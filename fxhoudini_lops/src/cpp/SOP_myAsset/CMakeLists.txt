set( library_name SOP_myAsset )
project( HDK_Project )

add_library( ${library_name} SHARED
    SOP_myAsset.C
    SOP_myAsset.h
)


list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )

houdini_configure_target( ${library_name} INSTDIR ${CMAKE_INSTALL_PREFIX}/houdini/dso)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)