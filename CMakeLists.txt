cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(ip_filter VERSION 0.0.1)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(ip_filter ip_filter.h ip_filter.cpp)
add_executable(ip_filter_test ip_filter_test.cpp)

set_target_properties(ip_filter ip_filter_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON 
)

target_include_directories(ip_filter_test
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(ip_filter_test
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_test PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT savenko.bogdan@gmail.com)

include(CPack)

enable_testing()

add_test(ip_filter_test ip_filter_test)