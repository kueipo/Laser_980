
#ifndef __APP_COMMREQ_H
#define __APP_COMMREQ_H

#define INDEX_TYPE_OPERATE				(uint8_t)(0X83)
#define INDEX_TYPE_READ						(uint8_t)(0X01)
#define INDEX_TYPE_FEEDBACK				(uint8_t)(0X82)
#define INDEX_TYPE_HEARTBEAT			(uint8_t)(0X82)

#define TARGET_LENGTH							(uint8_t)(0X01)
#define TARGET_START_ADDR					(uint8_t)(0X00)	/* it can be modified if needed */

#define DEV_INDEX_MASTER					(uint8_t)(0X10)														/* 0x10 */
#define DEV_INDEX_HANDLE_0				(uint8_t)(DEV_INDEX_MASTER + 0X10)				/* 0x20 */
#define DEV_INDEX_HANDLE_1				(uint8_t)(DEV_INDEX_HANDLE_0 + 0X10)			/* 0x30 */

#define DEV_INDEX_PORTECT					(uint8_t)(0X60)														/* 0x60 */

/* FAN */
#define DEV_INDEX_FAN							(uint8_t)(0X03)
#define FEEDBACK_DIFFERENCE				(uint8_t)(0x01)
#define INDEX_TARGET_FAN_POWER_CONTROL \
																	(uint8_t)(0x00)																	/* 00 */
#define INDEX_TARGET_FAN_TEMPERATURE \
																	TARGET_LENGTH + INDEX_TARGET_FAN_POWER_CONTROL	/* 01 */
#define INDEX_TARGET_FAN_POWER_AUTO \
																	TARGET_LENGTH + INDEX_TARGET_FAN_TEMPERATURE		/* 02 */
#define INDEX_TARGET_FAN_SPEED \
																	TARGET_LENGTH + INDEX_TARGET_FAN_POWER_AUTO			/* 03 */
#define INDEX_TARGET_FAN_NUMBER \
																	TARGET_LENGTH + INDEX_TARGET_FAN_SPEED					/* 04 */
#define INDEX_TARGET_FAN_SELF_CHECK \
																	TARGET_LENGTH + INDEX_TARGET_FAN_NUMBER					/* 05 */

#define INDEX_SYSTEM_READY				(uint8_t)(TARGET_START_ADDR + 0x00)										/* 0x00 */
#define INDEX_OVERTEMP_PROTECT		(uint8_t)(TARGET_LENGTH + INDEX_SYSTEM_READY)					/* 0x01 */
#define INDEX_SET_TEMP_THRESHOLD	(uint8_t)(TARGET_LENGTH + INDEX_OVERTEMP_PROTECT)			/* 0x02 */
#define INDEX_TARGET_WATER_TEMPERATURE \
																	(uint8_t)(TARGET_LENGTH + INDEX_SET_TEMP_THRESHOLD)		/* 0x03 */
#define INDEX_WATER_FLOW_PORTECT	(uint8_t)(TARGET_LENGTH + INDEX_TARGET_WATER_TEMPERATURE)
																																												/* 0x04 */
#define INDEX_TARGET_WATER_SPEED	(uint8_t)(TARGET_LENGTH + INDEX_WATER_FLOW_PORTECT)		/* 0x05 */
#define INDEX_TARGET_WATER_LEVEL	(uint8_t)(TARGET_LENGTH + INDEX_TARGET_WATER_SPEED)		/* 0x06 */
#define SET_LASER_PULSE_WIDTH			(uint8_t)(TARGET_LENGTH + INDEX_TARGET_WATER_LEVEL)		/* 0x07 */
#define INDEX_LASER_PULSE					(uint8_t)(TARGET_LENGTH + SET_LASER_PULSE_WIDTH)			/* 0x08 */
#define INDEX_LASER_FREQUENCY			(uint8_t)(TARGET_LENGTH + INDEX_LASER_PULSE)					/* 0x09 */
#define INDEX_LASER_POWER					(uint8_t)(TARGET_LENGTH + INDEX_LASER_FREQUENCY)			/* 0x0A */
#define INDEX_TARGET_LASERCOUNT_MODIFY \
																	(uint8_t)(TARGET_LENGTH + INDEX_LASER_POWER)					/* 0x0B */
#define INDEX_TARGET_TIME					(uint8_t)(TARGET_LENGTH + INDEX_TARGET_LASERCOUNT_MODIFY)
																																												/* 0x0C */
#define GET_VERSION_MS_A_J				(uint8_t)(TARGET_LENGTH + INDEX_TARGET_TIME)					/* 0x0D */
#define INDEX_KEY_DELAY						(uint8_t)(TARGET_LENGTH + GET_VERSION_MS_A_J)					/* 0x0E */
#define INDEX_ICO_RUNNING					(uint8_t)(TARGET_LENGTH + INDEX_KEY_DELAY)						/* 0x0F */
#define INDEX_HANDPIECE_CONN			(uint8_t)(TARGET_LENGTH + INDEX_ICO_RUNNING)					/* 0x10 */
#define INDEX_HANDPIECE_PROTECT		(uint8_t)(TARGET_LENGTH + INDEX_HANDPIECE_CONN)				/* 0x11 */
#define SET_SAFELOCK_ENABLE				(uint8_t)(TARGET_LENGTH + INDEX_HANDPIECE_PROTECT)		/* 0x12 */
#define INDEX_LASER_MODE					(uint8_t)(TARGET_LENGTH + SET_SAFELOCK_ENABLE)				/* 0x13 */
#define INDEX_LASER_CW_MODE				INDEX_LASER_MODE
#define INDEX_LED_CONFIG					(uint8_t)(TARGET_LENGTH + INDEX_LASER_MODE)						/* 0x14 */
#define INDEX_LASER_NUM_CONFIG		(uint8_t)(TARGET_LENGTH + INDEX_LED_CONFIG)						/* 0x15 */
#define INDEX_RESPOND_VERSION			(uint8_t)(TARGET_LENGTH + INDEX_LASER_NUM_CONFIG)			/* 0x16 */
#define INDEX_COOLER_VOLTAGE			(uint8_t)(TARGET_LENGTH + INDEX_RESPOND_VERSION)			/* 0x17 */
#define INDEX_COOLER_CURRENT			(uint8_t)(TARGET_LENGTH + INDEX_COOLER_VOLTAGE)				/* 0x18 */
#define INDEX_PUMP_VOLTAGE				(uint8_t)(TARGET_LENGTH + INDEX_COOLER_CURRENT)				/* 0x19 */
#define INDEX_PUMP_CURRENT				(uint8_t)(TARGET_LENGTH + INDEX_PUMP_VOLTAGE)					/* 0x1A */
#define INDEX_LASER_CUR						(uint8_t)(TARGET_LENGTH + INDEX_PUMP_CURRENT)					/* 0x1B */
#define INDEX_LASER_PLUSE					(uint8_t)(TARGET_LENGTH + INDEX_LASER_CUR)						/* 0x1C */
#define INDEX_SAFELOCKER_STATE		(uint8_t)(TARGET_LENGTH + INDEX_LASER_PLUSE)					/* 0x1D */
#define INDEX_AC_VOLTAGE					(uint8_t)(TARGET_LENGTH + INDEX_SAFELOCKER_STATE)			/* 0x1E */
#define INDEX_LASER_ENERGY				(uint8_t)(TARGET_LENGTH + INDEX_AC_VOLTAGE)						/* 0x1F */
#define INDEX_FAN_SPEED						(uint8_t)(TARGET_LENGTH + INDEX_LASER_ENERGY)					/* 0x20 */
#define INDEX_LASER_INDICATOR_POWER \
																	(uint8_t)(TARGET_LENGTH + INDEX_FAN_SPEED)						/* 0x21 */
#define INDEX_DC05_INFO						(uint8_t)(TARGET_LENGTH + INDEX_LASER_INDICATOR_POWER)/* 0x22 */
#define INDEX_DC12_INFO						(uint8_t)(TARGET_LENGTH + INDEX_DC05_INFO)						/* 0x23 */
#define INDEX_DCLD_INFO						(uint8_t)(TARGET_LENGTH + INDEX_DC12_INFO)						/* 0x24 */
#define INDEX_MOS_TEMPERATURE			(uint8_t)(TARGET_LENGTH + INDEX_DCLD_INFO)						/* 0x25 */
#define HANDLE_MOTOR_DIRECTION		(uint8_t)(TARGET_LENGTH + INDEX_MOS_TEMPERATURE)			/* 0x26 */
#define HANDLE_UPDATA_PIC					(uint8_t)(TARGET_LENGTH + HANDLE_MOTOR_DIRECTION)			/* 0x27 */
#define HANDLE_POWER_SET					(uint8_t)(TARGET_LENGTH + HANDLE_UPDATA_PIC)					/* 0x28 */
#define HANDLE_TIME_INFO					(uint8_t)(TARGET_LENGTH + HANDLE_POWER_SET)						/* 0x29 */
#define PROTECT_FAN_SPEED_ADC			(uint8_t)(TARGET_LENGTH + HANDLE_TIME_INFO)						/* 0x2A */
#define PROTECT_DC24_ADC					(uint8_t)(TARGET_LENGTH + PROTECT_FAN_SPEED_ADC)			/* 0x2B */
#define PROTECT_CURRENT_ADC				(uint8_t)(TARGET_LENGTH + PROTECT_DC24_ADC)						/* 0x2C */
#define PROTECT_VOLTAGE_ADC				(uint8_t)(TARGET_LENGTH + PROTECT_CURRENT_ADC)				/* 0x2D */
#define PROTECT_PULSEWIDTH				(uint8_t)(TARGET_LENGTH + PROTECT_VOLTAGE_ADC)				/* 0x2E */
#define INDEX_SYSTEM_RUNNING			(uint8_t)(TARGET_LENGTH + PROTECT_PULSEWIDTH)					/* 0x2F */

#define INFO_LASER_GET						(uint8_t)(TARGET_LENGTH + INDEX_SYSTEM_RUNNING)				/* 0x30 */
#define INFO_LASER_CUR						(uint8_t)(TARGET_LENGTH + INFO_LASER_GET)							/* 0x31 */
#define INFO_LASER_WIDTH					(uint8_t)(TARGET_LENGTH + INFO_LASER_CUR)							/* 0x32 */
#define INFO_LASER_ENERGY					(uint8_t)(TARGET_LENGTH + INFO_LASER_WIDTH)						/* 0x33 */
#define INFO_LASER_POWER					(uint8_t)(TARGET_LENGTH + INFO_LASER_ENERGY)					/* 0x34 */

/* add ... here */

#define INDEX_ERROR_CODE						(uint8_t)(INDEX_TARGET_UPDATA - TARGET_LENGTH)			/* FB */
#define INDEX_TARGET_UPDATA					(uint8_t)(INDEX_TARGET_PRODUCT_DATE - TARGET_LENGTH)/* FC */
#define INDEX_TARGET_PRODUCT_DATE		(uint8_t)(INDEX_TARGET_VERSION - TARGET_LENGTH)			/* FD */
#define INDEX_TARGET_VERSION				(uint8_t)(INDEX_SYSTEMRESET - TARGET_LENGTH)				/* FE */
#define INDEX_SYSTEMRESET						(uint8_t)(TARGET_START_ADDR + 0xFF)									/* FF */

/* --------------------------------------------------------------------------------------------------------------------- */

#endif
