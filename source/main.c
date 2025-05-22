/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"
#include "lcd.h"


void setLed(int r, int g, int b) {
	GPIO_PinWrite(BOARD_LED_R_GPIO, BOARD_LED_R_PIN, r);
	GPIO_PinWrite(BOARD_LED_G_GPIO, BOARD_LED_G_PIN, g);
	GPIO_PinWrite(BOARD_LED_B_GPIO, BOARD_LED_B_PIN, b);
}

void disp() {
	static char ch = 32; // space
	static int prev_enc_a = 1;
	static int prev_enc_b = 1;

	// a = 0 if rotating, 1 if still
	// b = 0 if moving & closer to CCW step, 1 if moving & closer to CW step or if still
	int enc_a = GPIO_PinRead(BOARD_ENC_A_GPIO, BOARD_ENC_A_PIN);
	int enc_b = GPIO_PinRead(BOARD_ENC_B_GPIO, BOARD_ENC_B_PIN);

	if (prev_enc_a == 0 && enc_a == 1) { // have we _just_ finished moving?
		int dir = prev_enc_b;

		lcd_goto(1, 0);

		ch += prev_enc_b ? 1 : -1;
		lcd_putc(ch);
	}

	prev_enc_a = enc_a;
	prev_enc_b = enc_b;
}

void PIT_CHANNEL_0_IRQHANDLER(void) {
  uint32_t intStatus;
  /* Reading all interrupt flags of status register */
  intStatus = PIT_GetStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0);
  PIT_ClearStatusFlags(PIT_PERIPHERAL, PIT_CHANNEL_0, intStatus);

  /* Place your code here */
  disp();

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

int main(void) {
//    char ch;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    PRINTF("init done\n");

    lcd_init();

    lcd_goto(0, 0);
    lcd_puts("cba");
    lcd_goto(1, 0);
    lcd_puts("");

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

