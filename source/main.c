#include "game.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "enc.h"
#include "bt.h"
#include "lcd.h"
#include "temp.h"
#include "hangman.h"
#include "rand.h"
#include "led.h"
#include "fsl_debug_console.h"
#include "typing.h"

void PIT_CHANNEL_0_IRQHANDLER(void) {
	// read all interrupt flags of status register
	uint32_t intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0);
	PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0, intStatus);

	// run every millisecond
	switch (game_get_state()) {
	case 1: {
		int enc_state = enc_get_state();
		if (enc_state) hangman_change_guess(enc_state);
		break;
	}

	case 2: {
		int enc_state = enc_get_state();
		if (enc_state) typing_change_letter(enc_state);
		break;
	}
	}
}

int main(void) {
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();
	lcd_init();

	PRINTF("init done\n");

	set_led(0, 0, 0);

	lcd_goto(0, 0);
	lcd_puts("welcome!");

	long long t = 0;

	while (1) {
		int bt_state = bt_get_state();
		if (bt_state == 1) game_set_state(1);
		else if (bt_state == 2) game_set_state(2);

		switch (game_get_state()) {

		case 1: {
			if (enc_sw_get_state()) hangman_confirm_guess();
			break;
		}

		case 2: {
			if (enc_sw_get_state()) typing_confirm_letter();
			break;
		}

		case 69: {
			int bt_state = bt_get_state();

			if (bt_state == 2) lcd_move_caret(1);
			else if (bt_state == 3) lcd_move_caret(-1);

			if (t % 100000 == 0) {
				t = 0;

				PRINTF("BT: %d\n", bt_get_state());

				get_temp_state();
			}

			t++;

			break;
		}
		}

		rand_bump();
	}

	return 0;
}

