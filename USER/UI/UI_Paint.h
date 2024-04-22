/**
 * @file UI_Paint.h
 *
 */

#ifndef UI_PAINT_H
#define UI_PAINT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "display.h"
/*********************
 *      DEFINES
 *********************/
/**
 * image color
**/

#define WHITE		0xFFFF
#define BLACK		0x0000	  
#define BLUE 		0x001F  
#define BRED 		0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED  		0xF800
#define MAGENTA		0xF81F
#define GREEN		0x07E0
#define CYAN 		0x7FFF
#define YELLOW		0xFFE0
#define BROWN		0XBC40 
#define BRRED		0XFC07 
#define GRAY 		0X8430 
#define DARKBLUE	0X01CF	
#define LIGHTBLUE	0X7D7C	 
#define GRAYBLUE    0X5458 
#define LIGHTGREEN  0X841F 
#define LGRAY 		0XC618 
#define LGRAYBLUE   0XA651
#define LBBLUE      0X2B12 

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void UI_DrawString_EN(uint16_t Xstart, uint16_t Ystart, const char *pString,
                         sFONT *Font, uint16_t Color_Background, uint16_t Color_Foreground);
void UI_Paint_DrawNum(uint16_t Xpoint, uint16_t Ypoint, int32_t Nummber,
                   sFONT *Font, uint16_t Color_Background, uint16_t Color_Foreground);
void UI_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,uint16_t color);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UI_PAINT_H */
