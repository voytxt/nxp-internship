#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "lcd.h"
#include "enc.h"

void setLed(int r, int g, int b) {
	GPIO_PinWrite(BOARD_LED_R_GPIO, BOARD_LED_R_PIN, r);
	GPIO_PinWrite(BOARD_LED_G_GPIO, BOARD_LED_G_PIN, g);
	GPIO_PinWrite(BOARD_LED_B_GPIO, BOARD_LED_B_PIN, b);
}

char ch = 32; // space
int pos = 3;

void update() {
	int enc_state = get_enc_state();

	if (enc_state) {
		ch += enc_state;

		lcd_goto(0, pos);
		lcd_putc(ch);

		// todo: do this in one string in some smart idiomatic C way

		lcd_goto(1, 0);
		lcd_puts("                ");

		lcd_goto(1, pos);
		lcd_putc('^');
	}
}

void PIT_CHANNEL_0_IRQHANDLER(void) {
  /* Reading all interrupt flags of status register */
  uint32_t intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0);
  PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0, intStatus);

  /* Place your code here */
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

    long long t = 0;

    while (1) {
//    	if (t % 10000 == 0 && !(enc_a && enc_b)) PRINTF("%d | %d\n", enc_a, enc_b);

    	if (t % 100000 == 0) {
    		t = 0;
//    		PRINTF("!");
    	}

//    	if (t < 10000) {
////		if (1) {
//    		int a = GPIO_PinRead(BOARD_SW1_EXT_GPIO, BOARD_SW1_EXT_PIN);
//			int b = GPIO_PinRead(BOARD_SW2_EXT_GPIO, BOARD_SW2_EXT_PIN);
//			int c = GPIO_PinRead(BOARD_SW3_EXT_GPIO, BOARD_SW3_EXT_PIN);
//
//			setLed(a, b, c);
//    	} else {
//    		setLed(1, 1, 1);
//    	}
    	setLed(0, 0, 0);

    	t++;

//      PUTCHAR(GETCHAR());
    }

    return 0;
}

