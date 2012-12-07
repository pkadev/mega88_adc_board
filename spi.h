#ifndef SPI_H_
#define SPI_H_
#define MAX1168_CS_DDR DDRD
#define MOSI PB3
#define SCK  PB5
#define MAX1168_CS_PIN PD7
#define DDR_SPI DDRB 
#define MAX1168_CS_PORT PORTD
#define CS_LOW()             (MAX1168_CS_PORT &= ~(1<<MAX1168_CS_PIN))
#define CS_HIGH()            (MAX1168_CS_PORT |= (1<<MAX1168_CS_PIN))
#define SPI_WAIT()  while(!(SPSR & (1<<SPIF)))
#define SPI_DUMMY_BYTE 0xff
#define EOC PB0
#define DSEL PB2
void max1168_init(void);

void max1168_write_reg(uint8_t val);
#endif
