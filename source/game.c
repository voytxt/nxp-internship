#include "lcd.h"
#include "hangman.h"

/**
 * 0 = start
 * 1 = hangman
 * 2 = typing
 * todo hádačka slov based on blinking led
 * todo worlde
 */
int state = 0;


int game_get_state(void) {
	return state;
}

void game_set_state(int new_state) {
	if (new_state == 1) {
		hangman_init();
	} else if (new_state == 2) {
		typing_init();
	}

	state = new_state;
}
