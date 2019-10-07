cmake_minimum_required( VERSION 3.14 )
project( fxhoudini_lops )

MESSAGE(STATUS "TESTING")


include(RezBuild)
rez_find_packages(PREFIX pkgs)
list( APPEND CMAKE_PREFIX_PATH "/film/tools/packages/houdiniDevKit/17.5.252/houdini/toolkit/cmake")

# find_package(Houdini REQUIRED)
# set(Houdini_DIR /film/tools/packages/houdiniDevKit/17.5.252/houdini/toolkit/cmake)
find_package( Houdini REQUIRED )


set(fxhoudini_lops_build_root ${CMAKE_SOURCE_DIR}/houdini)
MESSAGE(STATUS "fxhoudini_lops_build_root: " ${fxhoudini_lops_build_root})
MESSAGE(STATUS "fxhoudini_lops_build_root: " ${fxhoudini_lops_build_root})


add_subdirectory( ${CMAKE_SOURCE_DIR}/src/cpp/LOP_Sphere)
add_subdirectory( ${CMAKE_SOURCE_DIR}/src/cpp/SOP_custom_brush)
add_subdirectory( ${CMAKE_SOURCE_DIR}/src/cpp/SOP_Star)
add_subdirectory( ${CMAKE_SOURCE_DIR}/src/cpp/SOP_myAsset)

file(GLOB_RECURSE py_files "src/python/*.py")
rez_install_python(
    py
    FILES ${py_files}
    DESTINATION .
)

file(GLOB icon_files "houdini/config/Icons/*.svg")
rez_install_files(
    ${icon_files}
    DESTINATION .
    EXECUTABLE
)
