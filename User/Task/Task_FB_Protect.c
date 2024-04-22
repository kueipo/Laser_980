
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/

/* Local function prototypes -------------------------------------------------*/
static void Protect_Error(void *arg);
static void Protect_FB_Error(void);

static void Protect_Updata(void *arg);
static void Protect_FB_Updata(void);

static void Protect_Version(void *arg);
static void Protect_FB_Version(void);

/* Variables -----------------------------------------------------------------*/
typedef struct
{
	volatile uint8_t type;
	volatile uint8_t target;
	void (*current_operation)(void *arg);
} _Local_App_St;

static volatile _Local_App_St AppTable[] = 
{
	{INDEX_TYPE_FEEDBACK,	INDEX_ERROR_CODE,			(*Protect_Error) },
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_UPDATA,	(*Protect_Updata)},
	{INDEX_TYPE_FEEDBACK, INDEX_TARGET_VERSION,	(*Protect_Version)},
};
static volatile uint8_t s_ucAppQty = sizeof(AppTable) / sizeof(AppTable[0]);

static volatile Task_Typedef TaskLocal[] = 
{	
/* 	State		RunTime		Period   current_operation */
	{ SUSPEND,	1,			1,		(*Protect_FB_Error)	},
	{ SUSPEND,	2,			1,		(*Protect_FB_Updata)},
	{ SUSPEND,	4,			1,		(*Protect_FB_Version)},
};
static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/**
 * @brief  Protect_Error.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Protect_Error(void *arg)
{
	uint8_t *data = arg;
	uint8_t errcode;

	errcode = data[OFFSET_DATA_CONTENT_START + 1];

	APP_Protect_WriteErrorCode(errcode);

#if 0
	Task_FB_Protect_Enable(TASK_FB_PROTECT_ERROR, 0);
#endif
}

/**
 * @brief  Protect_FB_Error.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Protect_FB_Error(void)
{
	TaskLocal[TASK_FB_PROTECT_ERROR].State = SUSPEND;
}

/* ---------------------------------------------------------------------------*/
#ifndef FILE_SIZE_LENGTH
#define FILE_SIZE_LENGTH 4
#endif
/**
 * @brief  Protect_Updata.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Protect_Updata(void *arg)
{
	uint8_t buf = UPLOAD_APP_PRO;

#if defined(ENABLE_FAL_SUPPORT)
	/* Read Size */
	uint32_t filesize = 0;
	uint8_t buff[FILE_SIZE_LENGTH];

	const struct fal_partition *part = fal_partition_find("APP0");
	if (part == NULL)
		return;

	if (fal_partition_read(part, 0, buff, FILE_SIZE_LENGTH) < FILE_SIZE_LENGTH)
		return;

	/* Calculate size */
	for (uint8_t i = 0; i < FILE_SIZE_LENGTH; i++)
	{
		filesize <<= 8;
		filesize += buff[i];
	}

	/*  */
	if (filesize == 0 || filesize == 0xFFFFFFFF)
		return;

	part = fal_partition_find("upd");
	if (part != NULL)
	{
		fal_partition_erase(part, 0, 1);
		fal_partition_write(part, 0, &buf, 1);
	}
#endif /* ENABLE_FAL_SUPPORT */

#if 0 /* opt flash */
	FLASH_Init();
	FLASH_Erase(UPD_FLAG_ADDR, 1);
	FLASH_Write(UPD_FLAG_ADDR, &buf, 1);
#endif

	HAL_FLASH_OB_Launch();

#if 0	
	Task_FB_Protect_Enable(TASK_FB_PROTECT_UPDATA, 0);
#endif
}

/**
 * @brief  Protect_FB_Updata.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Protect_FB_Updata(void)
{
	TaskLocal[TASK_FB_PROTECT_UPDATA].State = SUSPEND;
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  Protect_Error.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Protect_Version(void *arg)
{
	uint8_t *data = arg;
	uint32_t version;
	
	version = data[OFFSET_DATA_CONTENT_START - 1];
	version <<= 8;
	version += data[OFFSET_DATA_CONTENT_START - 1 + 1];
	if (data[OFFSET_FRAME_LENGTH] > 5)
	{
		version <<= 8;
		version += data[OFFSET_DATA_CONTENT_START - 1 + 2];
		version <<= 8;
		version += data[OFFSET_DATA_CONTENT_START - 1 + 3];
	}
	
	APP_Protect_WriteVersion(version);

#if 0
	Task_FB_Protect_Enable(TASK_FB_PROTECT_VERSION, 0);
#endif
}

/**
 * @brief  Protect_FB_Error.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Protect_FB_Version(void)
{
	uint16_t temp[2];
	uint32_t version = APP_Protect_ReadVersion();
	
	if (version > 999)
	{
		temp[0] = (uint16_t)(version >> 16);
		temp[1] = (uint16_t)(version);
		APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_FEEDBACK, INDEX_TARGET_VERSION, 2, temp);
	}
	else
	{
		temp[0] = (uint16_t)(version);
		APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_FEEDBACK, INDEX_TARGET_VERSION, 1, temp);
	}

	TaskLocal[TASK_FB_PROTECT_VERSION].State = SUSPEND;
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  Task_FB_Protect_Marks_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_FB_Protect_Marks_Handler_Callback(void)
{
	for (uint8_t index = 0; index < TaskLocal_Total; index++)
	{
		if (TaskLocal[index].RunTime)
			TaskLocal[index].RunTime--;
	}
}

/**
 * @brief  Task_FB_Protect_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_FB_Protect_Handler_Callback(void)
{
	for (uint8_t index = 0; index < TaskLocal_Total; index++)
	{
		if (TaskLocal[index].RunTime == 0 && (TaskLocal[index].State == READY))
		{
			TaskLocal[index].TaskHook();
			TaskLocal[index].RunTime = TaskLocal[index].Period;
		}
	}
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  Task_FB_Protect_Enable.
 * @note   None.
 * @param  index.
 * @param	 DelayState.
 * @retval None.
 */
void Task_FB_Protect_Enable(uint8_t id, uint8_t delaystate)
{
	if (delaystate)
		delaystate = TaskLocal[id].Period;

	TaskLocal[id].RunTime = delaystate;
	TaskLocal[id].State = READY;
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  Task_FB_Protect_Search.
 * @note   None.
 * @param  buf.
 * @retval None.
 */
void Task_FB_Protect_Search(void *buf)
{
	uint8_t *data = buf;
	uint8_t type = data[OFFSET_DATA_TYPE];
	uint8_t dev = data[OFFSET_DATA_TARGET_H];
	uint8_t target = data[OFFSET_DATA_TARGET_L];

	if (dev != DEV_INDEX_PORTECT)
		return;

	/* Refresh WDG */
	APP_Protect_WDG_Refresh();
	
	for (uint8_t i = 0; i < s_ucAppQty; i++)
	{
		if ((AppTable[i].type == type) && (AppTable[i].target == target))
		{
			AppTable[i].current_operation(buf);
			break;
		}
	}
}
