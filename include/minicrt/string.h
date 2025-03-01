//
// Created by seiftnesse on 3/1/2025.
//

#ifndef MINICRT_STRING_H
#define MINICRT_STRING_H

/**
 * @file string.h
 * @brief String manipulation functions for MiniCRT
 */

#include "crt.h"


MINICRT_BEGIN
    /**
     * @brief Calculate the length of a string
     *
     * This function calculates the length of the given string by counting characters
     * until a null terminator is reached.
     *
     * @param str Pointer to the null-terminated string
     * @return The length of the string (excluding the null terminator)
     */
    size_t strlen(const char *str);

    /**
     * @brief Calculate the length of a string with a maximum limit
     *
     * This function calculates the length of the given string by counting characters
     * until either a null terminator is reached or max_len characters have been examined.
     *
     * @param str Pointer to the string
     * @param max_len Maximum number of characters to examine
     * @return The length of the string (excluding the null terminator) or max_len if no
     *         null terminator is found within max_len characters
     */
    size_t strnlen(const char *str, size_t max_len);

    /**
     * @brief Copy a string to another location
     *
     * This function copies the src string to the dest location. The dest buffer must be
     * large enough to hold the src string including the null terminator.
     *
     * @param dest Pointer to the destination buffer
     * @param src Pointer to the source string
     * @return A pointer to the destination string (dest)
     */
    char *strcpy(char *dest, const char *src);

    /**
     * @brief Compare two strings
     *
     * This function compares two strings lexicographically.
     *
     * @param lhs Pointer to the first string
     * @param rhs Pointer to the second string
     * @return <0 if lhs is less than rhs, 0 if lhs is equal to rhs, >0 if lhs is greater than rhs
     */
    int strcmp(const char *lhs, const char *rhs);

MINICRT_END

#endif // MINICRT_STRING_H
