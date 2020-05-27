project('canas', 'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++17'])

canas_lib = static_library('canas',
                           'src/canas.cpp',
                           'src/slip.cpp',
                           'src/errors.cpp',
                            include_directories: include_directories('include'))
canas_dep = declare_dependency(link_with: canas_lib,
                               include_directories: include_directories('include'))

subdir('tests')
