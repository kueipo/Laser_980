/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

//#include <rtconfig.h>
//#include <board.h>

#define USING_STM32_FLASH

#define FAL_DEBUG			1
#define	FAL_LOG_ERR		1
#define FAL_LOG_INFO	1

#define FAL_PART_HAS_TABLE_CFG

//#define FAL_PART_TABLE_FLASH_DEV_NAME		"W25Q80DV"

#define FAL_USING_NOR_FLASH_DEV_NAME        "norflash0"

#ifdef USING_STM32_FLASH
#define FAL_USING_STM_FLASH_DEV_NAME        "stm32_onchip"
#endif
/* ===================== Flash device Configuration ========================= */
#ifdef USING_STM32_FLASH
	extern const struct fal_flash_dev stm32_onchip_flash;
#endif
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE		\
{								\
	&stm32_onchip_flash,		\
    &nor_flash0,				\
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                              \
{                                                                                   \
	{FAL_PART_MAGIC_WORD,	"app", 			FAL_USING_STM_FLASH_DEV_NAME,	   (16)*1024, 	  48*1024, 0}, \
    {FAL_PART_MAGIC_WORD,	"picture0", 	FAL_USING_NOR_FLASH_DEV_NAME,	(0*128)*1024, 	 128*1024, 0}, \
	{FAL_PART_MAGIC_WORD,	"picture1",		FAL_USING_NOR_FLASH_DEV_NAME,	(1*128)*1024, 	 128*1024, 0}, \
    {FAL_PART_MAGIC_WORD,	"picture2",		FAL_USING_NOR_FLASH_DEV_NAME, 	(2*128)*1024,	 128*1024, 0}, \
	{FAL_PART_MAGIC_WORD,	"picture3",		FAL_USING_NOR_FLASH_DEV_NAME, 	(3*128)*1024,	 128*1024, 0}, \
	{FAL_PART_MAGIC_WORD,	"factory",		FAL_USING_NOR_FLASH_DEV_NAME,(1024-128)*1024,	  64*1024, 0}, \
	{FAL_PART_MAGIC_WORD,	"download",		FAL_USING_NOR_FLASH_DEV_NAME, (1024-64)*1024,	  60*1024, 0}, \
	{FAL_PART_MAGIC_WORD,	"env",			FAL_USING_NOR_FLASH_DEV_NAME,  (1024-4)*1024,	   4*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
