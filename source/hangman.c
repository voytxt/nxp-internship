#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "lcd.h"
#include "fsl_debug_console.h"

char secret[16] = "";
char ch_guess = 'A';
int tries = 0;

char* new_hangman_secret(void) {
	const char *words[] = {"CHESS", "BATTLE", "TIME", "PERSON", "YEAR", "THING", "WORLD", "WOMAN", "WORK", "GROUP"};
	strcpy(secret, words[rand() % 10]);

	return secret;
}

void hangman_init(void) {
	tries = 0;

	lcd_clear();
	lcd_goto(0, 0);

	for (char *ch = new_hangman_secret(); *ch; *ch++) {
		lcd_putc('_');
	}

	srand(time(NULL));
}

/**
 * dch is either 1 or -1
 */
void hangman_change_guess(int dch) {
	ch_guess += dch;

	if (ch_guess > 'Z') ch_guess = 'A';
	else if (ch_guess < 'A') ch_guess = 'Z';

	lcd_goto(1, 15);
	lcd_putc(ch_guess);
}

void hangman_confirm_guess(void) {
	for (int i = 0; secret[i]; i++) {
		if (secret[i] == ch_guess) {
			lcd_goto(0, i);
			lcd_putc(secret[i]);
		}
	}

	tries++;
	lcd_goto(0, 14);
	lcd_putc(tries / 10 + 48);
	lcd_putc((tries % 10) + 48);
}
