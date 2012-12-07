#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "m128_hal.h"
#include "uart.h"
#include "cmd.h"
#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"

uint8_t cmp_pattern(uint8_t *p, uint8_t pattern, size_t size)
{
    uint8_t *p_end = (p + size);
    while(p < p_end) {
        if(*p != pattern) {
            printk("Pattern match failed at 0x%x [%x]\n", *p);
            return -1;
        }
        p++;
    }
    return 0;
}

//static struct system_settings sys_settings;

int main(void)
{
    //XMCRA |= (1<<SRE);
    //XMCRA |= (1<<SRW01) | (1<<SRW11);

    //struct rtc_time time;
    wdt_enable(WDTO_8S);
    STATUS_REGISTER |= (1<<STATUS_REGISTER_IT);
    uart_init();
    cmd_init();
    while(1)
    {
    //    _delay_ms(250);
        pending_cmd();
        wdt_reset();
    _delay_ms(400);
    }
//fatal:
    printk("Fatal error!\n");
    while(1);
    return 0;
}

