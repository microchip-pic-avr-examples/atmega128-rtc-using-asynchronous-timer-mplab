#include "atmel_start.h"
#include <avr/sleep.h>

static char not_leap(void);
static void init(void);

typedef struct {
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char date;
	unsigned char month;
	unsigned char year;
} time;

time t;

int main(void)
{
	/* Configure all eight pins of port B as outputs */
	system_init();

	/* Initialize registers and configure RTC. */
	init();
	while (1) {
		/* Enter sleep mode.
		 * (Will wake up from timer overflow interrupt) */
		sleep_mode();

		/*The MCU should always be awake for a minimum of one
		 * TOSC cycle, before re-entering sleep mode. Otherwise,
		 * the interrupt flag will not be cleared, and the MCU
		 * will stay in sleep mode until it is reset. We solve
		 * this by doing a dummy write to the TCCR0 register
		 * and waiting until the ASSR register reports that TC0
		 * has been updated, before going to sleep*/

		/* Dummy write the desired prescaler */
		TCCR0 = (1 << CS00) | (1 << CS02);

		/* Wait until TC0 is updated */
		while (ASSR & ((1 << TCN0UB) | (1 << OCR0UB) | (1 << TCR0UB))) {
		}
	}
}

static void init(void)
{
	/* Wait for external clock crystal to stabilize */
	for (uint8_t i = 0; i < 0x40; i++) {
		for (int j = 0; j < 0xFFFF; j++) {
			/* Do a nop instruction to keep the empty
			 * loop from being optimized away */
			asm volatile("nop");
		}
	}

	/* Make sure all TC0 interrupts are disabled */
	TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));

	/* set Timer/counter0 to be asynchronous from the CPU clock.
	 * This will clock TC0 from the external 32,768 kHz crystal. */
	ASSR |= (1 << AS0);

	/* Reset timer */
	TCNT0 = 0;

	/* Prescale the timer to be clock source/128 to make */
	/* TC0 overflow precisely once every second. */
	TCCR0 = (1 << CS00) | (1 << CS02);

	/* Wait until TC0 is updated */
	while (ASSR & ((1 << TCN0UB) | (1 << OCR0UB) | (1 << TCR0UB))) {
	}

	/* Enable Timer/Counter0 Overflow Interrupts */
	TIMSK |= (1 << TOIE0);

	/* Set the Global Interrupt Enable Bit */
	sei();

	/* Setting the sleep mode to be used to power save mode. */
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);

	/* Enabling sleep mode */
	sleep_enable();
}

/* keep track of time, date, month, and year */
ISR(TIMER0_OVF_vect)
{
	if (++t.second == 60) {
		t.second = 0;
		if (++t.minute == 60) {
			t.minute = 0;
			if (++t.hour == 24) {
				t.hour = 0;
				if (++t.date == 32) {
					t.month++;
					t.date = 1;
				} else if (t.date == 31) {
					if ((t.month == 4) || (t.month == 6) || (t.month == 9) || (t.month == 11)) {
						t.month++;
						t.date = 1;
					}
				} else if (t.date == 30) {
					if (t.month == 2) {
						t.month++;
						t.date = 1;
					}
				} else if (t.date == 29) {
					if ((t.month == 2) && (not_leap())) {
						t.month++;
						t.date = 1;
					}
				}

				if (t.month == 13) {
					t.month = 1;
					t.year++;
				}
			}
		}
	}

	PORTB = ~(((t.second & 0x01) | t.minute << 1) | t.hour << 7);
}

/* check for leap year */
static char not_leap(void)
{
	if (!(t.year % 100)) {
		return (char)(t.year % 400);
	} else {
		return (char)(t.year % 4);
	}
}
