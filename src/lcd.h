#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define SCREEN_WIDTH  (256) //160;
#define SCREEN_HEIGHT (256) //144;


void lcd_init(void);
void lcd_set_pixel(uint8_t x, uint8_t y, uint8_t colour);
void lcd_test_line(void);
void lcd_refresh(void);
void lcd_close(void);

#endif //LCD_H
