#include "display.h"
#include "LCD_2inch.h"

uint8_t StringBuf[1024];

#define IMG_WIDTH_H 2
#define IMG_WIDTH_L 3
#define IMG_HEIGHT_H 4
#define IMG_HEIGHT_L 5
#define IMG_SIZE_LENGTH 8
#define IMG_ADD_OFFSET 4
#define IMG_ADD (IMG_ADD_OFFSET + IMG_SIZE_LENGTH)

void ImageDisplay(const char *partindex, uint16_t xStart, uint16_t yStart)
{
	uint32_t read_add = IMG_ADD_OFFSET;
	uint8_t pic_buf1[960] = {0};
	uint8_t pic_buf2[960] = {0};
	uint8_t *pic_buf = 0;
	uint32_t PicSize = 0;
	uint16_t PicWidth = 0;
	uint16_t PicHeight = 0;
	/*	uint16_t OnceHeight = 0;	*/
	uint16_t OnceReadMax = 0;
	bool sw = false;
	uint32_t Tickstart;
	uint32_t Timeout = 1000;

	const struct fal_partition *part = fal_partition_find(partindex);

	pic_buf = pic_buf1;

	/* Read Picture Properties */
	fal_partition_read(part, read_add, pic_buf, IMG_SIZE_LENGTH);

	read_add += IMG_SIZE_LENGTH;

	/* width */
	PicWidth += pic_buf[IMG_WIDTH_H];
	PicWidth = PicWidth << 8;
	PicWidth += pic_buf[IMG_WIDTH_L];

	/* height */
	PicHeight += pic_buf[IMG_HEIGHT_H];
	PicHeight = PicHeight << 8;
	PicHeight += pic_buf[IMG_HEIGHT_L];

	/* file size */
	PicSize = PicWidth * PicHeight * 2; // *2 ：16bit

//	if ((PicSize % (PicWidth << 1)) != 0) /* 存在不完整的行，图片不是方块形 */
//	{
//		Dsy_log_err("The picture size error! size is: (%d)", PicSize);
//		return;
//	}
	if ((xStart + PicWidth) > LCD_2IN_WIDTH) /* 宽度过大 */
	{
		Dsy_log_err("The picture width error! width is: (%d)", (xStart + PicWidth));
		return;
	}
	else if ((yStart + PicHeight) > LCD_2IN_HEIGHT) /* 高度过大 */
	{
		Dsy_log_err("The picture size height! height is: (%d)", (yStart + PicHeight));
		return;
	}

	OnceReadMax = sizeof(pic_buf1);

	/* Settings window */
	LCD_2IN_SetWindow(xStart, yStart, xStart + PicWidth, yStart + PicHeight);

	LCD_2IN_CS_0; /* CS */
	LCD_2IN_DC_1; /* DATA */

	/* PIC_START */
	for (; read_add < (PicSize + IMG_ADD); read_add += OnceReadMax)
	{
		/* Switch cache */
		if (sw)
			pic_buf = pic_buf1;
		else
			pic_buf = pic_buf2;
		sw = !sw;

		/* Last frame */
		if ((read_add + OnceReadMax) > (PicSize + IMG_ADD))
			OnceReadMax = (PicSize + IMG_ADD) - read_add;

		fal_partition_read(part, read_add, pic_buf, OnceReadMax);

		DEV_SPI_WRite_String(pic_buf, OnceReadMax);
	}

	Tickstart = HAL_GetTick();
	while (HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY) /* wait end */
	{
		if (((HAL_GetTick() - Tickstart) > Timeout))
		{
			HAL_SPI_Abort(DEV_LCD_SPI_PORT); /* Abort */
			break;
		}
	}
	LCD_2IN_CS_1; /* CS */
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
void Char_Display(uint16_t Xpoint, uint16_t Ypoint, const char Acsii_Char,
				  sFONT *Font, uint16_t Color_Background, uint16_t Color_Foreground)
{
	uint16_t Page, Column;

	uint16_t length = 0;
	uint16_t i;
	uint8_t tmp[1024] = {0};
	uint32_t Tickstart;
	uint32_t Timeout = 500;
	if (Xpoint > LCD_2IN_WIDTH || Ypoint > LCD_2IN_HEIGHT)
	{
		Debug("Paint_DrawChar Input exceeds the normal display range\r\n");
		return;
	}

	uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
	const unsigned char *ptr = &Font->table[Char_Offset];

	for (Page = 0; Page < Font->Height; Page++)
	{
		for (Column = 0; Column < Font->Width; Column++)
		{
			if (*ptr & (0x80 >> (Column % 8)))
			{
				//	Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
				tmp[length] = 0xff & (Color_Foreground >> 8);
				tmp[length + 1] = 0xff & (Color_Foreground);
			}
			else
			{
				//	Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Background);
				tmp[length] = 0xff & (Color_Background >> 8);
				tmp[length + 1] = 0xff & (Color_Background);
			}
			length += 2;
			/* One pixel is 8 bits */
			if (Column % 8 == 7)
				ptr++;
		} /* Write a line */
		if (Font->Width % 8 != 0)
			ptr++;
	} /* Write all */

	for (i = 0; i < length; i++)
		StringBuf[i] = tmp[i];

	Tickstart = HAL_GetTick();
	while (HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY)
	{
		if (((HAL_GetTick() - Tickstart) > Timeout))
		{
			HAL_SPI_Abort(DEV_LCD_SPI_PORT);
			break;
		}
	}
	
//	LCD_2IN_CS_1; /* CS */
	LCD_2IN_SetWindow(Xpoint, Ypoint, Xpoint + (Font->Width), Ypoint + (Font->Height));
	LCD_2IN_CS_0;
	LCD_2IN_DC_1;

//	Tickstart = HAL_GetTick();
//	while (HAL_SPI_GetState(DEV_LCD_SPI_PORT) != HAL_SPI_STATE_READY)
//	{
//		if (((HAL_GetTick() - Tickstart) > Timeout))
//			HAL_SPI_Abort(DEV_LCD_SPI_PORT);
//		break;
//	}

	HAL_SPI_Transmit_DMA(DEV_LCD_SPI_PORT, (uint8_t *)StringBuf, length);
}
