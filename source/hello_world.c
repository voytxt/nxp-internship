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

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");

    while (1) {
//    	PUTCHAR(48 + GPIO_PinRead(BOARD_ENC_SW_GPIO, BOARD_ENC_SW_PIN));
        int on = GPIO_PinRead(BOARD_SW1_EXT_GPIO, BOARD_SW1_EXT_PIN);
        GPIO_PinWrite(BOARD_LED_G_GPIO, BOARD_LED_G_PIN, on);
//      ch = GETCHAR();
//      PUTCHAR(ch);
    }
}
