cmake_minimum_required(VERSION 3.25)
project(ttns CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT ttns_ipo_supported OUTPUT ttns_ipo_output LANGUAGES CXX)
if(NOT ttns_ipo_supported)
    message(WARNING "IPO/LTO not supported: ${ttns_ipo_output}")
endif()

find_package(Torch CONFIG REQUIRED)

# add_library(ttns
#     include/TTNS/Tree.cpp
# )
# if(ttns_ipo_supported)
#     set_target_properties(ttns PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
# endif()
# target_include_directories(ttns PUBLIC include)

# add_executable(main
#     src/main.cpp
# )
# target_include_directories(main PUBLIC include)
# target_link_libraries(main ttns)
# target_compile_options(main PRIVATE ${TORCH_CXX_FLAGS})
# target_include_directories(main SYSTEM PRIVATE ${TORCH_INCLUDE_DIRS})
# target_link_libraries(main "${TORCH_LIBRARIES}")

add_executable(main
    src/main.cpp
)
target_compile_options(main PRIVATE ${TORCH_CXX_FLAGS})
target_include_directories(main SYSTEM PRIVATE ${TORCH_INCLUDE_DIRS})
target_include_directories(main PUBLIC include)
target_link_libraries(main "${TORCH_LIBRARIES}")
if(ttns_ipo_supported)
    set_target_properties(main PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()


add_executable(tests
    tests/test_tree.cpp
)
target_link_libraries(tests Catch2::Catch2WithMain)
target_include_directories(tests PUBLIC include)
if(ttns_ipo_supported)
    set_target_properties(tests PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_subdirectory(lib/Catch2)
include(CTest)
include(Catch)
catch_discover_tests(tests)