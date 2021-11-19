if(not meson.is_cross_build())
    catch_dep = subproject('catch2').get_variable('catch2_dep')
    sources = ['main.cpp',
               'circularbuffer_test.cpp',
               'crc16ibm_test.cpp',
               'serdes_serial_test.cpp',
               'slip_test.cpp',
               'utils_test.cpp']
    if host_machine.system() == 'linux'
        sources += 'serdes_cansocket_test.cpp'
    endif
    e = executable('canas_test',
                    sources,
                    dependencies: [canas_dep,
                                   catch_dep])

    test('canas', e)
endif