/**
 * @file main.c
 * @version 4.1.0
 *
 * @section License
 * Copyright (C) 2015-2016, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"
#include "digital_out.h"

static THRD_STACK(blink_task_stack, 256);

void* led_blink_task(void* arg_p){
    Digital_out LED(5);
    LED.init();
    LED.set_hi();

    while(1){
        /* Wait half a second. */
        thrd_sleep_us(500000);

        /* Toggle the LED on/off. */
        LED.toggle();
    }
}


int main()
{
    /* Start the system. */
    sys_start();

    /* Spawn led blink thread */
    thrd_spawn(led_blink_task,
                NULL,
                1,
                blink_task_stack,
                sizeof(blink_task_stack));

    while(1){
        thrd_sleep_ms(10000);
    }
    return (0);
}
