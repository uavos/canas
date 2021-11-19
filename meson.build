project('canas', 'cpp',
    version: '2.2.0',
    default_options: ['cpp_std=c++17',
                      'warning_level=2'])

sources = ['src/cansocket.cpp',
           'src/core.cpp',
           'src/crc16ibm.cpp',
           'src/errors.cpp',
           'src/serdes.cpp',
           'src/utils.cpp']

defines = []
if host_machine.endian() == 'big'
    defines += '-DCANAS_BIG_ENDIAN'
else
    defines += '-DCANAS_LITTLE_ENDIAN'
endif

canas_raw_dep = declare_dependency(compile_args: defines,
                                   sources: sources,
                                   include_directories: include_directories('include'))
canas_lib = static_library('canas',
                            dependencies: canas_raw_dep)
canas_dep = declare_dependency(compile_args: defines,
                               link_with: canas_lib,
                               include_directories: include_directories('include'))

subdir('tests')
