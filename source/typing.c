#include "lcd.h"
#include "fsl_debug_console.h"
#include "rand.h"

int NUMBER_OF_WORDS = 5;
int ch_current = 'A';
int typ_pos = 0;

char words[17] = "";

void typing_new_words(void) {
	char w[100] = "";

	for (int i = 0; i < NUMBER_OF_WORDS; i++) {
		if (i != 0) strcat(w, " ");
		strcat(w, rand_get_word());
	}

	for (int i = 0; i < 16; i++) {
		words[i] = w[i];
	}

	words[16] = '\0';
}

void typing_init(void) {
	lcd_clear();
	typing_new_words();

	lcd_goto(0, 0);
	for (int i = 0; words[i] && i < 16; i++) {
		lcd_putc('_');
	}

	lcd_goto(1, 0);
	for (int i = 0; words[i] && i < 16; i++) {
		lcd_putc(words[i]);
	}

	typ_pos = 0;
}

/**
 * dch is either 1 or -1
 */
void typing_change_letter(int dch) {
	ch_current += dch;

	if (ch_current > 'Z') ch_current = 'A';
	else if (ch_current < 'A') ch_current = 'Z';

	lcd_goto(0, typ_pos);
	lcd_putc(ch_current);
}

void typing_confirm_letter(void) {
	PRINTF("T: %d\n", typ_pos);

	if (ch_current == words[typ_pos]) typ_pos++;
	if (words[typ_pos] == ' ') typ_pos++;

	if (!words[typ_pos]) {
		lcd_clear();
		lcd_goto(0, 0);
		lcd_puts("u win");
	} else {
		typing_change_letter(0);
	}
}
