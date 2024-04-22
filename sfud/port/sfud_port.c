/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2018, zylx, <qgyhd1234@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2018-11-23
 */

#include <sfud/INC/sfud.h>
#include <stdarg.h>
#include <stdio.h>
#include <stm32F0xx_hal.h>
#include <stm32F0xx_hal_gpio.h>
#include <string.h>
#include "spi.h"

#define ENABLE_DMA_MODE	0
#define ENABLE_INTERRUPT_MODE	0
#define	SFUD_FLASH_SPI_PORT 	&hspi2
#define DLY 2000

void sfud_log_info(const char *format, ...);
sfud_err qspi_send_then_recv(const void *send_buf, size_t send_length, void *recv_buf, size_t recv_length);

typedef struct
{
	SPI_HandleTypeDef *spix;
	GPIO_TypeDef *cs_gpiox;
	uint16_t cs_gpio_pin;
	uint8_t tr_flg;
} spi_user_data, *spi_user_data_t;

#if 1
static char log_buf[256];
#endif
void sfud_log_debug(const char *file, const long line, const char *format, ...);

static void spi_lock(const sfud_spi *spi)
{
//	__disable_irq();
//	Disable_Irq(true);
}

static void spi_unlock(const sfud_spi *spi)
{
//	__enable_irq();
//	Disable_Irq(false);
}

#if (ENABLE_DMA_MODE || ENABLE_INTERRUPT_MODE)
static sfud_err SFUD_WaitOnFlagUntilTimeout(spi_user_data_t spidev)
{
	uint32_t tickstart = 0U;
	tickstart = HAL_GetTick();

	/* Wait until flag is set */
	while (HAL_SPI_GetState(spidev->spix) != HAL_SPI_STATE_READY)
	{
		/* Check for the Timeout */
		if ( (HAL_GetTick() - tickstart) > DLY )
		{
			SFUD_DEBUG("SFUD SPI WAITE TIME OUT!!!\r\n");
			return SFUD_ERR_TIMEOUT;
		}
	}
	return SFUD_SUCCESS;
}
#endif

/* The chip must have enable/disable action, otherwise it will not work normally */
/**
 * SPI write data then read data
 */
static sfud_err spi_write_read(const sfud_spi *spi, const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,
							   size_t read_size)
{
	sfud_err result = SFUD_SUCCESS;
	HAL_StatusTypeDef errorcode;
	spi_user_data_t spi_dev = (spi_user_data_t)spi->user_data;

	if (write_size)
		SFUD_ASSERT(write_buf);
	if (read_size)
		SFUD_ASSERT(read_buf);

	/* reset cs pin */
	if (spi_dev->cs_gpiox != NULL)
		HAL_GPIO_WritePin(spi_dev->cs_gpiox, spi_dev->cs_gpio_pin, GPIO_PIN_RESET);

	/* Write */
	if (write_size)
	{
#if 0
		if (SFUD_WaitOnFlagUntilTimeout(spi_dev) != SFUD_SUCCESS)
			return SFUD_ERR_TIMEOUT;
#endif

		/* send data */
#if ENABLE_DMA_MODE
		errorcode = HAL_SPI_Transmit_DMA(spi_dev->spix, (uint8_t *)write_buf, write_size);
#elif ENABLE_INTERRUPT_MODE
		errorcode = HAL_SPI_Transmit_IT(spi_dev->spix, (uint8_t *)write_buf, write_size);
#else
		errorcode = HAL_SPI_Transmit(spi_dev->spix, (uint8_t*)write_buf, write_size, DLY);
#endif

#if (ENABLE_DMA_MODE || ENABLE_INTERRUPT_MODE)		
		if (errorcode == HAL_OK)
		{
			if (SFUD_WaitOnFlagUntilTimeout(spi_dev) != SFUD_SUCCESS)
			{
				errorcode = HAL_TIMEOUT;
			}
		}
#endif
		if (errorcode == HAL_BUSY || errorcode == HAL_TIMEOUT)
		{
			SFUD_DEBUG("SFUD SPI WRITE ERR.\r\n");
			HAL_SPI_Abort(spi_dev->spix);
			result = SFUD_ERR_WRITE;
		}
	}
	/* Read */
	if (read_size)
	{
#if 0 /* In case of MASTER mode and SPI_DIRECTION_2LINES direction, no need to wait */
		if (SFUD_WaitOnFlagUntilTimeout(spi_dev) != SFUD_SUCCESS)
			return SFUD_ERR_TIMEOUT;
#endif
		
#if ENABLE_DMA_MODE
		errorcode = HAL_SPI_Receive_DMA(spi_dev->spix, (uint8_t *)read_buf, read_size);
#elif ENABLE_INTERRUPT_MODE
		errorcode = HAL_SPI_Receive_IT(spi_dev->spix, (uint8_t *)read_buf, read_size);
#else
		errorcode = HAL_SPI_Receive(spi_dev->spix, (uint8_t *)read_buf, read_size, DLY);
#endif
		
#if (ENABLE_DMA_MODE || ENABLE_INTERRUPT_MODE)
		if (errorcode == HAL_OK)
		{
			if (SFUD_WaitOnFlagUntilTimeout(spi_dev) != SFUD_SUCCESS)
			{
				errorcode = HAL_TIMEOUT;
			}
		}
#endif
		if (errorcode == HAL_BUSY || errorcode == HAL_TIMEOUT)
		{
			SFUD_DEBUG("SFUD SPI WRITE ERR.\r\n");
			HAL_SPI_Abort(spi_dev->spix);
			
			result = SFUD_ERR_READ;
		}
	}

	if (result != SFUD_SUCCESS)
	{
		SFUD_DEBUG("SFUD SPI ERR.\r\n");
		spi_dev->spix->State = HAL_SPI_STATE_READY;
	}

	/* set cs pin */
	if (spi_dev->cs_gpiox != NULL)
		HAL_GPIO_WritePin(spi_dev->cs_gpiox, spi_dev->cs_gpio_pin, GPIO_PIN_SET);

	return result;
}

/**
 * QSPI fast read data
 */

/* about 1 microsecond delay */
static void retry_delay_1ms(void)
{
	HAL_Delay(1);
}

static spi_user_data spi0 = { .spix = SFUD_FLASH_SPI_PORT, .cs_gpiox = F_CS_GPIO_Port, .cs_gpio_pin = F_CS_Pin, .tr_flg = 0 };
sfud_err sfud_spi_port_init(sfud_flash *flash)
{
	sfud_err result = SFUD_SUCCESS;

	switch (flash->index)
	{
	case SFUD_W25_DEVICE_INDEX:
	{
		/* set the interfaces and data */
		flash->spi.wr = spi_write_read;
		flash->spi.lock = spi_lock;
		flash->spi.unlock = spi_unlock;
		flash->spi.user_data = &spi0;
		/* about 100 microsecond delay */
		flash->retry.delay = retry_delay_1ms;
		/* adout 60 seconds timeout */
		flash->retry.times = 60 * 1000;
		break;
	}
	default:
		break;
	}

	return result;
}

/**
 * This function is print debug info.
 *
 * @param file the file which has call this function
 * @param line the line number which has call this function
 * @param format output format
 * @param ... args
 */
void sfud_log_debug(const char *file, const long line, const char *format, ...)
{
#if 1
	va_list args;

	/* args point to the first variable parameter */
	va_start(args, format);
	printf("[D][SFUD](%s:%ld) ", file, line);
	/* must use vprintf to print */
	vsnprintf(log_buf, sizeof(log_buf), format, args);
	printf("%s\r\n", log_buf);
	va_end(args);
#endif
}

/**
 * This function is print routine info.
 *
 * @param format output format
 * @param ... args
 */
void sfud_log_info(const char *format, ...)
{
#if 1
	va_list args;

	/* args point to the first variable parameter */
	va_start(args, format);
	printf("[I][SFUD]");
	/* must use vprintf to print */
	vsnprintf(log_buf, sizeof(log_buf), format, args);
	printf("%s\r\n", log_buf);
	va_end(args);
#endif
}
