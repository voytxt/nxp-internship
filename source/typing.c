#include "lcd.h"
#include "fsl_debug_console.h"

int NUMBER_OF_WORDS = 3;
int ch_current = 'A';
int typ_pos = 0;

char *words = "AAA BBB CCCC";

void typing_new_words(void) {
	for (int i = 0; i < NUMBER_OF_WORDS; i++) {

	}
}

void typing_init(void) {
	lcd_clear();
	typing_new_words();

	lcd_goto(0, 0);
	for (char *ch = words; *ch; *ch++) {
		lcd_putc('_');
	}

	lcd_goto(1, 0);
	for (char *ch = words; *ch; *ch++) {
		lcd_putc(*ch);
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
