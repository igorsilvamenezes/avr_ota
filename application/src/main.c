/**
 * @file main.c
 * @brief Application entry point (Step 0 placeholder).
 *
 * Exists only to prove the toolchain, Makefile and flashing flow work
 * end to end. Real behaviour starts in Step 1.
 */
#include <avr/io.h>
#include <util/delay.h>

#include "memory_map.h" /* compiled here so its sanity chechs run */

/** Time between LED toggless; a full on/off cycle therefore takes 2 s.  */
#define LED_TOGGLE_INTERVAL_MS  1000U

/** Heartbeat LED bit within PORTA. */
#define HEARTBEAT_LED_BIT       PA0

int main(void)
{
    /** Only PA0 becomes an output; the other PORTA pins keep their reset
     * state (input, no pull-up) so nothing else on the board is driven. */
    DDRA |= _BV(HEARTBEAT_LED_BIT);

    for (;;) {
        /* ATmega128 has no "write 1 to PINx to toggle" feature (newer AVRs
         * do), so toggling must be a read-modify-write on PORT. */
        PORTA ^= _BV(HEARTBEAT_LED_BIT);

        /* Busy-wait; the CPU does nothing else meanwhile. Acceptable for a
         * first test, replaced by a timer-driven tick in Step 3. */
        _delay_ms(LED_TOGGLE_INTERVAL_MS);
    }
}
