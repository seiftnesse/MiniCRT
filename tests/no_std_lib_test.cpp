//
// Created by seiftnesse on 3/1/2025.
//
#include "minicrt/string.h"
#include "minicrt/memory.h"

// Simplified test framework macros without using stdio.h
#define TEST_ASSERT(condition) do { if (!(condition)) return #condition; } while(0)
#define TEST_ASSERT_EQ(a, b) do { if ((a) != (b)) return "Expected equality failed"; } while(0)
#define TEST_ASSERT_NE(a, b) do { if ((a) == (b)) return "Expected inequality failed"; } while(0)
#define TEST_ASSERT_STR_EQ(a, b) do { if (minicrt::strcmp((a), (b)) != 0) return "Expected string equality failed"; } while(0)

// Test function signature - returns NULL on success, or error message on failure
typedef const char * (*TestFunc)();

// Test function declarations
const char *test_strlen_basic();

const char *test_strnlen_basic();

const char *test_strcpy_basic();

const char *test_strcmp_basic();

const char *test_memory_basic();

int main();

#ifdef _WIN32
// Import Windows API directly
extern "C" {
int __stdcall WriteFile(void *hFile, const void *buffer, unsigned long nBytesToWrite,
                        unsigned long *lpBytesWritten, void *lpOverlapped);
}

extern "C" int CustomMainCRTStartup() {
    return main();
}

// Runtime Check stubs
extern "C" {
// RTC (Runtime Check) stubs
void _RTC_InitBase() {
}

void _RTC_Shutdown() {
}

void _RTC_CheckStackVars(void *, void *) {
}

// Stack check stub - critical for stack allocations
#ifdef _WIN64
void __chkstk() {
}
#else
    void _chkstk() {}
#endif
}
#endif


// Custom output function since we don't have stdio
void output_string(const char *str) {
#ifdef _WIN32
    // Use Windows API to print to console
#ifdef _WIN64
    // On 64-bit Windows, use the correct value for handles
    void *handle = reinterpret_cast<void *>(static_cast<long int>(-11)); // STD_OUTPUT_HANDLE is -11
#else
    // On 32-bit Windows, the original value works fine
    void* handle = reinterpret_cast<void*>(0xfffffff5); // STD_OUTPUT_HANDLE
#endif
    unsigned long written;
    unsigned long len = 0;
    const char *s = str;
    while (*s++) len++;

    WriteFile(handle, str, len, &written, 0);
#else
    // Use Linux syscall for write to stdout
    long result = 0;
    int len = 0;
    const char* s = str;
    while (*s++) len++;

    asm("movl $1, %%eax\n"     // syscall: write
        "movl $1, %%edi\n"     // file descriptor: stdout
        "movq %1, %%rsi\n"     // buffer
        "movl %2, %%edx\n"     // length
        "syscall\n"
        "movl %%eax, %0"
        : "=r" (result)
        : "r" (str), "r" (len)
        : "eax", "edi", "rsi", "edx");
#endif
}

/**
 * Main entry point for string tests
 */
int main() {
    // List of all test functions
    TestFunc tests[] = {
        test_strlen_basic,
        test_strnlen_basic,
        test_strcpy_basic,
        test_strcmp_basic,
        // test_memory_basic
    };

    int test_count = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    int failed = 0;

    // Run each test
    for (int i = 0; i < test_count; i++) {
        const char *result = tests[i]();
        if (result == 0) {
            passed++;
        } else {
            failed++;
            // In a real implementation, we would print the error message
            // but we don't have printf yet
        }
    }

    // Use a simple check to verify all tests passed
    if (passed == test_count && failed == 0) {
        const char success_message[] = "All tests passed!\n";
        output_string(success_message);
        return 0; // Success
    }

    return 1; // Failure
}

/**
 * Test basic functionality of strlen
 */
const char *test_strlen_basic() {
    const char *empty = "";
    const char *hello = "Hello";
    const char *with_spaces = "Hello, World!";
    const char *with_null = "Hello\0World";

    TEST_ASSERT_EQ(0, minicrt::strlen(empty));
    TEST_ASSERT_EQ(5, minicrt::strlen(hello));
    TEST_ASSERT_EQ(13, minicrt::strlen(with_spaces));
    TEST_ASSERT_EQ(5, minicrt::strlen(with_null)); // Should stop at the null character

    return 0; // Success
}

/**
 * Test basic functionality of strnlen
 */
const char *test_strnlen_basic() {
    const char *hello = "Hello";

    TEST_ASSERT_EQ(0, minicrt::strnlen(hello, 0));
    TEST_ASSERT_EQ(3, minicrt::strnlen(hello, 3));
    TEST_ASSERT_EQ(5, minicrt::strnlen(hello, 10));

    return 0; // Success
}

/**
 * Test basic functionality of strcpy
 */
const char *test_strcpy_basic() {
    const char *src = "Hello, World!";
    char dest[20];

    char *result = minicrt::strcpy(dest, src);

    TEST_ASSERT_EQ(result, dest);
    TEST_ASSERT_STR_EQ(dest, src);

    return 0; // Success
}

/**
 * Test basic functionality of strcmp
 */
const char *test_strcmp_basic() {
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";
    const char *str4 = "Hallo";

    TEST_ASSERT_EQ(0, minicrt::strcmp(str1, str2));
    TEST_ASSERT(minicrt::strcmp(str1, str3) < 0); // "Hello" < "World"
    TEST_ASSERT(minicrt::strcmp(str1, str4) > 0); // "Hello" > "Hallo"

    return 0; // Success
}

/**
 * Test basic memory operations
 */
/*const char* test_memory_basic()
{
    // Test malloc/free
    void* ptr = minicrt::malloc(100);
    TEST_ASSERT_NE(ptr, 0);

    // Test memset
    minicrt::memset(ptr, 0xAA, 100);
    unsigned char* bytePtr = (unsigned char*)ptr;
    for (int i = 0; i < 100; i++)
    {
        TEST_ASSERT_EQ(bytePtr[i], 0xAA);
    }

    // Test memcpy
    char src[10] = "TestData";
    minicrt::memcpy(ptr, src, 9);
    TEST_ASSERT_EQ(minicrt::memcmp(ptr, src, 9), 0);

    // Test free
    // minicrt::free(ptr);

    return 0; // Success
}*/
