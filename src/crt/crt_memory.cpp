//
// Created by seiftnesse on 3/1/2025.
//

#include "minicrt/memory.h"

MINICRT_BEGIN
    // For Windows platform-specific memory operations
    /**
     * @brief Fill a block of memory with a value
     */
    void *memset(void *dest, int c, size_t count) {
        unsigned char *p = (unsigned char *) dest;
        unsigned char value = (unsigned char) c;

        while (count--)
            *p++ = value;

        return dest;
    }

    /**
     * @brief Copy memory from one location to another
     */
    void *memcpy(void *dest, const void *src, size_t count) {
        unsigned char *d = (unsigned char *) dest;
        const unsigned char *s = (const unsigned char *) src;

        while (count--)
            *d++ = *s++;

        return dest;
    }

    /**
     * @brief Copy memory, handling overlapping regions
     */
    void *memmove(void *dest, const void *src, size_t count) {
        unsigned char *d = (unsigned char *) dest;
        const unsigned char *s = (const unsigned char *) src;

        // If source and destination don't overlap, use simple copy
        if (d >= s + count || s >= d + count)
            return memcpy(dest, src, count);

        // If source is before destination, copy backwards to avoid overwriting source
        if (d > s) {
            d += count - 1;
            s += count - 1;
            while (count--)
                *d-- = *s--;
        }
        // If destination is before source, copy forwards
        else {
            while (count--)
                *d++ = *s++;
        }

        return dest;
    }

    /**
     * @brief Compare two memory regions
     */
    int memcmp(const void *lhs, const void *rhs, size_t count) {
        const unsigned char *l = (const unsigned char *) lhs;
        const unsigned char *r = (const unsigned char *) rhs;

        while (count--) {
            if (*l != *r)
                return *l - *r;
            l++;
            r++;
        }

        return 0;
    }

MINICRT_END
