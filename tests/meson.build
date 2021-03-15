if(not meson.is_cross_build())
    catch_dep = subproject('catch2').get_variable('catch2_dep')
    e = executable('canas_test',
                   'core_test.cpp',
                   'circularbuffer_test.cpp',
                   'crc16ibm_test.cpp',
                   'slip_test.cpp',
                    dependencies: [canas_dep,
                                   catch_dep])

    test('canas', e)
endif