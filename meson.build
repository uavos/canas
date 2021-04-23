project('canas', 'cpp',
    version: '2.1.3',
    default_options: ['cpp_std=c++17',
                      'warning_level=2'])

sources = ['src/crc16ibm.cpp',
           'src/errors.cpp',
           'src/serdes.cpp']
canas_lib = static_library('canas',
                            sources,
                            include_directories: include_directories('include'))
canas_dep = declare_dependency(link_with: canas_lib,
                               include_directories: include_directories('include'))
canas_raw_dep = declare_dependency(sources: sources,
                                   include_directories: include_directories('include'))

subdir('tests')
