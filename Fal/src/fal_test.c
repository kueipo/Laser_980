
#include "fal/inc/fal.h"
#include <string.h>

#if FAL_TEST_ENABLE

#define BUF_SIZE 1024

static int fal_test(const char *partiton_name)
{
    int ret;
    int i, j, len;
    uint8_t buf[BUF_SIZE];
    const struct fal_flash_dev *flash_dev = NULL;
    const struct fal_partition *partition = NULL;

    if (!partiton_name)
    {
        FAL_PRINTF("Input param partition name is null!\n");
        return -1;
    }

    partition = fal_partition_find(partiton_name);
    if (partition == NULL)
    {
        FAL_PRINTF("Find partition (%s) failed!\n", partiton_name);
        ret = -1;
        return ret;
    }

    flash_dev = fal_flash_device_find(partition->flash_name);
    if (flash_dev == NULL)
    {
        FAL_PRINTF("Find flash device (%s) failed!\n", partition->flash_name);
        ret = -1;
        return ret;
    }

    FAL_PRINTF("Flash device : %s   "
               "Flash size : %dK   \n"
               "Partition : %s   "
               "Partition size: %dK\n", 
                partition->flash_name, 
                flash_dev->len/1024,
                partition->name,
                partition->len/1024);

    /* erase all partition */
    ret = fal_partition_erase_all(partition);
    if (ret < 0)
    {
        FAL_PRINTF("Partition (%s) erase failed!\n", partition->name);
        ret = -1;
        return ret;
    }
    FAL_PRINTF("Erase (%s) partition finish!\n", partiton_name);

    /* read the specified partition and check data */
    for (i = 0; i < partition->len;)
    {
        memset(buf, 0x00, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            FAL_PRINTF("Partition (%s) read failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        for(j = 0; j < len; j++)
        {
            if (buf[j] != 0xFF)
            {
                FAL_PRINTF("The erase operation did not really succeed!\n");
                ret = -1;
                return ret;
            }
        }
        i += len;
    }

    /* write 0x00 to the specified partition */
    for (i = 0; i < partition->len;)
    {
        memset(buf, 0x00, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_write(partition, i, buf, len);
        if (ret < 0)
        {
            FAL_PRINTF("Partition (%s) write failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        i += len;
    }
    FAL_PRINTF("Write (%s) partition finish! Write size %d(%dK).\n", partiton_name, i, i/1024);

    /* read the specified partition and check data */
    for (i = 0; i < partition->len;)
    {
        memset(buf, 0xFF, BUF_SIZE);

        len = (partition->len - i) > BUF_SIZE ? BUF_SIZE : (partition->len - i);

        ret = fal_partition_read(partition, i, buf, len);
        if (ret < 0)
        {
            FAL_PRINTF("Partition (%s) read failed!\n", partition->name);
            ret = -1;
            return ret;
        }

        for(j = 0; j < len; j++)
        {
            if (buf[j] != 0x00)
            {
                FAL_PRINTF("The write operation did not really succeed!\n");
                ret = -1;
                return ret;
            }
        }

        i += len;
    }

    ret = 0;
    return ret;
}

void fal_sample(void)
{
    /* init */
    fal_init();

    if (fal_test("app") == 0)
    {
        FAL_PRINTF("Fal partition (%s) test success!\n", "fac");
    }
    else
    {
        FAL_PRINTF("Fal partition (%s) test failed!\n", "fac");
    }

    if (fal_test("app") == 0)
    {
        FAL_PRINTF("Fal partition (%s) test success!\n", "env");
    }
    else
    {
        FAL_PRINTF("Fal partition (%s) test failed!\n", "env");
    }
}

#else
void fal_sample(void)
{}
#endif
