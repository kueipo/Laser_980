
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Private variables ---------------------------------------------------------*/
enum
{
	STATE_REG = 0,	/* Status register */
	CHECK_REG,		/* Detection register */
	VOL_P_REG_1,	/* Voltage parameter register */
	VOL_P_REG_2,
	VOL_P_REG_3,
	VOL_REG_1,		/* Voltage register */
	VOL_REG_2,
	VOL_REG_3,
	CUR_P_REG_1,	/* Current parameter register */
	CUR_P_REG_2,
	CUR_P_REG_3,
	CUR_REG_1,		/* Current register */
	CUR_REG_2,
	CUR_REG_3,
	POW_P_REG_1,	/* Power parameter register */
	POW_P_REG_2,
	POW_P_REG_3,
	POW_REG_1,		/* Power register */
	POW_REG_2,
	POW_REG_3,
	DAT_UPD_REG,	/* Data update register */
	PF_REG_1,		/* Number of PF pulses，Used with status register */
	PF_REG_2,
	CHK_REG,		/* Checksum */
};

typedef struct
{
	__IO uint16_t Val;
}ACvoltage_TypeDef;

ACvoltage_TypeDef s_stACvoltage;

/* Private function prototypes -----------------------------------------------*/
static void Voltage_Write(uint16_t val);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Voltage_Extract.
 * @note   None.
 * @param  arg.
 * @param  size.
 * @retval None.
 */
void Voltage_Extract(void* arg, uint8_t size)
{
	uint8_t i;
	uint8_t checksum;
	uint32_t Vol_p_reg = 0;
	uint32_t Vol_reg = 0;
	uint16_t Vol;
	uint8_t *data = arg;
	if (size > 23)
	{
	#if 0	/* Echo */
		HAL_UART_Transmit(DEV_MAINUART_PORT, data, size, 0xff);
	#endif
		/* Check data */
		checksum = 0;
		for (i = 2; i < 23; i++)
		{
			checksum += data[i];
		}
		/* Checksum */
		if (checksum ==  data[CHK_REG])
		{	
			/* Status bit */
			if (data[STATE_REG] != 0xAA)
			{					
				if (data[STATE_REG] == 0x55 || (data[STATE_REG]&0xF9) == 0xf0)
				{
					/* Updated */
					if ( (data[DAT_UPD_REG]&0x40) )
					{																
						Vol_p_reg = 0;
						for (i = 0; i < 3; i++)
						{
							Vol_p_reg <<= 8;
							Vol_p_reg += data[VOL_P_REG_1 + i];
						}
								
						Vol_reg = 0;
						for (i = 0; i < 3; i++)
						{
							Vol_reg <<= 8;
							Vol_reg += data[VOL_REG_1 + i];
						}
					#if 0
						Vol = (uint16_t)(Vol_p_reg / Vol_reg) * 2;
					#else
						Vol = (uint16_t)(Vol_p_reg / Vol_reg) * 3;
					#endif
						Voltage_Write(Vol);
					}
				}
			}		
		}
	}
}

/**
 * @brief  Voltage_Write.
 * @note   None.
 * @param  val.
 * @retval None.
 */
static void Voltage_Write(uint16_t val)
{
	s_stACvoltage.Val = val;
}

/**
 * @brief  Voltage_Read.
 * @note   None.
 * @param  None.
 * @retval Val.
 */
uint16_t Voltage_Read(void)
{
	return s_stACvoltage.Val;
}
