//
// Created by seiftnesse on 3/1/2025.
//

#ifndef MINICRT_CRT_H
#define MINICRT_CRT_H

/**
 * @file crt.h
 * @brief Main header file for MiniCRT - custom implementation of C Runtime Library
 */

// Define namespace macros for easy toggling between namespace and global functions
#ifdef MINICRT_BUILDING_LIB
    // When building the library, we define everything in the minicrt namespace
    #define MINICRT_BEGIN namespace minicrt {
    #define MINICRT_END }
    #define MINICRT_USING
#else
    // When including from outside, we use the minicrt namespace explicitly
    #define MINICRT_BEGIN namespace minicrt {
    #define MINICRT_END }
    #define MINICRT_USING using namespace minicrt;
#endif

// Basic types
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
    #ifdef _WIN64
        typedef unsigned long long size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
#ifdef _WIN64
typedef long long ptrdiff_t;
#else
typedef int ptrdiff_t;
#endif
#endif

MINICRT_BEGIN

typedef int errno_t;

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#define MINICRT_WINDOWS
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
#define MINICRT_UNIX
#else
#error "Unsupported platform"
#endif

// NULL definition
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

// Inline function support
#ifndef MINICRT_INLINE
#if defined(_MSC_VER)
#define MINICRT_INLINE __inline
#elif defined(__GNUC__)
#define MINICRT_INLINE inline
#else
#define MINICRT_INLINE
#endif
#endif

// Initialization and termination
void minicrt_init(void);
void minicrt_cleanup(void);

// Program termination
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void exit(int status);

// Error handling
extern int errno;

MINICRT_END

#endif // MINICRT_CRT_H
