/**
 * @file main.c
 * @brief Application entry point (Step 0 placeholder).
 *
 * Exists only to prove the toolchain, Makefile and flashing flow work
 * end to end. Real behaviour starts in Step 1.
 */
#include <avr/io.h>
#include "memory_map.h" /* compiled here so its sanity chechs run */

int main(void)
{
    for (;;) {
        /* Nothing to do yet: an empty loop keeps the CPU parked
         * instead of running off into erased flash. */
    }
}
