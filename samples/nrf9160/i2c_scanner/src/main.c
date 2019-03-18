#include <nrf9160.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <i2c.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define I2C_ACCEL_WRITE_ADDR 0x32
#define I2C_ACCEL_READ_ADDR 0x33

struct device * i2c_accel;
uint8_t WhoAmI = 0u;

uint8_t init_accelerometer(){
        i2c_accel = device_get_binding("I2C_2");
        if (!i2c_accel) {
		printk("error\r\n");
                return -1;
	} else  {
                i2c_configure(i2c_accel, I2C_SPEED_SET(I2C_SPEED_STANDARD));
                return 0;
        }
}

void main(void)
{
        printk("Hello, World!\r\n");
        init_accelerometer();

	while (1) {
                printk("loop head\r\n");

                if (i2c_reg_read_byte(i2c_accel, I2C_ACCEL_READ_ADDR, 0x0F, WhoAmI) != 0) {
                        printk("Error on i2c_read()\n");
                }
                printk("WhoAmI = %u\r\n", WhoAmI);
                printk("enter sleep\r\n");
                k_sleep(1000);
	}
}


