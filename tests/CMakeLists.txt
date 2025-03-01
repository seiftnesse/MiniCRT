# Create a standalone project for tests
project(MiniCRTTests CXX)

# Set C++ standard settings once at the top
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable warnings about unsafe functions
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# Create a separate test library to avoid inheriting flags
add_library(minicrt_test STATIC
        ${CMAKE_SOURCE_DIR}/src/crt/crt_string.cpp
        ${CMAKE_SOURCE_DIR}/src/crt/crt_memory.cpp
        ${CMAKE_SOURCE_DIR}/src/crt/crt_entry.cpp
)

# Configure the test library
target_include_directories(minicrt_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(minicrt_test PRIVATE MINICRT_BUILDING_LIB)

# Setup Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create test executables
add_executable(test_string test_string.cpp)
target_link_libraries(test_string PRIVATE minicrt_test GTest::gtest_main)

# Simple test without Google Test
add_executable(simple_test simple_test.cpp)
target_link_libraries(simple_test PRIVATE minicrt_test)

# Enable CTest and register tests
enable_testing()
include(GoogleTest)
gtest_discover_tests(test_string)
add_test(NAME simple_test COMMAND simple_test)

# Platform-specific test with /NoDefaultLib (Windows only)
if (MSVC OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND WIN32))
    # Use the original approach from the first CMakeLists.txt that worked
    add_executable(no_std_lib_test no_std_lib_test.cpp)

    # Make sure we have the right include paths
    target_include_directories(no_std_lib_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

    # Use the same path that worked in the original CMakeLists.txt
    if (EXISTS "${CMAKE_SOURCE_DIR}/cmake-build-debug/minicrt.lib")
        target_link_libraries(no_std_lib_test PRIVATE "${CMAKE_SOURCE_DIR}/cmake-build-debug/minicrt.lib")
    else ()
        message(STATUS "Looking for minicrt.lib in alternate locations...")
        # Try to find minicrt.lib in common build directories
        file(GLOB_RECURSE MINICRT_LIB_CANDIDATES
                "${CMAKE_BINARY_DIR}/**/minicrt.lib"
                "${CMAKE_SOURCE_DIR}/**/minicrt.lib"
        )
        if (MINICRT_LIB_CANDIDATES)
            list(GET MINICRT_LIB_CANDIDATES 0 MINICRT_LIB_PATH)
            message(STATUS "Found minicrt.lib at: ${MINICRT_LIB_PATH}")
            target_link_libraries(no_std_lib_test PRIVATE "${MINICRT_LIB_PATH}")
        else ()
            message(WARNING "minicrt.lib not found! Make sure to build the main minicrt target first.")
            message(WARNING "You may need to modify the CMakeLists.txt to specify the correct path.")
        endif ()
    endif ()

    # Set compiler-specific options
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # Clang-specific compiler options
        target_compile_options(no_std_lib_test PRIVATE
                -fno-builtin      # Don't use built-in functions
                -fno-stack-protector  # Disable stack protection
                -ffreestanding    # Freestanding environment (no standard library)
        )

        # Clang-specific linker options - use different syntax
        if (WIN32)
            # For Clang on Windows, we need to use -Wl flags to pass options to the linker
            target_link_options(no_std_lib_test PRIVATE
                    -fuse-ld=lld-link
                    "-Wl,-nodefaultlib"
                    "-Wl,-entry:CustomMainCRTStartup"
            )
        else ()
            # For Clang on Unix, use appropriate flags
            target_link_options(no_std_lib_test PRIVATE
                    -nostdlib
                    -e _start
            )
        endif ()
    else ()
        # MSVC-specific compiler options
        target_compile_options(no_std_lib_test PRIVATE
                /GS-   # Disable buffer security checks
                /Gs0   # Disable stack probes
        )

        # MSVC-specific linker options
        set_target_properties(no_std_lib_test PROPERTIES
                LINK_FLAGS "/NODEFAULTLIB /ENTRY:CustomMainCRTStartup"
        )
    endif ()

    # Register the test
    add_test(
            NAME no_default_lib_test
            COMMAND no_std_lib_test
    )

    # Set test success criteria
    set_tests_properties(no_default_lib_test PROPERTIES
            PASS_REGULAR_EXPRESSION "All tests passed"
    )
endif ()