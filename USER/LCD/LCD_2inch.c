/******************************************************************************/
#include "LCD_2inch.h"
#include <string.h>
/*******************************************************************************
function:
	Hardware reset
*******************************************************************************/
static void LCD_2IN_Reset(void)
{
	LCD_2IN_RST_1;
	DEV_Delay_ms(100);
	LCD_2IN_RST_0;
	DEV_Delay_ms(100);
	LCD_2IN_RST_1;
	DEV_Delay_ms(100);
}

/*******************************************************************************
function:
		Write data and commands
*******************************************************************************/
static void LCD_2IN_Write_Command(uint8_t data)		
{	
	LCD_2IN_CS_0;
	LCD_2IN_DC_0;
//	__disable_irq();
	DEV_SPI_WRITE(data);
//	__enable_irq();
//	LCD_2IN_CS_1;
}

static void LCD_2IN_WriteData_Byte(uint8_t data) 
{	
	LCD_2IN_CS_0;
	LCD_2IN_DC_1;
//	__disable_irq();
	DEV_SPI_WRITE(data);
//	__enable_irq();
	LCD_2IN_CS_1;
}  

static void LCD_2IN_WriteData_Word(uint16_t data)
{
	LCD_2IN_CS_0;					// 片选
	LCD_2IN_DC_1;					// 数据模式
	
	DEV_SPI_WRITE_WORD(data);
	
	LCD_2IN_CS_1;
}


/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
//void LCD_2IN_Init(void)
//{
//	LCD_2IN_Reset();

//	LCD_2IN_Write_Command(0x36);
//	LCD_2IN_WriteData_Byte(0xC0);

//	LCD_2IN_Write_Command(0x3A); 
//	LCD_2IN_WriteData_Byte(0x05);

//	LCD_2IN_Write_Command(0x21); 

//	LCD_2IN_Write_Command(0x2A);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0x01);
//	LCD_2IN_WriteData_Byte(0x3F);

//	LCD_2IN_Write_Command(0x2B);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0xEF);

//	LCD_2IN_Write_Command(0xB2);
//	LCD_2IN_WriteData_Byte(0x0C);
//	LCD_2IN_WriteData_Byte(0x0C);
//	LCD_2IN_WriteData_Byte(0x00);
//	LCD_2IN_WriteData_Byte(0x33);
//	LCD_2IN_WriteData_Byte(0x33);

//	LCD_2IN_Write_Command(0xB7);
//	LCD_2IN_WriteData_Byte(0x35); 

//	LCD_2IN_Write_Command(0xBB);
//	LCD_2IN_WriteData_Byte(0x1F);

//	LCD_2IN_Write_Command(0xC0);
//	LCD_2IN_WriteData_Byte(0x2C);

//	LCD_2IN_Write_Command(0xC2);
//	LCD_2IN_WriteData_Byte(0x01);

//	LCD_2IN_Write_Command(0xC3);
//	LCD_2IN_WriteData_Byte(0x12);   

//	LCD_2IN_Write_Command(0xC4);
//	LCD_2IN_WriteData_Byte(0x20);

//	LCD_2IN_Write_Command(0xC6);
//	LCD_2IN_WriteData_Byte(0x0F); 

//	LCD_2IN_Write_Command(0xD0);
//	LCD_2IN_WriteData_Byte(0xA4);
//	LCD_2IN_WriteData_Byte(0xA1);

//	LCD_2IN_Write_Command(0xE0);
//	LCD_2IN_WriteData_Byte(0xD0);
//	LCD_2IN_WriteData_Byte(0x08);
//	LCD_2IN_WriteData_Byte(0x11);
//	LCD_2IN_WriteData_Byte(0x08);
//	LCD_2IN_WriteData_Byte(0x0C);
//	LCD_2IN_WriteData_Byte(0x15);
//	LCD_2IN_WriteData_Byte(0x39);
//	LCD_2IN_WriteData_Byte(0x33);
//	LCD_2IN_WriteData_Byte(0x50);
//	LCD_2IN_WriteData_Byte(0x36);
//	LCD_2IN_WriteData_Byte(0x13);
//	LCD_2IN_WriteData_Byte(0x14);
//	LCD_2IN_WriteData_Byte(0x29);
//	LCD_2IN_WriteData_Byte(0x2D);

//	LCD_2IN_Write_Command(0xE1);
//	LCD_2IN_WriteData_Byte(0xD0);
//	LCD_2IN_WriteData_Byte(0x08);
//	LCD_2IN_WriteData_Byte(0x10);
//	LCD_2IN_WriteData_Byte(0x08);
//	LCD_2IN_WriteData_Byte(0x06);
//	LCD_2IN_WriteData_Byte(0x06);
//	LCD_2IN_WriteData_Byte(0x39);
//	LCD_2IN_WriteData_Byte(0x44);
//	LCD_2IN_WriteData_Byte(0x51);
//	LCD_2IN_WriteData_Byte(0x0B);
//	LCD_2IN_WriteData_Byte(0x16);
//	LCD_2IN_WriteData_Byte(0x14);
//	LCD_2IN_WriteData_Byte(0x2F);
//	LCD_2IN_WriteData_Byte(0x31);
//	LCD_2IN_Write_Command(0x21);

//	LCD_2IN_Write_Command(0x11);

//	LCD_2IN_Write_Command(0x29);
//}

/******************************************************************************
function:	Set the cursor position
parameter	:
	  Xstart: 	Start uint16_t x coordinate
	  Ystart:	Start uint16_t y coordinate
	  Xend  :	End uint16_t coordinates
	  Yend  :	End uint16_t coordinatesen
******************************************************************************/
void LCD_2IN_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t  Yend)
{
	uint16_t x_start = Xstart + X_SHIFT, x_end = Xend + X_SHIFT;
	uint16_t y_start = Ystart + Y_SHIFT, y_end = Yend + Y_SHIFT;
	
	LCD_2IN_Write_Command(0x2a);
	LCD_2IN_WriteData_Word(x_start);
	LCD_2IN_WriteData_Word(x_end - 1);

	LCD_2IN_Write_Command(0x2b);
	LCD_2IN_WriteData_Word(y_start);
	LCD_2IN_WriteData_Word(y_end - 1);
	
	LCD_2IN_Write_Command(0x2C);
}

///******************************************************************************
//function:	Settings window
//parameter	:
//	  Xstart: 	Start uint16_t x coordinate
//	  Ystart:	Start uint16_t y coordinate

//******************************************************************************/
//void LCD_2IN_SetCursor(uint16_t X, uint16_t Y)
//{ 
//	LCD_2IN_Write_Command(0x2a);
//	LCD_2IN_WriteData_Word(X);
//	LCD_2IN_WriteData_Word(X);

//	LCD_2IN_Write_Command(0x2b);
//	LCD_2IN_WriteData_Word(Y);
//	LCD_2IN_WriteData_Word(Y);
//	
//	LCD_2IN_Write_Command(0x2C);
//}

///******************************************************************************
//function:	Clear screen function, refresh the screen to a certain color
//parameter	:
//	  Color :		The color you want to clear all the screen
//******************************************************************************/
void LCD_2IN_Clear(uint16_t Color)
{
    uint16_t i;
	
    LCD_2IN_SetWindow(0, 0, LCD_2IN_WIDTH, LCD_2IN_HEIGHT);

	LCD_2IN_CS_0;					// 片选
	LCD_2IN_DC_1;					// 数据模式
	
	for(i = 0; i < LCD_2IN_WIDTH * LCD_2IN_HEIGHT; i++)
		DEV_SPI_WRITE_WORD(Color);
	
	LCD_2IN_CS_1;
}

///******************************************************************************
//function:	Refresh a certain area to the same color
//parameter	:
//	  Xstart: Start uint16_t x coordinate
//	  Ystart:	Start uint16_t y coordinate
//	  Xend  :	End uint16_t coordinates
//	  Yend  :	End uint16_t coordinates
//	  color :	Set the color
//******************************************************************************/
//void LCD_2IN_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,uint16_t color)
//{          
//	uint16_t i,j;
//	
//	LCD_2IN_SetWindow(Xstart, Ystart, Xend, Yend);
//	
//	LCD_2IN_CS_0;	//片选
//	LCD_2IN_DC_1;	//数据模式
//	
//	for (i = Ystart; i < Yend; i++)
//	{
//		for (j = Xstart; j < Xend; j++)
//		{							
//			DEV_SPI_WRITE_WORD(color);
//		}
//	}
//	
//	LCD_2IN_DC_0;	//命令模式
//	LCD_2IN_CS_1;
//}

///******************************************************************************
//function: Show a picture
//parameter	:
//		image: Picture buffer
//******************************************************************************/
//void LCD_2IN_Display(uint8_t *image)
//{
//    uint16_t i,j;
//	
//    LCD_2IN_SetWindow(0, 0, LCD_2IN_WIDTH, LCD_2IN_HEIGHT);

//	DEV_Digital_Write(DEV_DC_PIN, 1);
//	for (i = 0; i < LCD_2IN_WIDTH; i++)
//	{
//		for (j = 0; j < LCD_2IN_HEIGHT; j++)
//			LCD_2IN_WriteData_Word(*(image + i*LCD_2IN_WIDTH + j));
//	 }
//}

///******************************************************************************
//function: Draw a point
//parameter	:
//	    X	: 	Set the X coordinate
//	    Y	:	Set the Y coordinate
//	  Color :	Set the color
//******************************************************************************/
//void LCD_2IN_DrawPaint(uint16_t x, uint16_t y, uint16_t Color)
//{
//	LCD_2IN_SetCursor(x, y);
//	LCD_2IN_WriteData_Word(Color); 	    
//}

/*******************************************************************************
function:
	Setting backlight
parameter	:
	  value : Range 0~1000   Duty cycle is value/1000	
*******************************************************************************/
void LCD_2IN_SetBackLight(uint16_t Value)
{
	DEV_BL_PWM_OFF;

	DEV_Set_PWM(Value);
	
	if (Value)
		DEV_BL_PWM_ON;
}

/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
void LCD_2IN_Init(void)
{
	DEV_Module_Init();

	LCD_2IN_Reset();

	LCD_2IN_Write_Command(0x36);
	LCD_2IN_WriteData_Byte(0xC0);

	LCD_2IN_Write_Command(0x3A); 
	LCD_2IN_WriteData_Byte(0x05);

	LCD_2IN_Write_Command(0x21); 

	LCD_2IN_Write_Command(0x2A);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0x01);
	LCD_2IN_WriteData_Byte(0x3F);

	LCD_2IN_Write_Command(0x2B);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0xEF);

	LCD_2IN_Write_Command(0xB2);
	LCD_2IN_WriteData_Byte(0x0C);
	LCD_2IN_WriteData_Byte(0x0C);
	LCD_2IN_WriteData_Byte(0x00);
	LCD_2IN_WriteData_Byte(0x33);
	LCD_2IN_WriteData_Byte(0x33);

	LCD_2IN_Write_Command(0xB7);
	LCD_2IN_WriteData_Byte(0x35); 

	LCD_2IN_Write_Command(0xBB);
	LCD_2IN_WriteData_Byte(0x1F);

	LCD_2IN_Write_Command(0xC0);
	LCD_2IN_WriteData_Byte(0x2C);

	LCD_2IN_Write_Command(0xC2);
	LCD_2IN_WriteData_Byte(0x01);

	LCD_2IN_Write_Command(0xC3);
	LCD_2IN_WriteData_Byte(0x12);   

	LCD_2IN_Write_Command(0xC4);
	LCD_2IN_WriteData_Byte(0x20);

	LCD_2IN_Write_Command(0xC6);
	LCD_2IN_WriteData_Byte(0x0F); 

	LCD_2IN_Write_Command(0xD0);
	LCD_2IN_WriteData_Byte(0xA4);
	LCD_2IN_WriteData_Byte(0xA1);

	LCD_2IN_Write_Command(0xE0);
	LCD_2IN_WriteData_Byte(0xD0);
	LCD_2IN_WriteData_Byte(0x08);
	LCD_2IN_WriteData_Byte(0x11);
	LCD_2IN_WriteData_Byte(0x08);
	LCD_2IN_WriteData_Byte(0x0C);
	LCD_2IN_WriteData_Byte(0x15);
	LCD_2IN_WriteData_Byte(0x39);
	LCD_2IN_WriteData_Byte(0x33);
	LCD_2IN_WriteData_Byte(0x50);
	LCD_2IN_WriteData_Byte(0x36);
	LCD_2IN_WriteData_Byte(0x13);
	LCD_2IN_WriteData_Byte(0x14);
	LCD_2IN_WriteData_Byte(0x29);
	LCD_2IN_WriteData_Byte(0x2D);

	LCD_2IN_Write_Command(0xE1);
	LCD_2IN_WriteData_Byte(0xD0);
	LCD_2IN_WriteData_Byte(0x08);
	LCD_2IN_WriteData_Byte(0x10);
	LCD_2IN_WriteData_Byte(0x08);
	LCD_2IN_WriteData_Byte(0x06);
	LCD_2IN_WriteData_Byte(0x06);
	LCD_2IN_WriteData_Byte(0x39);
	LCD_2IN_WriteData_Byte(0x44);
	LCD_2IN_WriteData_Byte(0x51);
	LCD_2IN_WriteData_Byte(0x0B);
	LCD_2IN_WriteData_Byte(0x16);
	LCD_2IN_WriteData_Byte(0x14);
	LCD_2IN_WriteData_Byte(0x2F);
	LCD_2IN_WriteData_Byte(0x31);
	LCD_2IN_Write_Command(0x21);

	LCD_2IN_Write_Command(0x11);

	LCD_2IN_Write_Command(0x29);
	
//	LCD_2IN_Clear(0xFFFF);

	LCD_2IN_SetBackLight(BRIGHTNESS_LEVELS_100);
}
