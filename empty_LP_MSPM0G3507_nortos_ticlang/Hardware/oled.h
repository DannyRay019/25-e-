#ifndef __OLED_H
#define __OLED_H
#include "ti_msp_dl_config.h"

#define OLED_SCL OLED_OLED_SCL_PIN
#define OLED_SDA OLED_OLED_SDA_PIN

 
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, char chr);
void OLED_ShowString(uint8_t x, uint8_t y, const char *str);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);


#endif