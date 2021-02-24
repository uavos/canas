if(not meson.is_cross_build())
    e = executable('canas_test',
                   'core_test.cpp',
                   'circularbuffer_test.cpp',
                   'crc16ibm_test.cpp',
                   'slip_test.cpp',
                    dependencies: canas_dep)

    test('canas', e)
endif