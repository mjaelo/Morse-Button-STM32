//
// Created by marci on 28.05.2019.
//

#ifndef WYSW2_DISPLAY_H
#define WYSW2_DISPLAY_H

#include <sched.h>

void spi_send(uint8_t byte);

void lcd_reset();

void lcd_command(uint8_t cmd);

void lcd_data(const uint8_t *data, int size);

void lcd_symbol(const uint8_t *data, int size);

void lcd_write(char st[]);

#endif //WYSW2_DISPLAY_H
