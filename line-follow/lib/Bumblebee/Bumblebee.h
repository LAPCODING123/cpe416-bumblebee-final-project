// Global defines
#pragma once

#include <stdint.h>
#include <Arduino.h>

typedef unsigned char u08;

#define sbi(a, b) (a) |= _BV(b)
#define cbi(a, b) (a) &= ~_BV(b)

#define LCD_E_PIN 4  // PC4
#define LCD_RS_PIN 7 // PF7
#define LCD_DATA_PORT PORTA

#define SW1_PIN 7        // PE7
#define LED0_PIN 0       // PG0
#define LED1_PIN 1       // PG1
#define USB_DETECT_PIN 2 // PG2
#define IR_PIN 0         // PD0
#define ACCEL_INT_PIN 1  // PD1

#define MOTOR0_EN_PIN 4   // PB4
#define MOTOR1_EN_PIN 7   // PB7
#define MOTOR0_DIR0_PIN 4 // PD4
#define MOTOR0_DIR1_PIN 5 // PD5
#define MOTOR1_DIR0_PIN 6 // PD6
#define MOTOR1_DIR1_PIN 7 // PD7

#define SERVO0_PIN 0 // PC0
#define SERVO1_PIN 1 // PC1
#define SERVO2_PIN 2 // PC2
#define SERVO3_PIN 3 // PF3

#define SDA_PIN 5
#define SCL_PIN 4
#define I2C_DDR DDRE
#define I2C_PORT PORTE
#define I2C_PIN PINE
#define SDA_HI I2C_DDR &= ~_BV(SDA_PIN); // make as input to set high
#define SCL_HI I2C_DDR &= ~_BV(SCL_PIN); // make as input to set high
#define SDA_LO               \
    I2C_DDR |= _BV(SDA_PIN); \
    I2C_PORT &= ~_BV(SDA_PIN); // set as output and write low
#define SCL_LO               \
    I2C_DDR |= _BV(SCL_PIN); \
    I2C_PORT &= ~_BV(SCL_PIN); // set as output and write low
#define I2C_DELAY 1
#define MMA8453_ADDR 0x1C
#define COMPASS_ADDR 0x1E

u08 digital(u08 num);
u08 analog(u08 num);
void print_string(const char *string);
void i2c_start(void);
void i2c_stop(void);
void unlock_bus(void);
void clock_scl();
void send_address(u08 addr, u08 reg, u08 read);
void write_register(u08 *data, u08 num);
void read_register(u08 addr, u08 *data, u08 num);

u08 get_btn(void);
void led_on(u08 num);
void led_off(u08 num);
void led(u08 num, u08 state);
void init(void);
void clear_screen(void);
void digital_dir(u08 num, u08 dir);
void digital_out(u08 num, u08 out);

void init_lcd();
void init_servo();
void init_motor();

void print_string(char *string);
void print_num(u16 number);
void lcd_cursor(uint8_t col, uint8_t row);
void init_scrolling(char *m);
void toggle_scrolling();

void test_motor(void);
void set_motor(u08 num, signed char speed);

void set_servo(u08 servo_num, u08 position);

void servo_isr(void);

void i2c_regwrite(u08 dev_addr, u08 address, u08 data);
u08 i2c_regread(u08 dev_addr, u08 address);
u08 get_accel_x();
u08 get_accel_y();
u08 get_accel_z();
