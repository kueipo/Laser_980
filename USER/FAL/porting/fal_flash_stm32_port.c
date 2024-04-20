/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal/inc/fal.h>
#include "main.h"

#ifndef FAL_USING_STM_FLASH_DEV_NAME
	#define FAL_USING_STM_FLASH_DEV_NAME             "stm32_onchip"
#endif

static int init(void)
{
	/* Unlock the Program memory */
	HAL_FLASH_Unlock();

	/* Clear all FLASH flags */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	/* Unlock the Program memory */
	HAL_FLASH_Lock();
	return 1;
}

static int read(long offset, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t addr = stm32_onchip_flash.addr + offset;
	for (i = 0; i < size; i++, addr++, buf++)
	{
		*buf = *(uint8_t *)addr;
	}

	return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
	uint32_t addr = stm32_onchip_flash.addr + offset;
	size_t i;

	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	for (i = 0; i < size; i += 2, addr += 2, buf += 2)
	{
		/* write data */
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr, *(uint16_t *)(buf));

		/* check data */
		if (*(uint16_t *)addr != *(uint16_t *)(buf))
		{
			return -1;
		}
	}

	HAL_FLASH_Lock();

	return size;
}

static int erase(long offset, size_t size)
{
	uint32_t addr = stm32_onchip_flash.addr + offset;
	uint32_t NbrOfPages = 0;
	uint32_t PageError = 0;
	FLASH_EraseInitTypeDef pEraseInit;
	HAL_StatusTypeDef status = HAL_OK;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();

	/* Get the sector where start the user flash area */
	NbrOfPages = (size + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;

	pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	pEraseInit.PageAddress = addr;
#ifdef FLASH_BANK_1
	pEraseInit.Banks = FLASH_BANK_1;
#endif
	pEraseInit.NbPages = NbrOfPages;
	status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);

	/* Lock the Flash to disable the flash control register access (recommended
		 to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();

	if (status != HAL_OK)
	{
		/* Error occurred while page erase */
		return -1;
	}
	return size;
}

const struct fal_flash_dev stm32_onchip_flash =
{
	.name = FAL_USING_STM_FLASH_DEV_NAME,
	.addr = FLASH_BASE,
	.len = 256 * 1024,
	.blk_size = FLASH_PAGE_SIZE,
	.ops = {init, read, write, erase},
#if defined(STM32F030x8) || defined(STM32F103xE)
	.write_gran = 16
#else
	.write_gran = 8
#endif
};
