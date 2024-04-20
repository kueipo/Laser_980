
#include "Stm32_Flash.h"

int FLASH_Init(void)
{
#if 0
	/* Unlock the Program memory ************************************************/
	HAL_FLASH_Unlock();

	/* Clear all FLASH flags ****************************************************/
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	/* Unlock the Program memory ************************************************/
	HAL_FLASH_Lock();
#endif	
	return 1;
}

int FLASH_Read(uint32_t addr, uint8_t *buf, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++, addr++, buf++)
	{
		*buf = *(uint8_t *)addr;
	}

	return size;
}

int FLASH_Write(uint32_t addr, const uint8_t *buf, size_t size)
{
	size_t i;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	for (i = 0; i < size; i += 2, addr += 2, buf += 2)
	{
		/* write data *************************************************************/
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr, *(uint16_t *)(buf));

		/* check data *************************************************************/
		if (*(uint16_t *)addr != *(uint16_t *)(buf))
		{
			return -1;
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	   to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();

	return size;
}

int FLASH_Erase(uint32_t addr, size_t size)
{
	uint32_t NbrOfPages = 0;
	uint32_t PageError = 0;
	FLASH_EraseInitTypeDef pEraseInit;
	HAL_StatusTypeDef status = HAL_OK;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();

	/* Clear all FLASH flags ****************************************************/
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	/* Get the sector where start the user flash area ***************************/
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
		/* Error occurred while page erase ****************************************/
		return -1;
	}
	return size;
}
