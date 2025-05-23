#include "pin_mux.h"
#include "peripherals.h"
#include "fsl_debug_console.h"

int prev = 0;

int get_bt_state() {
	int curr = 0;

	if (!GPIO_PinRead(BOARD_BT_N_GPIO, BOARD_BT_N_PIN)) curr = 1;
	else if (!GPIO_PinRead(BOARD_BT_E_GPIO, BOARD_BT_E_PIN)) curr = 2;
	else if (!GPIO_PinRead(BOARD_BT_W_GPIO, BOARD_BT_W_PIN)) curr = 3;
	else if (!GPIO_PinRead(BOARD_BT_S_GPIO, BOARD_BT_S_PIN)) curr = 4;

//	PRINTF("%d - %d\n", prev, curr);

	if (curr == prev) return 0;

	prev = curr;
	return curr;

//	static uint16_t debounce  = 0xFFFF;
//	debounce <<= 1;
//	if (stiskle) debounce |= 0x0001;
//	if (debounce == 0x8000);
}
