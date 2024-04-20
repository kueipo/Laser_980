
/* Includes ------------------------------------------------------------------*/
#include "AD840X/AD840X.h"
#include "Sys/Delay.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define Delay_ms(x)   			HAL_Delay(x)
#define AD840X_Delay(x)			delay_us(x)

/* Private function prototypes -----------------------------------------------*/

/* Private functions --------------------------------------------------------*/
/**
  * @brief  AD840X_Delay.
  * @note   None.
  * @param  time.
  * @retval	None.
  */
#ifndef AD840X_Delay
static void AD840X_Delay(uint16_t time)
{
	uint8_t i;

	while (time)
	{    
		for (i = 0; i < 30; i++)
		{
			;
		}
		time--;
	}
}
#endif

/* External functions --------------------------------------------------------*/
/**
  * @brief  AD840X_Init.
  * @note   None.
  * @param  None.
  * @retval	None.
  */
void AD840X_Init(void)
{
	AD840X_CS_HIGH();
	AD840X_SCLK_LOW();
	AD840X_SDA_HIGH();
}

/**
  * @brief  AD840X_WriteByte.
  * @note   None.
  * @param  addr,data.
  * @retval	None.
  */
void AD840X_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t i;

	AD840X_CS_LOW();
	AD840X_SCLK_LOW();
	AD840X_Delay(1);
	
	addr <<= 6;
	for (i = 0; i < 2; i++)
	{	
		if ( addr & 0x80)
		{
			AD840X_SDA_HIGH();
		}
		else
		{
			AD840X_SDA_LOW();
		}
		
		addr <<= 1;
		
		AD840X_Delay(1);
		AD840X_SCLK_HIGH();
		AD840X_Delay(1);
		AD840X_SCLK_LOW();
		AD840X_Delay(1);
	}

	for (i = 0; i < 8; i++)
	{	
		if ( data & 0x80 )
		{
			AD840X_SDA_HIGH();
		}
		else
		{
			AD840X_SDA_LOW();
		}
		
		data <<= 1;
		
		AD840X_Delay(1);
		AD840X_SCLK_HIGH();
		AD840X_Delay(1);
		AD840X_SCLK_LOW();
		AD840X_Delay(1);
	}
	
	AD840X_CS_HIGH();
	AD840X_Delay(1);  
}
