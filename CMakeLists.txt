cmake_minimum_required(VERSION 3.14)
project(MiniCRT VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to enable logging
option(MINI_CRT_ENABLE_LOGGING "Enable logging in MiniCRT" OFF)
if (MINI_CRT_ENABLE_LOGGING)
    add_definitions(-DMINI_CRT_ENABLE_LOGGING)
endif ()

# Library sources
set(CRT_SOURCES
        src/crt/crt_entry.cpp
        src/crt/crt_string.cpp
        src/crt/crt_memory.cpp
)

# Headers
set(HEADERS
        include/minicrt/crt.h
        include/minicrt/string.h
        include/minicrt/memory.h
)

# Create the main library with /NoDefaultLib
add_library(minicrt STATIC ${CRT_SOURCES} ${HEADERS})
target_include_directories(minicrt
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Setup compilation options for minicrt
if (MSVC)
    target_compile_options(minicrt PRIVATE
            /GS-
            /Gs0
    )
    target_compile_definitions(minicrt PRIVATE
            _NO_CRT_STDIO_INLINE
            MINICRT_BUILDING_LIB
    )
    set_target_properties(minicrt PROPERTIES
            STATIC_LIBRARY_OPTIONS "/NODEFAULTLIB"
    )
elseif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(minicrt PRIVATE
            -fno-builtin
            -ffreestanding
            -fno-exceptions
    )
    target_compile_definitions(minicrt PRIVATE MINICRT_BUILDING_LIB)
endif ()

# Optional: Enable testing
option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
    #  For tests, create a completely separate package to avoid inheriting flags
    add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()

# Installation settings
include(GNUInstallDirs)
install(TARGETS minicrt
        EXPORT minicrtTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets
install(EXPORT minicrtTargets
        FILE minicrtTargets.cmake
        NAMESPACE minicrt::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/minicrt
)

# Create and install the config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/minicrtConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/minicrtConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/minicrt
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/minicrtConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/minicrtConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/minicrtConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/minicrt
)