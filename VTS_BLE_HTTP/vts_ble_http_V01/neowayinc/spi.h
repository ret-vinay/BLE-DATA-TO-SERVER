
#include "neoway_openplatform.h"

#define sck 27
#define cs 26
#define miso 29
#define mosi 28

void spi_config(void);
void spi_write(U8 buff);
U8 spi_read(void);
void clock_pulse(void);
void clock_pulse_with_no_api(void);
void spi_delay(void);
void set_spi_delay_count(unsigned char set_value);
//void cs_pin_config(void);