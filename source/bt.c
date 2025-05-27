#include "pin_mux.h"
#include "peripherals.h"

int prev = 0;

/**
 * @return 0 if no button was just pressed, otherwise 1, 2, 3, 4 corresponding to N, E, W, S
 */
int bt_get_state(void) {
	int curr = 0;

	if (!GPIO_PinRead(BOARD_BT_N_GPIO, BOARD_BT_N_PIN)) curr = 1;
	else if (!GPIO_PinRead(BOARD_BT_E_GPIO, BOARD_BT_E_PIN)) curr = 2;
	else if (!GPIO_PinRead(BOARD_BT_W_GPIO, BOARD_BT_W_PIN)) curr = 3;
	else if (!GPIO_PinRead(BOARD_BT_S_GPIO, BOARD_BT_S_PIN)) curr = 4;

	if (curr == prev) return 0;
	return prev = curr;
}
