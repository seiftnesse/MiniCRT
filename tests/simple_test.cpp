//
// Created by seiftnesse on 3/1/2025.
//

#include "minicrt/string.h"

/**
 * Simple test program that doesn't require GTest
 * Tests basic string functions
 */
int main() {
    // Test strlen
    const char *test_str = "Hello, World!";
    size_t len = minicrt::strlen(test_str);

    // Test string copy
    char buffer[64];
    minicrt::strcpy(buffer, test_str);

    // Test string comparison
    int cmp_result = minicrt::strcmp(buffer, test_str);

    // Test success if we got here without crashes
    // and our string functions work correctly
    return (len == 13 && cmp_result == 0) ? 0 : 1;
}
