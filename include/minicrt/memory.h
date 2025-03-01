//
// Created by seiftnesse on 3/1/2025.
//

#ifndef MINICRT_MEMORY_H
#define MINICRT_MEMORY_H

/**
 * @file memory.h
 * @brief Memory management functions for MiniCRT
 */

#include "crt.h"

MINICRT_BEGIN
    /**
     * @brief Fill memory with a constant byte
     *
     * This function fills the first count bytes of the memory area pointed to by
     * dest with the constant byte c.
     *
     * @param dest Pointer to the memory area to fill
     * @param c Value to be set (converted to unsigned char)
     * @param count Number of bytes to fill
     * @return Pointer to the memory area (dest)
     */
    void *memset(void *dest, int c, size_t count);

    /**
     * @brief Copy memory area
     *
     * This function copies count bytes from the memory area pointed to by src to
     * the memory area pointed to by dest. The memory areas must not overlap.
     *
     * @param dest Pointer to the destination memory area
     * @param src Pointer to the source memory area
     * @param count Number of bytes to copy
     * @return Pointer to the destination memory area (dest)
     */
    void *memcpy(void *dest, const void *src, size_t count);

    /**
     * @brief Copy memory area, handling overlap
     *
     * This function copies count bytes from the memory area pointed to by src to
     * the memory area pointed to by dest. The memory areas may overlap.
     *
     * @param dest Pointer to the destination memory area
     * @param src Pointer to the source memory area
     * @param count Number of bytes to copy
     * @return Pointer to the destination memory area (dest)
     */
    void *memmove(void *dest, const void *src, size_t count);

    /**
     * @brief Compare memory areas
     *
     * This function compares the first count bytes of the memory areas pointed to by
     * lhs and rhs.
     *
     * @param lhs Pointer to the first memory area
     * @param rhs Pointer to the second memory area
     * @param count Number of bytes to compare
     * @return <0 if lhs is less than rhs, 0 if lhs is equal to rhs, >0 if lhs is greater than rhs
     */
    int memcmp(const void *lhs, const void *rhs, size_t count);

MINICRT_END


#endif // MINICRT_MEMORY_H
