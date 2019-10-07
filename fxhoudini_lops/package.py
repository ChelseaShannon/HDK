name = "fxhoudini_lops"

version = "1.0.2"

authors = ["Chelsea"]

private_build_requires = [
    "gcc-6.3.1",
    'glimpse_oiio-1.65+',
    'houdini'
]

build_requires = [
    "AL_CMakeLib-2.0+<3",
    "AL_CMakeLibHoudini-1.0+<2",
    "cmake-2.8+",
    "python-2.7"
]

requires = [
    "glew-2.0+",
    "AL_USDGlimpseSchemas-0.11",
    'AL_boost-1.66.0',
    "Qt_vfx-5.6.1",
    'glimpse-3.24+',
    'ALQt-8.5+',
    'ALSimpleTypes-1.0+',
    'ALPropertyLayout-1.2+'
]


# def commands():
#     env.HOUDINI_PATH.append("{root}/houdini")
#     env.PYTHONPATH.append("{root}/src/python/fxhoudini_lops")



def commands():
    env.PYTHONPATH.append("{root}/src/python/t28houdini_lops")
    # append to HOUDINI_PATH
    houdini_path_str = (
        "{root}/houdini:"
        "$REZ_HOUDINIDEVKIT_BASE/houdini/bin:"
        "$REZ_HOUDINIDEVKIT_BASE/houdini/houdini:")
    env.HOUDINI_PATH.append(houdini_path_str)
