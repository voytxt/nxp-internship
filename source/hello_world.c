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

int main(void) {
//    char ch;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals(); // uncomment PIT INIT if i want to use it in the future
    BOARD_InitDebugConsole();

    PRINTF("init done\n");

    lcd_init();

    lcd_goto(0, 0);
    lcd_puts("chess");
    lcd_goto(1, 0);
    lcd_puts("");

    long long t = 0;
    int prevX = 1;
    char ch = 32; // space

    while (1) {
    	int x = GPIO_PinRead(BOARD_ENC_A_GPIO, BOARD_ENC_A_PIN);
    	if (x != 1) PRINTF("ENC_A: %d\n", x);

    	int y = GPIO_PinRead(BOARD_ENC_SW_GPIO, BOARD_ENC_SW_PIN);
    	if (y != 1) PRINTF("ENC_SW: %d\n", y);

    	int z = GPIO_PinRead(BOARD_ENC_B_GPIO, BOARD_ENC_B_PIN);
    	if (z != 1) PRINTF("ENC_B: %d\n", z);

    	if (x && !prevX) {
    		lcd_goto(1, 0);
    		lcd_putc(ch);
    		ch++;
    	}

    	prevX = x;

    	if (t % 100000 == 0) {
    		t = 0;
//    		PRINTF("!");
    	}

    	if (t < 10000) {
//		if (1) {
    		int a = GPIO_PinRead(BOARD_SW1_EXT_GPIO, BOARD_SW1_EXT_PIN);
			int b = GPIO_PinRead(BOARD_SW2_EXT_GPIO, BOARD_SW2_EXT_PIN);
			int c = GPIO_PinRead(BOARD_SW3_EXT_GPIO, BOARD_SW3_EXT_PIN);

			setLed(a, b, c);
    	} else {
    		setLed(1, 1, 1);
    	}

    	t++;

//      PUTCHAR(GETCHAR());
    }

    return 0;
}

