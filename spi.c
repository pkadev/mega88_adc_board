#include "spi.h"
void max1168_init(void)
{
    /* Set MOSI and SCK output */
    DDR_SPI |= (1<<MOSI) | (1<<SCK);
    DDR_SPI |= (1<<DSEL);
    PORTB |= (1<<DSEL);
    /* CS is output */
    MAX1168_CS_DDR |= (1<<MAX1168_CS_PIN);
    /* SPI SS pin as output to aviod slave mode */
    DDRB |= (1<<PB0);

    /*
     * Enable SPI, Master, set clock rate.
     * ds3234 can run in 4MHz max
     */
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPHA);
    SPCR |= (1<<SPR0) | (1<<SPR1);
    CS_HIGH();
}
static uint8_t max1168_xfer_byte(uint8_t tx)
{
#define RETRIES 255

    uint8_t val;
    SPDR = tx;
    SPI_WAIT();
    val = SPDR;
    return val;
}


void max1168_write_reg(uint8_t val)
{
    CS_LOW();
    max1168_xfer_byte(0x8e);
    SPI_WAIT();
    max1168_xfer_byte(val);
    CS_HIGH();
}
uint8_t max1168_read_reg(uint8_t reg)
{
    uint8_t val = 0;

    CS_LOW();
    val = max1168_xfer_byte(0x06);
    val = max1168_xfer_byte(SPI_DUMMY_BYTE);
    val = max1168_xfer_byte(SPI_DUMMY_BYTE);
    CS_HIGH();
    return val;
}
