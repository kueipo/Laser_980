
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#define USING_STM32_FLASH
//#define USING_NOR_FLASH

#define FAL_DEBUG				0
#define	FAL_LOG_ERR			0
#define FAL_LOG_INFO		0

#define FAL_PART_HAS_TABLE_CFG

#ifdef USING_STM32_FLASH
	#define FAL_USING_STM_FLASH_DEV_NAME        "stm32_onchip"
#endif /* USING_STM32_FLASH */

#ifdef USING_NOR_FLASH
	#define FAL_USING_NOR_FLASH_DEV_NAME        "norflash0"
#endif /* USING_NOR_FLASH */

/* ===================== Flash device Configuration ========================= */
#ifdef USING_STM32_FLASH
	extern const struct fal_flash_dev stm32_onchip_flash;
#endif /* USING_STM32_FLASH */

#ifdef USING_NOR_FLASH
	extern struct fal_flash_dev nor_flash0;
#endif /* USING_NOR_FLASH */

/* flash device table */
#if defined(USING_STM32_FLASH) && defined(USING_NOR_FLASH)
	#define FAL_FLASH_DEV_TABLE \
		{                         \
			&stm32_onchip_flash,    \
			&nor_flash0,        		\
		}
#elif defined(USING_STM32_FLASH)
	#define FAL_FLASH_DEV_TABLE \
		{                         \
			&stm32_onchip_flash,    \
		}
#elif defined(USING_NOR_FLASH)
	#define FAL_FLASH_DEV_TABLE \
		{                         \
			&nor_flash0,        		\
		}
#else
	#error Please define the relevant flash
#endif /* USING_STM32_FLASH && USING_NOR_FLASH */
	
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
	/* partition table */
	#define FAL_PART_TABLE                                                              \
	{                                                                                   \
		{FAL_PART_MAGIC_WORD,	"app",	FAL_USING_STM_FLASH_DEV_NAME,	(20)*1024,							(60)*1024, 0}, \
		{FAL_PART_MAGIC_WORD,	"fac",	FAL_USING_STM_FLASH_DEV_NAME,	(20+60)*1024,						(60)*1024, 0}, \
		{FAL_PART_MAGIC_WORD,	"dwn",	FAL_USING_STM_FLASH_DEV_NAME,	(20+60+60)*1024,				(60)*1024, 0}, \
		{FAL_PART_MAGIC_WORD, "APP0",	FAL_USING_STM_FLASH_DEV_NAME,	(20+60+60+60)*1024, 		(48)*1024, 0}, \
		{FAL_PART_MAGIC_WORD,	"env",	FAL_USING_STM_FLASH_DEV_NAME,	(20+60+60+60+48)*1024,	(6)*1024, 0}, \
		{FAL_PART_MAGIC_WORD,	"upd",	FAL_USING_STM_FLASH_DEV_NAME,	(256-2)*1024,						(2)*1024, 0},	\
	}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
