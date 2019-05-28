cmake_minimum_required(VERSION 3.10)
project(bone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER_FILES include/bone/step_iterator.hpp
                 include/bone/event_dispatcher.hpp
                 include/bone/move_checker.hpp
                 include/bone/c_api_interop.hpp
                 include/bone/stable_priority_queue.hpp
                 include/bone/cyclic_queue.hpp
                 include/bone/noalloc_vector.hpp
                 include/bone/multi_array.hpp
   )
set(TEST_FILES tests/main_tests.cpp
               tests/step_iterator_tests.cpp
               tests/event_dispatcher_tests.cpp
               tests/move_checker_tests.cpp
               tests/c_api_interop_tests.cpp
               tests/stable_priority_queue_tests.cpp
               tests/cyclic_queue_tests.cpp
               tests/noalloc_vector_tests.cpp
               tests/multi_array_tests.cpp
   )

include_directories( include )
add_executable(bone_test ${TEST_FILES} ${HEADER_FILES})

if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT bone)
    target_compile_options(bone_test PRIVATE /permissive- /GR-)
else()
    target_compile_options(bone_test PRIVATE -fno-rtti)
endif()
