/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal.h>

#include <stm32f0xx.h>

/* base address of the flash sectors */
#define ADDR_FLASH_SECTOR_0      ((uint32_t)0x08000000) /* Base address of Sector 0, 4 K bytes   */
#define ADDR_FLASH_SECTOR_1      ((uint32_t)0x08001000) /* Base address of Sector 1, 4 K bytes   */
#define ADDR_FLASH_SECTOR_2      ((uint32_t)0x08002000) /* Base address of Sector 2, 4 K bytes   */
#define ADDR_FLASH_SECTOR_3      ((uint32_t)0x08003000) /* Base address of Sector 3, 4 K bytes   */
#define ADDR_FLASH_SECTOR_4      ((uint32_t)0x08004000) /* Base address of Sector 4, 4 K bytes   */
#define ADDR_FLASH_SECTOR_5      ((uint32_t)0x08005000) /* Base address of Sector 5, 4 K bytes  */
#define ADDR_FLASH_SECTOR_6      ((uint32_t)0x08006000) /* Base address of Sector 6, 4 K bytes  */
#define ADDR_FLASH_SECTOR_7      ((uint32_t)0x08007000) /* Base address of Sector 7, 4 K bytes  */
#define ADDR_FLASH_SECTOR_8      ((uint32_t)0x08008000) /* Base address of Sector 8, 4 K bytes  */
#define ADDR_FLASH_SECTOR_9      ((uint32_t)0x08009000) /* Base address of Sector 9, 4 K bytes  */
#define ADDR_FLASH_SECTOR_10     ((uint32_t)0x0800A000) /* Base address of Sector 10, 4 K bytes */
#define ADDR_FLASH_SECTOR_11     ((uint32_t)0x0800B000) /* Base address of Sector 11, 4 K bytes */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x0800C000) /* Base address of Sector 12, 4 K bytes */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x0800D000) /* Base address of Sector 13, 4 K bytes */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x0800E000) /* Base address of Sector 14, 4 K bytes */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0800F000) /* Base address of Sector 15, 4 K bytes */
/**
 * Get the sector of a given address
 *
 * @param address flash address
 *
 * @return The sector of a given address
 */
static uint32_t stm32_get_sector(uint32_t address)
{
    uint32_t sector = 0;

    if ((address < ADDR_FLASH_SECTOR_1) && (address >= ADDR_FLASH_SECTOR_0))
    {
        sector = FLASH_Sector_0;
    }
    else if ((address < ADDR_FLASH_SECTOR_2) && (address >= ADDR_FLASH_SECTOR_1))
    {
        sector = FLASH_Sector_1;
    }
    else if ((address < ADDR_FLASH_SECTOR_3) && (address >= ADDR_FLASH_SECTOR_2))
    {
        sector = FLASH_Sector_2;
    }
    else if ((address < ADDR_FLASH_SECTOR_4) && (address >= ADDR_FLASH_SECTOR_3))
    {
        sector = FLASH_Sector_3;
    }
    else if ((address < ADDR_FLASH_SECTOR_5) && (address >= ADDR_FLASH_SECTOR_4))
    {
        sector = FLASH_Sector_4;
    }
    else if ((address < ADDR_FLASH_SECTOR_6) && (address >= ADDR_FLASH_SECTOR_5))
    {
        sector = FLASH_Sector_5;
    }
    else if ((address < ADDR_FLASH_SECTOR_7) && (address >= ADDR_FLASH_SECTOR_6))
    {
        sector = FLASH_Sector_6;
    }
    else if ((address < ADDR_FLASH_SECTOR_8) && (address >= ADDR_FLASH_SECTOR_7))
    {
        sector = FLASH_Sector_7;
    }
    else if ((address < ADDR_FLASH_SECTOR_9) && (address >= ADDR_FLASH_SECTOR_8))
    {
        sector = FLASH_Sector_8;
    }
    else if ((address < ADDR_FLASH_SECTOR_10) && (address >= ADDR_FLASH_SECTOR_9))
    {
        sector = FLASH_Sector_9;
    }
    else if ((address < ADDR_FLASH_SECTOR_11) && (address >= ADDR_FLASH_SECTOR_10))
    {
        sector = FLASH_Sector_10;
    }
		else if ((address < ADDR_FLASH_SECTOR_12) && (address >= ADDR_FLASH_SECTOR_11))
    {
        sector = FLASH_Sector_11;
    }
		else if ((address < ADDR_FLASH_SECTOR_13) && (address >= ADDR_FLASH_SECTOR_12))
    {
        sector = FLASH_Sector_12;
    }
		else if ((address < ADDR_FLASH_SECTOR_14) && (address >= ADDR_FLASH_SECTOR_13))
    {
        sector = FLASH_Sector_13;
    }
		else if ((address < ADDR_FLASH_SECTOR_15) && (address >= ADDR_FLASH_SECTOR_14))
    {
        sector = FLASH_Sector_14;
    }
    else
    {
        sector = FLASH_Sector_11;
    }

    return sector;
}

/**
 * Get the sector size
 *
 * @param sector sector
 *
 * @return sector size
 */
static uint32_t stm32_get_sector_size(uint32_t sector) {
    assert(IS_FLASH_SECTOR(sector));

    switch (sector) {
    case FLASH_Sector_0: return 4 * 1024;
    case FLASH_Sector_1: return 4 * 1024;
    case FLASH_Sector_2: return 4 * 1024;
    case FLASH_Sector_3: return 4 * 1024;
    case FLASH_Sector_4: return 4 * 1024;
    case FLASH_Sector_5: return 4 * 1024;
    case FLASH_Sector_6: return 4 * 1024;
    case FLASH_Sector_7: return 4 * 1024;
    case FLASH_Sector_8: return 4 * 1024;
    case FLASH_Sector_9: return 4 * 1024;
    case FLASH_Sector_10: return 4 * 1024;
    case FLASH_Sector_11: return 4 * 1024;
		case FLASH_Sector_12: return 4 * 1024;
		case FLASH_Sector_13: return 4 * 1024;
		case FLASH_Sector_14: return 4 * 1024;
		case FLASH_Sector_15: return 4 * 1024;
    default : return 64 * 1024;
    }
}
static int init(void)
{
    /* do nothing now */
}

static int read(long offset, uint8_t *buf, size_t size)
{
    size_t i;
    uint32_t addr = stm32f2_onchip_flash.addr + offset;
    for (i = 0; i < size; i++, addr++, buf++)
    {
        *buf = *(uint8_t *) addr;
    }

    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    size_t i;
    uint32_t read_data;
    uint32_t addr = stm32f2_onchip_flash.addr + offset;

    FLASH_Unlock();
    FLASH_ClearFlag(
            FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR
                    | FLASH_FLAG_PGSERR);
    for (i = 0; i < size; i++, buf++, addr++)
    {
        /* write data */
        FLASH_ProgramByte(addr, *buf);
        read_data = *(uint8_t *) addr;
        /* check data */
        if (read_data != *buf)
        {
            return -1;
        }
    }
    FLASH_Lock();

    return size;
}

static int erase(long offset, size_t size)
{
    FLASH_Status flash_status;
    size_t erased_size = 0;
    uint32_t cur_erase_sector;
    uint32_t addr = stm32f2_onchip_flash.addr + offset;

    /* start erase */
    FLASH_Unlock();
    FLASH_ClearFlag(
            FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR
                    | FLASH_FLAG_PGSERR);
    /* it will stop when erased size is greater than setting size */
    while (erased_size < size)
    {
        cur_erase_sector = stm32_get_sector(addr + erased_size);
        flash_status = FLASH_EraseSector(cur_erase_sector, VoltageRange_3);
        if (flash_status != FLASH_COMPLETE)
        {
            return -1;
        }
        erased_size += stm32_get_sector_size(cur_erase_sector);
    }
    FLASH_Lock();

    return size;
}

const struct fal_flash_dev stm32f2_onchip_flash =
{
    .name       = "stm32_onchip",
    .addr       = 0x08000000,
    .len        = 64*1024,
    .blk_size   = 4*1024,
    .ops        = {init, read, write, erase},
    .write_gran = 8
};

