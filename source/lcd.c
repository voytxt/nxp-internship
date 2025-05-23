#include "pin_mux.h"
#include "board.h"
#include "MK64F12.h"

#define LCD_GPIO(gpio, pin) ((gpio)->PDDR |= (1U << (pin)))
#define LCD_SET(gpio, pin)  ((gpio)->PSOR  = (1U << (pin)))
#define LCD_CLR(gpio, pin)  ((gpio)->PCOR  = (1U << (pin)))

static void lcd_delay_us(volatile uint32_t us) {
	while (us--) {
		for (volatile int i = 0; i < 10; i++) {
			__NOP();
		}
	}
}

static void lcd_write_nibble(uint8_t nibble) {
	LCD_CLR(BOARD_DB4_GPIO, BOARD_DB4_PIN);
	LCD_CLR(BOARD_DB6_GPIO, BOARD_DB6_PIN);
	LCD_CLR(BOARD_DB5_GPIO, BOARD_DB5_PIN);
	LCD_CLR(BOARD_DB7_GPIO, BOARD_DB7_PIN);

	if (nibble & 0x1) LCD_SET(BOARD_DB4_GPIO, BOARD_DB4_PIN);
	if (nibble & 0x2) LCD_SET(BOARD_DB5_GPIO, BOARD_DB5_PIN);
	if (nibble & 0x4) LCD_SET(BOARD_DB6_GPIO, BOARD_DB6_PIN);
	if (nibble & 0x8) LCD_SET(BOARD_DB7_GPIO, BOARD_DB7_PIN);

	LCD_SET(BOARD_D_E_GPIO, BOARD_D_E_PIN);
	lcd_delay_us(1);
	LCD_CLR(BOARD_D_E_GPIO, BOARD_D_E_PIN);
	lcd_delay_us(100);
}

/**
 * send either a command (isData=0) or a data byte (isData=1)
 */
static void lcd_send(uint8_t value, bool isData) {
	if (isData) LCD_SET(BOARD_D_RS_GPIO, BOARD_D_RS_PIN);
	else LCD_CLR(BOARD_D_RS_GPIO, BOARD_D_RS_PIN);

	lcd_write_nibble(value >> 4); // high nibble
	lcd_write_nibble(value & 0x0F); // low nibble
}

void lcd_init(void) {
	LCD_CLR(BOARD_D_RS_GPIO, BOARD_D_RS_PIN);
	lcd_write_nibble(0x3);
	lcd_delay_us(5000);
	lcd_write_nibble(0x3);
	lcd_delay_us(150);
	lcd_write_nibble(0x3);
	lcd_write_nibble(0x2); // set 4-bit mode
	lcd_send(0x28, false); // function set: 2 lines, 5×8 dots
	lcd_send(0x08, false); // display off
	lcd_send(0x01, false); // clear
	lcd_delay_us(2000);
	lcd_send(0x06, false); // entry mode: inc, no shift
	lcd_send(0x0C, false); // display on, cursor off, blink off
}

void lcd_putc(char c) {
	lcd_send((uint8_t) c, true);
}

void lcd_puts(const char *s) {
	while (*s) {
		lcd_putc(*s++);
	}
}

void lcd_goto(uint8_t row, uint8_t col) {
	uint8_t addr = row * 64 + col;
	lcd_send(0x80 | addr, false);
}

int caret_pos = 0;

int lcd_get_caret_pos(void) {
	return caret_pos;
}

void lcd_update_caret(void) {
	lcd_goto(1, 0);

	for (int i = 0; i < 16; i++) {
		lcd_putc(i == caret_pos ? '^' : ' ');
	}
}

void lcd_move_caret(int dx) {
	lcd_goto(1, caret_pos);
	lcd_putc(' ');

	caret_pos = (caret_pos + dx + 16) % 16;

	lcd_goto(1, caret_pos);
	lcd_putc('^');
}

void lcd_putc_at_caret(char ch) {
	lcd_goto(0, caret_pos);
	lcd_putc(ch);
}
