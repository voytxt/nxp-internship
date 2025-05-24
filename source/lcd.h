void lcd_init(void);
void lcd_goto(int row, int col);
void lcd_puts(const char *s);
void lcd_putc(char);
void lcd_delay_us(volatile int);
void lcd_clear(void);

int lcd_get_caret(void);
void lcd_move_caret(int dx);
void lcd_putc_at_caret(char ch);
