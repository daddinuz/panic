set(HERE ${CMAKE_CURRENT_LIST_DIR})

add_library(fixtures ${HERE}/fixtures.h ${HERE}/fixtures.c)
target_link_libraries(fixtures PRIVATE panic traits-unit)

add_library(features ${HERE}/features.h ${HERE}/features.c)
target_link_libraries(features PRIVATE panic traits-unit)

add_executable(describe ${HERE}/describe.c)
target_link_libraries(describe PRIVATE fixtures features)

add_test(describe describe)
enable_testing()

unset(HERE)
