
/* Includes ------------------------------------------------------------------*/
#include "FT5466.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static FT5466_Status_t CommunicationResult;

/* Private function prototypes -----------------------------------------------*/
static void FT5466_Reset(void);
static FT5466_Status_t FT5466_GetProductID(uint32_t *id);
static FT5466_Status_t FT5466_SendConfig(void);
static FT5466_Status_t FT5466_GetPoints(uint8_t *status);
static FT5466_Status_t FT5466_WR_Reg(uint8_t reg, uint8_t *buf, uint8_t len);
static FT5466_Status_t FT5466_RD_Reg(uint8_t reg, uint8_t *buf, uint8_t len);

/* API Implementation --------------------------------------------------------*/
FT5466_Status_t FT5466_Init(void)
{
	/* Reset chip */
	FT5466_Reset();

	/* Get product ID */
	uint32_t productID = 0;
	CommunicationResult = FT5466_GetProductID(&productID);
	if (CommunicationResult != FT5466_OK)
	{
		return CommunicationResult;
	}
	if (productID == 0)
	{
		return FT5466_NotResponse;
	}

	/* Config chip */
	FT5466_SendConfig();

	return FT5466_OK;
}

FT5466_Status_t FT5466_ReadTouch(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate)
{
	uint8_t RxBuffer[4] = {0};
	uint8_t Points;
	FT5466_Status_t Result = FT5466_OK;

	*number_of_cordinate = 0; // default 0

	Result = FT5466_GetPoints(&Points);
	if (Result != FT5466_OK)
		return Result;

	if (Points != 0)
	{
		*number_of_cordinate = Points;
		for (uint8_t i = 0; i < *number_of_cordinate; i++)
		{
			Result = FT5466_RD_Reg(FT_TP1_REG + (i * 6), RxBuffer, 4);
			if (Result != FT5466_OK)
				return Result;

			cordinate[i].x = RxBuffer[0] & 0x0F;
			cordinate[i].x = RxBuffer[1] + (cordinate[i].x << 8);
			cordinate[i].y = RxBuffer[2] & 0x0F;
			cordinate[i].y = RxBuffer[3] + (cordinate[i].y << 8);
		}
	}

	return FT5466_OK;
}

/* LVGL --------------------------------------------------------------------- */
typedef struct
{
	uint16_t x;
	uint16_t y;
	bool flag;
} FT5466_X_Y_t;

static FT5466_X_Y_t FT5466_X_Y = {
	.x = 0,
	.y = 0,
	.flag = false,
};

void FT5466_write_xy(void)
{
	uint8_t RxBuffer[4];
	FT5466_Status_t Result = FT5466_OK;
	Result = FT5466_RD_Reg(FT_TP1_REG, RxBuffer, 4);
	if (Result != FT5466_OK)
		return;

	FT5466_X_Y.x = RxBuffer[0] & 0x0F;
	FT5466_X_Y.x = RxBuffer[1] + (FT5466_X_Y.x << 8);
	FT5466_X_Y.y = RxBuffer[2] & 0x0F;
	FT5466_X_Y.y = RxBuffer[3] + (FT5466_X_Y.y << 8);

	//	printf("%d, %d\r\n",FT5466_X_Y.x, FT5466_X_Y.y);

	FT5466_X_Y.flag = true;
}

void FT5466_Read_xy(int16_t *x, int16_t *y)
{
	FT5466_X_Y.flag = false;
	/* The resolution can be adjusted according to the screen direction.
	example:
		(*x) = FT5466_X_Y.y;
		(*y) = 480 - FT5466_X_Y.x;
	*/
	(*x) = FT5466_X_Y.x;
	(*y) = FT5466_X_Y.y;
}

bool FT5466_IsTouch(void)
{
	return FT5466_X_Y.flag;
}

/* Private functions Implementation ---------------------------------------------------------*/
static void FT5466_Reset(void)
{
	FT5466_RST_Control(0);
	FT5466_Delay(100);
	FT5466_RST_Control(1);
	FT5466_Delay(100);
}

static FT5466_Status_t FT5466_GetProductID(uint32_t *id)
{
	uint8_t RxBuffer[2] = {0};
	FT5466_Status_t Result = FT5466_NotResponse;

	Result = FT5466_RD_Reg(FT_ID_G_LIB_VERSION, RxBuffer, 2);
	if (Result == FT5466_OK)
		id[0] = RxBuffer[1];

	return Result;
}

static FT5466_Status_t FT5466_SendConfig(void)
{
	uint8_t TxBuffer[1];
	FT5466_WR_Reg(FT_DEVIDE_MODE, TxBuffer, 1);	 // 进入正常操作模式
	FT5466_WR_Reg(FT_ID_G_MODE, TxBuffer, 1);	 // 查询模式
	TxBuffer[0] = 22;							 // 触摸有效值，22，越小越灵敏
	FT5466_WR_Reg(FT_ID_G_THGROUP, TxBuffer, 1); // 设置触摸有效值
	TxBuffer[0] = 12;							 // 激活周期，不能小于12，最大14
	FT5466_WR_Reg(FT_ID_G_PERIODACTIVE, TxBuffer, 1);
	return FT5466_OK;
}

static FT5466_Status_t FT5466_GetPoints(uint8_t *status)
{
	uint8_t RxBuffer[1] = {0};
	FT5466_Status_t Result = FT5466_NotResponse;

	Result = FT5466_RD_Reg(FT_REG_NUM_FINGER, RxBuffer, 1);
	if (Result == FT5466_OK)
	{
		if ((RxBuffer[0] & 0x0F) > 6) /* 1-5 is valid */
			*status = 0;
		else
			*status = RxBuffer[0];
	}

	return Result;
}

static FT5466_Status_t FT5466_WR_Reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t Address = reg;
	FT5466_Status_t Result = FT5466_NotResponse;

	Result = FT5466_I2C_Write(FT_ADDRESS, &Address, 1);
	if (Result == FT5466_OK)
		Result = FT5466_I2C_Write(FT_ADDRESS, buf, len);

	return Result;
}

static FT5466_Status_t FT5466_RD_Reg(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t Address = reg;
	FT5466_Status_t Result = FT5466_NotResponse;

	Result = FT5466_I2C_Write(FT_ADDRESS, &Address, 1);
	if (Result == FT5466_OK)
		Result = FT5466_I2C_Read(FT_ADDRESS, buf, len);

	return Result;
}
