#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "m128_hal.h"
#include "uart.h"
#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"
#include "max1168.h"


int main(void)
{
    uint16_t i = 20;

    _delay_ms(2500);
    DDRD |= (1<<PD2);

    uart_init();
    STATUS_REGISTER |= (1<<STATUS_REGISTER_IT);


    while(i--)
    {
        //uint16_t val = max1168_mean(0, 3);
        //printk("reg: %u\n", val);
        uint16_t val = max1168_read_adc(SPI_DUMMY_BYTE, CLK_EXTERNAL, MODE_8BIT);
        printk("reg: %u\n", val);
    }

    printk("Conversion Completed!\n");
    while(1);
    return 0;
}

