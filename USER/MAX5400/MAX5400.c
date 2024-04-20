
/* Includes ------------------------------------------------------------------*/
#include "MAX5400/MAX5400.h"
#include "Sys/Delay.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define Delay_ms(x)   				HAL_Delay(x)
#define Max5400_Delay(x)			delay_us(x)

/* Private function prototypes -----------------------------------------------*/

/* Private functions --------------------------------------------------------*/
/**
  * @brief  Max5400_Delay.
  * @note   None.
  * @param  time.
  * @retval	None.
  */
#ifndef Max5400_Delay
static void Max5400_Delay(uint16_t time)
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
  * @brief  Max5400_Init.
  * @note   None.
  * @param  None.
  * @retval	None.
  */
void Max5400_Init(void)
{
	Max5400_CS_HIGH();
	Max5400_SCLK_LOW();
	Max5400_SDA_HIGH();
}

/**
  * @brief  Max5400_WriteByte.
  * @note   None.
  * @param  data.
  * @retval	None.
  */
void Max5400_WriteByte(uint8_t data)
{			   	
	Max5400_CS_LOW();
	Max5400_SCLK_LOW();
	Max5400_Delay(1);
	
	for (uint8_t i = 0; i < 8; i++)
	{	
		if ( (data & 0x80) )
		{
			Max5400_SDA_HIGH();
		}
		else
		{
			Max5400_SDA_LOW();
		}
		
		data <<= 1;
		
		Max5400_Delay(1);
		Max5400_SCLK_HIGH();
		Max5400_Delay(1);
		Max5400_SCLK_LOW();
		Max5400_Delay(1);
	}
	
	Max5400_CS_HIGH();
	Max5400_Delay(1);  
}
