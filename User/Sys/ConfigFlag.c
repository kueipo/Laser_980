
#include "ConfigFlag.h"

void cf_Config_App_Flag(uint8_t configflag)
{
	uint8_t flag;
	uint32_t addr = 0 + cf_UPD_FLAG_ADDR;
#if defined(ENABLE_FAL_SUPPORT)
	const struct fal_partition *part = fal_partition_find ("upd");

	if (part == NULL)
		return;

	if (fal_partition_read(part, addr, &flag, 1) >= 0)
	{
		if (flag != configflag)
		{
			flag = configflag;
			fal_partition_erase(part, addr, 1);
			fal_partition_write(part, addr, &flag, 1);
			cf_Delay_ms(10);
			cf_Restart();
		}
	}
#else
	cf_FLASH_Read(addr, &flag, 1);
	if (flag != configflag)
	{
		flag = configflag;
		cf_FLASH_Init();
		cf_FLASH_Erase(addr, 1);
		cf_FLASH_Write(addr, &flag, 1);
	  cf_Delay_ms(10);
		cf_Restart();
	}
#endif
}
