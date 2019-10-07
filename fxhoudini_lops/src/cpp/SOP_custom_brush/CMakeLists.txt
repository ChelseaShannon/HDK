set( library_name SOP_custom_brush )
project( HDK_Project )

add_library( ${library_name} SHARED
MSS_CustomBrushState.C
MSS_CustomBrushState.h
MSS_CustomBrushState.ui
)

MESSAGE(STATUS  "Install path for dso ${CMAKE_INSTALL_PREFIX}/houdini/dso")
MESSAGE(STATUS  ${CMAKE_INSTALL_PREFIX}/houdini/dso)

houdini_configure_target( ${library_name} INSTDIR ${CMAKE_INSTALL_PREFIX}/houdini/dso)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)