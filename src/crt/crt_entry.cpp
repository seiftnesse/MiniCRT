//
// Created by seiftnesse on 3/1/2025.
//
#include "minicrt/crt.h"

MINICRT_BEGIN
    // Global error variable
    int errno = 0;

    /**
     * @brief Initialize CRT before main
     *
     * This function is called before main() to set up the CRT environment
     */
    void minicrt_init(void) {
        // This would typically initialize various subsystems
        // For now, we have a minimal implementation
    }

    /**
     * @brief Clean up CRT resources
     *
     * This function is called when the program exits
     */
    void minicrt_cleanup(void) {
        // This would typically clean up resources
        // For now, we have a minimal implementation
    }

    /**
     * @brief Terminate the program
     *
     * @param status Exit status code
     */
    void exit(int status) {
        // Clean up resources
        minicrt_cleanup();

#ifdef MINICRT_WINDOWS
        // Windows-specific exit
#define WIN32_LEAN_AND_MEAN
        /*#include <Windows.h>
        ExitProcess(status);*/
#else
    // Unix-like systems
    asm("movl %0, %%edi\n"
        "movl $60, %%eax\n"  // syscall: exit
        "syscall"
        : : "r" (status) : "edi", "eax");

    // Should never reach here
    __builtin_unreachable();
#endif
    }

    // CRT entry point is defined when compiled with /NoDefaultLib
#ifdef MINICRT_BUILDING_LIB

    // Forward declaration for user's main function
    extern int main(int argc, char *argv[]);

#ifdef MINICRT_WINDOWS
    /**
     * @brief Entry point for Windows applications
     *
     * This is the entry point when using /ENTRY:CustomMainCRTStartup
     */
    int CustomMainCRTStartup(void) {
        // Initialize CRT
        minicrt_init();

        // Call the main function
        int exit_code = main(0, NULL); // We don't process command line args yet

        // Exit the program
        exit(exit_code);

        // Should never reach here
        return exit_code;
    }
#else
/**
 * @brief Entry point for Unix-like applications
 */
void _start(void)
{
    // Initialize CRT
    minicrt_init();

    // Call the main function
    int exit_code = main(0, NULL);  // We don't process command line args yet

    // Exit the program
    exit(exit_code);

    // Should never reach here
    __builtin_unreachable();
}
#endif

#endif // MINICRT_BUILDING_LIB

MINICRT_END
