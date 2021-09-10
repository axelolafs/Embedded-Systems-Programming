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
#include "digital_in.h"

static THRD_STACK(blink_task_stack, 256);
static THRD_STACK(button_task_stack, 256);
struct sem_t sem_button;

void* led_blink_task(void* arg_p){
    Digital_out LED(5);
    LED.init();

    while(1){
        /* Wait half a second. */
        // thrd_sleep_us(500000);

        /* Toggle the LED on/off. */
        sem_take(&sem_button, NULL);
        LED.toggle();
    }
}
void* button_read_task(void* arg_p){
    Digital_in BUTTON(0);
    BUTTON.init();
    bool stateInit;
    
    while(1){
        /* Wait 50 ms */
        stateInit = BUTTON.is_lo();
        thrd_sleep_ms(20);
        
        /* Read button push */
        if(BUTTON.is_lo() && (stateInit == false)){
            sem_give(&sem_button, 1);
        }
    }
}


int main()
{
    /* Start the system. */
    sys_start();
    sem_init(&sem_button, 0, 1);

    /* Spawn led blink thread */
    thrd_spawn(led_blink_task,
                NULL,
                0,
                blink_task_stack,
                sizeof(blink_task_stack));
    
    /* Spawn button read thread */
    thrd_spawn(button_read_task,
                NULL,
                1,
                button_task_stack,
                sizeof(button_task_stack));

    while(1){
        thrd_sleep_ms(10000);
    }
    return (0);
}


