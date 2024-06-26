
/* Includes ------------------------------------------------------------------*/
#include "iap/inc/iap.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define SCB_AIRCR (*(volatile unsigned long *)0xE000ED0C) /* Reset control Address Register */
#define SCB_RESET_VALUE 0x05FA0004                        /* Reset value, write to SCB_AIRCR can reset cpu */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  reset CPU
 * @param  None
 * @retval None
 */
void cpu_reset(void)
{
  SCB_AIRCR = SCB_RESET_VALUE;
}

/**
 * @brief  Convert an Integer to a string
 * @param  p_str: The string output pointer
 * @param  intnum: The integer to be converted
 * @retval None
 */
void Int2Str(uint8_t *p_str, uint32_t intnum)
{
  uint32_t i, divider = 1000000000, pos = 0, status = 0;

  for (i = 0; i < 10; i++)
  {
    p_str[pos++] = (intnum / divider) + 48;

    intnum = intnum % divider;
    divider /= 10;
    if ((p_str[pos - 1] == '0') & (status == 0))
    {
      pos = 0;
    }
    else
    {
      status++;
    }
  }
}

/**
 * @brief  Convert a string to an integer
 * @param  p_inputstr: The string to be converted
 * @param  p_intnum: The integer value
 * @retval 1: Correct
 *         0: Error
 */
uint32_t Str2Int(uint8_t *p_inputstr, uint32_t *p_intnum)
{
  uint32_t i = 0, res = 0;
  uint32_t val = 0;

  if ((p_inputstr[0] == '0') && ((p_inputstr[1] == 'x') || (p_inputstr[1] == 'X')))
  {
    i = 2;
    while ((i < 11) && (p_inputstr[i] != '\0'))
    {
      if (ISVALIDHEX(p_inputstr[i]))
      {
        val = (val << 4) + CONVERTHEX(p_inputstr[i]);
      }
      else
      {
        /* Return 0, Invalid input */
        res = 0;
        break;
      }
      i++;
    }

    /* valid result */
    if (p_inputstr[i] == '\0')
    {
      *p_intnum = val;
      res = 1;
    }
  }
  else /* max 10-digit decimal input */
  {
    while ((i < 11) && (res != 1))
    {
      if (p_inputstr[i] == '\0')
      {
        *p_intnum = val;
        /* return 1 */
        res = 1;
      }
      else if (((p_inputstr[i] == 'k') || (p_inputstr[i] == 'K')) && (i > 0))
      {
        val = val << 10;
        *p_intnum = val;
        res = 1;
      }
      else if (((p_inputstr[i] == 'm') || (p_inputstr[i] == 'M')) && (i > 0))
      {
        val = val << 20;
        *p_intnum = val;
        res = 1;
      }
      else if (ISVALIDDEC(p_inputstr[i]))
      {
        val = val * 10 + CONVERTDEC(p_inputstr[i]);
      }
      else
      {
        /* return 0, Invalid input */
        res = 0;
        break;
      }
      i++;
    }
  }

  return res;
}

/**
 * @brief  Print a string on the HyperTerminal
 * @param  p_string: The string to be printed
 * @retval None
 */
void Serial_PutString(char *p_string)
{
#if ENABLE_PRINT_DEBUG
  uint16_t length = 0;

  while (p_string[length] != '\0')
  {
    length++;
  }
	Data_Transmit((uint8_t *)p_string, length, TX_TIMEOUT);
#else
  UNUSED(p_string);
#endif
}

/**
 * @brief  Transmit a byte to the HyperTerminal
 * @param  param The byte to be sent
 * @retval HAL_StatusTypeDef HAL_OK if OK
 */
HAL_StatusTypeDef Serial_PutByte(uint8_t param)
{
  /* May be timeouted... */
  return Data_Transmit(&param, 1, TX_TIMEOUT);
}

/* Flash Read/Write ----------------------------------------------------------*/
int Read_Flash(uint32_t addr, uint8_t *buf, size_t size)
{
	return fal_partition_read(opt_area, addr, buf, size);
}

int Write_Flash(uint32_t addr, const uint8_t *buf, size_t size)
{
	return fal_partition_write(opt_area, addr, buf, size);
}

int Erase_Flash(uint32_t addr, size_t size)
{
	return fal_partition_erase(opt_area, addr, size);
}

/* Data transmission ---------------------------------------------------------*/
HAL_StatusTypeDef Data_Transmit(uint8_t *pData, size_t Size, uint32_t Timeout)
{
	if (g_huart->gState == HAL_UART_STATE_TIMEOUT)
  {
    g_huart->gState = HAL_UART_STATE_READY;
  }
	
	return HAL_UART_Transmit(g_huart, pData, Size, Timeout);
}

HAL_StatusTypeDef Data_Receive(uint8_t *pData, size_t Size, uint32_t Timeout)
{
	return HAL_UART_Receive(g_huart, pData, Size, Timeout);
}
