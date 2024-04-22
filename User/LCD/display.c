#include "display.h"
#include "LCD_2inch.h"

#define	PIC_SIZE_0		0
#define	PIC_SIZE_1		1
#define	PIC_SIZE_2		2
#define	PIC_SIZE_3		3
#define	PIC_WIDTH_H		4
#define	PIC_WIDTH_L		5
#define	PIC_HEIGHT_H	6
#define	PIC_HEIGHT_L	7
#define	PIC_START		8
#define PIC_ADD_OFFSET	8

uint8_t StringBuf[1024];

void ImageDisplay(const struct fal_partition *part, uint16_t xStart, uint16_t yStart)
{
//	uint16_t i			 	= 0;
	uint32_t read_add	 	= PIC_ADD_OFFSET;
	uint8_t  pic_buf1[960]	= {0};
	uint8_t	 pic_buf2[960] 	=	{0};
	uint8_t  *pic_buf		= 0;
	uint32_t PicSize 		= 0;
	uint16_t PicWidth 		= 0;
	uint16_t PicHeight 		= 0;
//	uint16_t OnceHeight 	= 0;
	uint16_t OnceReadMax 	= 0;
	bool	sw 				= 0;	
	uint32_t Tickstart;
	uint32_t Timeout = 1000;
	
	pic_buf = pic_buf1;
	/* 读取图片属性 */
	// 大小
	fal_partition_read(part,read_add,pic_buf,PIC_START);
	PicSize += pic_buf[PIC_SIZE_0];
	PicSize = PicSize<<8;
	PicSize += pic_buf[PIC_SIZE_1];
	PicSize = PicSize<<8;
	PicSize += pic_buf[PIC_SIZE_2];
	PicSize = PicSize<<8;
	PicSize += pic_buf[PIC_SIZE_3];
	// 宽度
	PicWidth += pic_buf[PIC_WIDTH_H];
	PicWidth = PicWidth<<8;
	PicWidth += pic_buf[PIC_WIDTH_L];
	
	// 高度
	PicHeight += pic_buf[PIC_HEIGHT_H];
	PicHeight = PicHeight<<8;
	PicHeight += pic_buf[PIC_HEIGHT_L];
	
	if ( (PicSize % (PicWidth<<1) ) != 0 )		// 存在不完整的行，图片不是方块形
	{
		Dsy_log_err("The picture size error! size is: (%d)", PicSize);
		return;
	}
	else if ((xStart+PicWidth) > LCD_2IN_WIDTH)	//宽度过大
	{
		Dsy_log_err("The picture width error! width is: (%d)", (xStart+PicWidth) );
		return;
	}
	else if ((yStart+PicHeight) > LCD_2IN_HEIGHT)	//高度过大
	{
		Dsy_log_err("The picture size height! height is: (%d)", (yStart+PicHeight));
		return;
	}
	
	OnceReadMax = sizeof(pic_buf1);
	
	// 设置窗口大小
	LCD_2IN_SetWindow(xStart, yStart, xStart+PicWidth, yStart+PicHeight);
	LCD_2IN_CS_0;	// 片选
	LCD_2IN_DC_1;	// 数据模式
																										 /* 偏移 PIC_START */
	for (read_add = PIC_START+PIC_ADD_OFFSET; read_add < (PicSize+PIC_START); read_add += OnceReadMax) 
	{
		// 切换buf，缓存数据
		if(sw)	pic_buf = pic_buf1;
		else	pic_buf = pic_buf2;
		sw = !sw;
				
		if ( (read_add+OnceReadMax) > (PicSize+PIC_START))
		{
			OnceReadMax = (PicSize+PIC_START) - read_add;
		}
			
		fal_partition_read(part,read_add,pic_buf,OnceReadMax);
			
	//	while ( HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY );	// 等待空闲
		Tickstart = HAL_GetTick();
		while ( HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY )	// 等待空闲
		{
			if (((HAL_GetTick() - Tickstart) > Timeout) )	break;
		}
		HAL_SPI_Transmit_DMA(DEV_LCD_SPI_PORT, (uint8_t*)pic_buf, OnceReadMax);
		
	}
	
	Tickstart = HAL_GetTick();
	while ( HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY )	// 等待空闲
	{
		if (((HAL_GetTick() - Tickstart) > Timeout) )	break;
	}
	LCD_2IN_CS_1;	// 解除片选
}

/******************************************************************************
function:	Show English characters
parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void Char_Display(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                    sFONT* Font, UWORD Color_Background, UWORD Color_Foreground)
{
    UWORD Page, Column;
	
	uint16_t length = 0;
	uint16_t i;
	uint8_t tmp[1024] = {0};
	uint32_t Tickstart;
	uint32_t Timeout = 1000;
    if (Xpoint > LCD_2IN_WIDTH || Ypoint > LCD_2IN_HEIGHT)
	{
        Debug("Paint_DrawChar Input exceeds the normal display range\r\n");
        return;
    }
	
    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page ++ ) 
	{
        for (Column = 0; Column < Font->Width; Column ++ )
		{
            if (*ptr & (0x80 >> (Column % 8)))
			{
			//	Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
				tmp[length] = 0xff&(Color_Foreground>>8);
				tmp[length+1] = 0xff&(Color_Foreground);
			} else 
			{
			//	Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Background);
				tmp[length] = 0xff&(Color_Background>>8);
				tmp[length+1] = 0xff&(Color_Background);
			}
			length += 2;
            //One pixel is 8 bits
            if (Column % 8 == 7)
                ptr++;
        }// Write a line
        if (Font->Width % 8 != 0)
            ptr++;
    }// Write all
	
	for(i=0;i<length;i++) StringBuf[i] = tmp[i];
	
	Tickstart = HAL_GetTick();
	while ( HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY )	// 等待空闲
	{
		if (((HAL_GetTick() - Tickstart) > Timeout) )	break;
	}
		
	// 设置窗口大小
	LCD_2IN_SetWindow(Xpoint, Ypoint, Xpoint+(Font->Width), Ypoint+(Font->Height));
	LCD_2IN_CS_0;	// 片选
	LCD_2IN_DC_1;	// 数据模式
	
	Tickstart = HAL_GetTick();
	while ( HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY )	// 等待空闲
	{
		if (((HAL_GetTick() - Tickstart) > Timeout) )	break;
	}
	HAL_SPI_Transmit_DMA(DEV_LCD_SPI_PORT, (uint8_t*)StringBuf, length);
}
