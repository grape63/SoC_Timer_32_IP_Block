/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/******************************************************************************
* Copyright (C) 2025 Conner Davis
* SPDX-License-Identifier: MIT
*
* This file is part of SoC_Timer_32_IP_Block project, distributed under the MIT license
* see LICENSE file in the project root for full license information.
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
 
 
 
 
#include <stdio.h>
#include <xgpio_l.h>
#include "platform.h"
#include "xgpio.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
 
//get the base address for the my_timer_0 module
int *baseaddr_p = (int *)XPAR_MY_TIMER_0_BASEADDR;
//my_timer_0's registers:      usage:
//reg0 at *(baseaddr_p+0)      din[31:0]
//reg1 at *(baseaddr_p+1)      dout[31:0]
//reg2 at *(baseaddr_p+2)      unused[31:5] , reset[4] , addr[3:2], rden[1], wren[0]                         
//reg3 at *(baseaddr_p+3)      unused[31:0]

int main()
{
    init_platform();
    print("Hello World\n\r");
 
    // Initialize the GPIO module.
    int timer_value;
    XGpio xgpio;

    if (XGpio_Initialize(&xgpio, XPAR_XGPIO_0_BASEADDR) != XST_SUCCESS) {
        print("Error configuring GPIO.\r\n");
    }

    // Configure the LED's (channel 1) as outputs (0s). 
    XGpio_SetDataDirection(&xgpio, 1, 0);
//  XGpio_SetDataDirection(reference to xgpio module, channel, bit mask to set as inputs/outputs)

    //set LED values to the output from the my_timer_0 module
    XGpio_DiscreteWrite(&xgpio, 1, *(baseaddr_p+1));

    // Print output value of my_timer_0 to the console.
    xil_printf("Read : 0x%08x \n\r", *(baseaddr_p+1));
    // Print the LED values to console. 
    //value of LEDs should equal value of my_timer_0 dout[15:0] (which is value in register 1)
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    
    //sleep for 3 to allow user time to observe LED's
    sleep(3);

    //set my_timer_0's din to 0
    *(baseaddr_p+0) = 0x00000000;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+0));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    
    // set my_timer_0's register 2 to 2 (reset=0, addr=00, rden=1, wren=0).
    *(baseaddr_p+2) = 0x00000002;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    //sleep for 3 to allow user time to observe LED's
    sleep(3);

    // set my_timer_0's register 2 to 6 (reset=0, addr=01, rden=1, wren=0).
    *(baseaddr_p+2) = 0x00000006;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    //sleep for 3 to allow user time to observe LED's
    sleep(3);

    // set my_timer_0's register 2 to A (reset=0, addr=10, rden=1, wren=0).
    *(baseaddr_p+2) = 0x0000000A;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    // set my_timer_0's register 2 to E (reset=0, addr=11, rden=1, wren=0).
    *(baseaddr_p+2) = 0x0000000E;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    // set my_timer_0's register 2 to 2 (reset=0, addr=00, rden=1, wren=0).
    *(baseaddr_p+2) = 0x00000002;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    //output timer value a few times to show it incrementing, then verify reset function
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));

    // set my_timer_0's register 2 to 2 (reset=1, addr=00, rden=1, wren=0).
    *(baseaddr_p+2) = 0x00000012;
    xil_printf("Wrote: 0x%08x \n\r", *(baseaddr_p+2));

    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));


    // set my_timer_0's register 2 to 2 (reset=0, addr=00, rden=1, wren=0).
    *(baseaddr_p+2) = 0x00000002;
    //set timer_value to my_timer_0's register 1 (dout), then output.
    timer_value = *(baseaddr_p+1);
    XGpio_DiscreteWrite(&xgpio, 1, timer_value);
    xil_printf("Read : 0x%08x \n\r", timer_value);
    xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));


    while (1) {
        timer_value = *(baseaddr_p+1);
        // XGpio_DiscreteWrite(&xgpio, 1, timer_value);
        // xil_printf("Read : 0x%08x \n\r", timer_value);
        // xil_printf("LEDs: 0x%X\r\n", XGpio_DiscreteRead(&xgpio, 1));
    }
 
    cleanup_platform();
    return 0;
}