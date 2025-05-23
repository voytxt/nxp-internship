#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "lcd.h"
#include "enc.h"
#include "bt.h"

void set_led(int r, int g, int b) {
	GPIO_PinWrite(BOARD_LED_R_GPIO, BOARD_LED_R_PIN, r);
	GPIO_PinWrite(BOARD_LED_G_GPIO, BOARD_LED_G_PIN, g);
	GPIO_PinWrite(BOARD_LED_B_GPIO, BOARD_LED_B_PIN, b);
}

char secret[] = "CHESS";

char ch = 'A';

void update() {
	int enc_state = get_enc_state();

	if (enc_state) {
		ch += enc_state;
		if (ch > 'Z') ch = 'A';
		else if (ch < 'A') ch = 'Z';

		lcd_putc_at_caret(ch);
	}
}

void PIT_CHANNEL_0_IRQHANDLER(void) {
	/* Reading all interrupt flags of status register */
	uint32_t intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0);
	PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0, intStatus);

	/* Code to run every millisecond */
	update();

	/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
	 Store immediate overlapping exception return operation might vector to incorrect interrupt. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

int main(void) {
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
	lcd_init();
	PRINTF("init done\n");

	set_led(0, 0, 0);

	long long t = 0;

	while (1) {
		int bt_state = get_bt_state();

		if (bt_state == 2) lcd_move_caret(1);
		else if (bt_state == 3) lcd_move_caret(-1);

		if (t % 100000 == 0) {
			t = 0;

			PRINTF("BT: %d\n", get_bt_state());
		}

		t++;
	}

	return 0;
}

