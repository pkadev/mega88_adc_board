#include <string.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "m128_hal.h"
#include "cmd.h"
#include "uart.h"


int (*pt2Function)(void) = 0;
static uint8_t initialized = 0;
static cmd_input_t cmd_input;
static void find_service(const char * service);

/*
 * Functions that can be registered
 */
static int volt_out(void);
static int reboot(void);

#define CHAR_BACKSPACE 0x7F

ISR(USART_RX_vect)
{
    char c = UART_DATA_REG;
    if(isalnum(c) || c == 0x0D || c == ' ')
    {
        if (c == 0x0D) {
            c = 0x0;
        }
        cmd_input.buffer[cmd_input.pos] = c;
        cmd_input.pos++;
    } else if (c == CHAR_BACKSPACE) {
        cmd_input.pos--;
       // printk("char: %i\n", c);
    }
}


void cmd_init(void)
{
    memset(cmd_input.buffer, 0, CMD_INPUT_BUFFER_SIZE);
    cmd_input.pos = 0;
    printk("Cmd initialized\n");
    initialized = 1;
}

void pending_cmd(void)
{
    if(initialized == 1)
    {
        if (cmd_input.pos != 0 )
        {
            if (cmd_input.buffer[cmd_input.pos-1] == 0x0 && cmd_input.pos > 1)
            {
                find_service(cmd_input.buffer);

                if( pt2Function != 0) {
                    pt2Function();
                    pt2Function = 0;
                } else {
                    printk("%s not found\n", cmd_input.buffer);
                }
                memset(cmd_input.buffer, 0, CMD_INPUT_BUFFER_SIZE);
                cmd_input.pos = 0;
            }
        }
    }
}

static void find_service(const char * service)
{
    if (strcmp(service, "volt_out") == 0)
        pt2Function = volt_out;
    if (strcmp(service, "reboot") == 0)
        pt2Function = reboot;

}

/*
 * Functions that can be registered
 */
static int volt_out(void)
{
    printk("Volt: 5.01V\n");
    return 0;
}


static int reboot(void)
{
    printk("Rebooting...\n");
    wdt_enable(WDTO_250MS);

    /* Wait for WD reset */
    while(1)
        ;
    return 0;
}
