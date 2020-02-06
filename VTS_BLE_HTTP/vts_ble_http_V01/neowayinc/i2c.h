
#include "neoway_openplatform.h"

#define sda 44
#define scl 43
#define clk_high_time 10
#define clk_low_time 10

void i2c_pin_config(void);
void i2c_start(void);
void i2c_stop(void);
U8 i2c_tx(unsigned char d);
U8 i2c_rx(char ack);
void i2c_read(U8 read_adr,char* buf);
void i2c_write(U8 write_adr,U8 write_value);