//
// Created by marci on 28.05.2019.
//

#include "lcd.h"
#include <main.h>
#include <logo.h>
#include <string.h>

extern SPI_HandleTypeDef hspi1;

// Funkcja pomocnicza
void spi_send(uint8_t byte) {
    HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
    //HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
}


void lcd_reset() {
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
}

void lcd_command(uint8_t cmd) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    spi_send(cmd);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

void lcd_data(const uint8_t *data, int size) {
    lcd_command(0x40 | 0x00);   //Zerowanie Y
    lcd_command(0x80 | 0x00);   //Zerowanie X
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < size; i++) { spi_send(data[i]); }
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

void lcd_symbol(const uint8_t *data, int size)
{
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < size; i++) {
        spi_send(data[i]);
    }
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}


void lcd_write(char st[])
{
    uint16_t n = strlen(st);
    uint16_t x_ = 0;
    while (x_ < n) {
        uint8_t ch[6];
        for (int i = 0; i < 6; i++) {
            ch[i] = ASCII[st[x_] - 0x20][i];
        }
        uint16_t s = sizeof(ch);
        lcd_symbol(ch, s);
        x_++;
    }
}
