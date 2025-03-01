#include <gtest/gtest.h>
#include "minicrt/string.h"

// Test basic functionality of strlen
TEST(StringTest, StrLenBasic) {
    const char *empty = "";
    const char *hello = "Hello";
    const char *with_spaces = "Hello, World!";
    const char *with_null = "Hello\0World";

    EXPECT_EQ(0, minicrt::strlen(empty));
    EXPECT_EQ(5, minicrt::strlen(hello));
    EXPECT_EQ(13, minicrt::strlen(with_spaces));
    EXPECT_EQ(5, minicrt::strlen(with_null)); // Should stop at the null character
}

// Test basic functionality of strnlen
TEST(StringTest, StrNLenBasic) {
    const char *hello = "Hello";

    EXPECT_EQ(0, minicrt::strnlen(hello, 0));
    EXPECT_EQ(3, minicrt::strnlen(hello, 3));
    EXPECT_EQ(5, minicrt::strnlen(hello, 10));
}

// Test basic functionality of strcpy
TEST(StringTest, StrCpyBasic) {
    const char *src = "Hello, World!";
    char dest[20];

    char *result = minicrt::strcpy(dest, src);

    EXPECT_EQ(result, dest);
    EXPECT_STREQ(dest, src);
}

// Test basic functionality of strcmp
TEST(StringTest, StrCmpBasic) {
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";
    const char *str4 = "Hallo";

    EXPECT_EQ(0, minicrt::strcmp(str1, str2));
    EXPECT_LT(minicrt::strcmp(str1, str3), 0); // "Hello" < "World"
    EXPECT_GT(minicrt::strcmp(str1, str4), 0); // "Hello" > "Hallo"
}

// Test comparison with standard library
TEST(StringTest, CompareWithStdLib) {
    // Check our functions against the standard ones
    const char *text = "The quick brown fox jumps over the lazy dog";

    EXPECT_EQ(minicrt::strlen(text), ::strlen(text));

    char dest1[100];
    char dest2[100];

    minicrt::strcpy(dest1, text);
    ::strcpy(dest2, text);

    EXPECT_STREQ(dest1, dest2);

    EXPECT_EQ(minicrt::strcmp(text, dest1), ::strcmp(text, dest2));
}
