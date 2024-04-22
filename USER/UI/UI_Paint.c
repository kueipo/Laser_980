/**
 * @file UI_Paint.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "UI_Paint.h"
#include "FT5466/FT5466.h"
#include "main.h"
#include "DEV_Config.h"
#include "LCD_2inch.h"
#include "fonts.h"

/*********************
 *      DEFINES
 *********************/
#define LCD_WIDTH    240
#define LCD_HEIGHT   240

/**********************
 *      TYPEDEFS
 **********************/
 
 /**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
 
 /******************************************************************************
function:	Display the string
parameter:
    Xstart           ：X coordinate
    Ystart           ：Y coordinate
    pString          ：The first address of the English string to be displayed
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void UI_DrawString_EN(uint16_t Xstart, uint16_t Ystart, const char *pString,
                         sFONT *Font, uint16_t Color_Background, uint16_t Color_Foreground)
{
    uint16_t Xpoint = Xstart;
    uint16_t Ypoint = Ystart;

    if (Xstart > LCD_WIDTH || Ystart > LCD_HEIGHT)
    {
        Debug("Paint_DrawString_EN Input exceeds the normal display range\r\n");
        return;
    }

    while (*pString != '\0')
    {
        // if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
        if ((Xpoint + Font->Width) > LCD_WIDTH)
        {
            Xpoint = Xstart;
            Ypoint += Font->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if ((Ypoint + Font->Height) > LCD_HEIGHT)
        {
            Xpoint = Xstart;
            Ypoint = Ystart;
        }
        Char_Display(Xpoint, Ypoint, *pString, Font, Color_Background, Color_Foreground);

        // The next character of the address
        pString++;

        // The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}

/******************************************************************************
function:	Display nummber
parameter:
    Xstart           ：X coordinate
    Ystart           : Y coordinate
    Nummber          : The number displayed
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
#define ARRAY_LEN 16
void UI_Paint_DrawNum(uint16_t Xpoint, uint16_t Ypoint, int32_t Nummber,
                   sFONT *Font, uint16_t Color_Background, uint16_t Color_Foreground)
{

    int16_t Num_Bit = 0, Str_Bit = 0;
    uint8_t Str_Array[ARRAY_LEN] = {0}, Num_Array[ARRAY_LEN] = {0};
    uint8_t *pStr = Str_Array;

    if (Xpoint > LCD_WIDTH || Ypoint > LCD_HEIGHT)
    {
        Debug("Paint_DisNum Input exceeds the normal display range\r\n");
        return;
    }

    // Converts a number to a string
    while (Nummber)
    {
        Num_Array[Num_Bit] = Nummber % 10 + '0';
        Num_Bit++;
        Nummber /= 10;
    }

    // The string is inverted
    while (Num_Bit > 0)
    {
        Str_Array[Str_Bit] = Num_Array[Num_Bit - 1];
        Str_Bit++;
        Num_Bit--;
    }

    // 避免数字为0时，显示为空
    if (Str_Array[0] == 0)
        Str_Array[0] = '0';

    // show
    UI_DrawString_EN(Xpoint, Ypoint, (const char *)pStr, Font, Color_Background, Color_Foreground);
}

/******************************************************************************
function:	Refresh a certain area to the same color
parameter	:
	  Xstart: Start uint16_t x coordinate
	  Ystart:	Start uint16_t y coordinate
	  Xend  :	End uint16_t coordinates
	  Yend  :	End uint16_t coordinates
	  color :	Set the color
******************************************************************************/
void UI_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,uint16_t color)
{          
	uint16_t i,j;

	LCD_2IN_SetWindow(Xstart, Ystart, Xend, Yend);

	LCD_2IN_CS_0;	//片选
	LCD_2IN_DC_1;	//数据模式
	for (i = Ystart; i < Yend; i++)
	{
		for (j = Xstart; j < Xend; j++)
		{
			DEV_SPI_WRITE_WORD(color);
		}
	}

	LCD_2IN_DC_0;	//命令模式
	LCD_2IN_CS_1;	
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
