// encoder
// a = 0 if rotating, 1 if still
// b = 0 if moving & closer to CCW step, 1 if moving & closer to CW step or if still

#include "pin_mux.h"
#include "peripherals.h"

int prev_a = 1;
int prev_b = 1;

/**
 * @return 0 if nothing notable happen, 1 if encoder just got rotated CW, -1 if CCW
 */
int enc_get_state(void) {
	int a = GPIO_PinRead(BOARD_ENC_A_GPIO, BOARD_ENC_A_PIN);
	int b = GPIO_PinRead(BOARD_ENC_B_GPIO, BOARD_ENC_B_PIN);

	int dir = 0;

	// if we have just finished rotating, it means that the state just before this had the correct b value
	if (prev_a == 0 && a == 1) {
		dir += prev_b ? 1 : -1;
	}

	prev_a = a;
	prev_b = b;

	return dir;
}

int prev_sw = 0;

int enc_sw_get_state(void) {
	int sw = !GPIO_PinRead(BOARD_ENC_SW_GPIO, BOARD_ENC_SW_PIN);

	int state = 0;

	if (prev_sw == 0 && sw == 1) {
		state = 1;
	}

	prev_sw = sw;

	return state;
}
