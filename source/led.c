#include "peripherals.h"
#include "pin_mux.h"

void set_led(int r, int g, int b) {
	GPIO_PinWrite(BOARD_LED_R_GPIO, BOARD_LED_R_PIN, r);
	GPIO_PinWrite(BOARD_LED_G_GPIO, BOARD_LED_G_PIN, g);
	GPIO_PinWrite(BOARD_LED_B_GPIO, BOARD_LED_B_PIN, b);
}
