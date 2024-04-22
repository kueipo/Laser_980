#include "easyflash.h"
#include <stdlib.h>
#include "stdio.h"

#ifdef ENABLE_EF_TEST

void easyflash_sample(void)
{
	/* fal init */

	/* easyflash init */
	if (easyflash_init() == EF_NO_ERR)
	{
		uint32_t i_boot_times = NULL;
		char *c_old_boot_times, c_new_boot_times[11] = {0};

		/* get the boot count number from Env */
		c_old_boot_times = ef_get_env("boot_times");
		/* get the boot count number failed */
		if (c_old_boot_times == NULL)
		{
			i_boot_times = 0;
		}
		else
			i_boot_times = atol(c_old_boot_times);
		/* boot count +1 */
		i_boot_times++;
		EF_DEBUG("===============================================\n");
		EF_DEBUG("The system now boot %d times\n", i_boot_times);
		EF_DEBUG("===============================================\n");
		/* interger to string */
		sprintf(c_new_boot_times, "%d", i_boot_times);
		/* set and store the boot count number to Env */
		ef_set_env("boot_times", c_new_boot_times);
		ef_save_env();
#ifdef PRINT_DEBUG
		ef_print_env();
#endif

		i_boot_times = 0;
		char *c_old_boot_times_1 = ef_get_env("boot_times");
		i_boot_times = atol(c_old_boot_times_1);
		i_boot_times++;
		EF_DEBUG("===============================================\n");
		EF_DEBUG("The system now boot %d times\n", i_boot_times);
		EF_DEBUG("===============================================\n");
	}
}
#endif /* ENABLE_EF_TEST */
