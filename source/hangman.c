#include <string.h>
#include "lcd.h"
#include "fsl_debug_console.h"

char secret[] = "CHESS";
char ch_guess = 'A';
int tries = 0;

char* new_hangman_secret(void) {
	strcpy(secret, "BATTLE");
	return secret;
}

char* get_hangman_secret(void) {
	return secret;
}

void hangman_init(void) {
	lcd_clear();
	lcd_goto(0, 0);

	for (char *ch = new_hangman_secret(); *ch; *ch++) {
		lcd_putc('_');
	}

	lcd_goto(1, 0);
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
//	lcd_putc_at_caret(ch_guess);
}

void hangman_confirm_guess(void) {
	char *ch = secret;
	for (int i = 0; *ch; *ch++, i++) {
		PRINTF("guess %c | ch %c\n", ch_guess, *ch);
		if (*ch == ch_guess) {
			PRINTF("GOT %c\n", *ch);
			lcd_goto(0, i);
			lcd_putc(*ch);
		}
	}

	lcd_goto(0, 15);
	lcd_putc(++tries + 48);
}
