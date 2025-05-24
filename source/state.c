#include "lcd.h"
#include "hangman.h"

/**
 * 0 = start
 * todo hádačka slov based on blinking led
 * todo hangman
 * todo worlde
 */
int state = 0;


int get_state(void) {
	return state;
}

void set_state(int new_state) {
	// hangman
	if (new_state == 1) {
		hangman_init();
	}

	state = new_state;
}
