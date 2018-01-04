cmake_minimum_required(VERSION 3.8)
project(bone)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES include/bone/step_iterator.hpp
                 include/bone/event_dispatcher.hpp
                 include/bone/move_checker.hpp
   )
set(TEST_FILES tests/main_tests.cpp
               tests/step_iterator_tests.cpp
               tests/event_dispatcher_tests.cpp
   )

include_directories( include )
add_executable(bone ${TEST_FILES} ${HEADER_FILES})

if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT bone)
endif()
