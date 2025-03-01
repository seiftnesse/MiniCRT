//
// Created by seiftnesse on 3/1/2025.
//
#include "minicrt/string.h"


MINICRT_BEGIN
    /**
     * @brief Calculates the length of a string
     *
     * This function counts characters in a string until a null terminator is found.
     *
     * @param str The string to measure
     * @return The number of characters in the string (excluding null terminator)
     */
    size_t strlen(const char *str) {
        /* Implementation notes:
         * 1. We use a simple approach for our first function
         * 2. No check for NULL because that is undefined behavior in standard C
         * 3. We count until we find the null terminator '\0'
         */

        const char *s = str;

        /* Count characters until we find the null terminator */
        while (*s)
            s++;

        /* Return the difference between the current position and start position */
        return (size_t) (s - str);
    }

    /**
     * @brief Calculates the length of a string with a maximum limit
     *
     * This function counts characters in a string until a null terminator is found
     * or until max_len characters have been examined.
     *
     * @param str The string to measure
     * @param max_len The maximum number of characters to examine
     * @return The number of characters in the string (excluding null terminator) or max_len
     */
    size_t strnlen(const char *str, size_t max_len) {
        size_t i;

        /* Count characters until we find the null terminator or reach max_len */
        for (i = 0; i < max_len; i++) {
            if (str[i] == '\0')
                break;
        }

        return i;
    }

    /**
     * @brief Copies a string to a destination buffer
     *
     * This function copies characters from src to dest until the null terminator
     * is encountered, including the null terminator.
     *
     * @param dest The destination buffer
     * @param src The source string
     * @return A pointer to the destination buffer
     */
    char *strcpy(char *dest, const char *src) {
        char *d = dest;

        /* Copy characters until we encounter the null terminator */
        while ((*d++ = *src++) != '\0');

        /* Return the destination buffer */
        return dest;
    }

    /**
     * @brief Compares two strings lexicographically
     *
     * This function compares two strings character by character.
     *
     * @param lhs The first string
     * @param rhs The second string
     * @return <0 if lhs < rhs, 0 if lhs == rhs, >0 if lhs > rhs
     */
    int strcmp(const char *lhs, const char *rhs) {
        /* Compare characters until we find a difference or reach the end */
        while (*lhs && (*lhs == *rhs)) {
            lhs++;
            rhs++;
        }

        /* Return the difference between the characters */
        return (int) (unsigned char) *lhs - (int) (unsigned char) *rhs;
    }

MINICRT_END
