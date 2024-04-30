//<<< Use Configuration Wizard in Context Menu >>>

#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

/* Board Info ----------------------------------------------------------------*/
// <h>Board Info
// <i>Board info
	
	//	<s.10>Name
	//	<i>Board Name
	#define BOARD_Name "980P"
	
	// <o>Firmware Version
	// <10000-999999>
	// <i>Enter Firmware Version Rang <10000 - 999999>
	#define BSP_VERSION		(uint16_t)10001
	
	// <o>Hardware Version
	// <i>Hardware Version Select
	//  <0=> V1
	//  <1=> V2
		#define HARDWARE_SELECT		0
		#if   (HARDWARE_SELECT == 0)
			#define BSP_V01
		#elif (HARDWARE_SELECT == 1)
			#define BSP_V02
		#endif

// </h>

//<<< end of configuration section >>>

#endif /* __CONFIGURE_H__ */


/* ---------------------------------------------------------------------------*/
#define IAP_FLAG_808_ADDR_OFFSET					0X0000	//0X0000
#define IAP_FLAG_808_PROTECT_ADDR_OFFSET	0X0000	//0X0004

#define IAP_FLAG_MASSAGER_ADDR_OFFSET							0X0008	//0X0008
#define IAP_FLAG_MASSAGER_PROTECT_ADDR_OFFSET			0X000C	//0X000C

#define IAP_FLAG_980_ADDR_OFFSET					0X0010					//0X0010
#define IAP_FLAG_980_PROTECT_ADDR_OFFSET	IAP_FLAG_980_ADDR_OFFSET + 4	//0X0014
/* ---------------------------------------------------------------------------*/
#define IAP_FLAG_ADDR_SETOFF		IAP_FLAG_980_PROTECT_ADDR_OFFSET //customize

/* example ------------------------------------------------------------- */
#if 0

/* Download fac --------------------------------------------------------------*/
// <h>Download Config
// <i>Download to fac erea Enable or Disable
	// <c1>Enable FAC erea
	// <i>Enable Download FAC erea
	//#define ENABLE_DOWNLOAD_FAC
	// </c>

// </h>

/* Debug Config --------------------------------------------------------------*/
// <h>Debug Config
// <i>Debug option Enable or Disable
	// <o>Storage Classer Select
	// <i>Storage Classer Select
	//  <0=> atuo
	//  <1=> static
		#define STORAGE_CLASSES_SELECT	 0
		#if   (STORAGE_CLASSES_SELECT == 1)
			#define STORAGE_CLASSES	static
		#else
			#define STORAGE_CLASSES
		#endif
// </h>

/* Console --------------------------------------------------------------------*/
// <h>Console Config
// <i>Console Config

	/* Main -------------------------------------------------------------------*/
	// <e> Enable Main Console
	#define EN_MAIN_CONSOLE	1
		// <o>Main Console Config
		// <i>Main Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_MAIN_CONSOLE
			#define ENABLE_MAIN_CONSOLE
			#define MAIN_SELECT		0
			#if   (MAIN_SELECT == 0)
				#define ENABLE_UART_0				1
				#define MAIN_CONSOLE_PORT		UART_0
			#elif (MAIN_SELECT == 1)
				#define ENABLE_UART_1				1
				#define MAIN_CONSOLE_PORT		UART_1
			#elif (MAIN_SELECT == 2)
				#define ENABLE_UART_2				1
				#define MAIN_CONSOLE_PORT		UART_2
			#elif (MAIN_SELECT == 3)
				#define ENABLE_UART_3				1
				#define MAIN_CONSOLE_PORT		UART_3
			#elif (MAIN_SELECT == 4)
				#define ENABLE_UART_4				1
				#define MAIN_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>
	
// </h>

	/* AC -----------------------------------------------------------------*/
	// <e> Enable AC Console
		#define EN_AC_CONSOLE	0
		// <o>AC Console Config
		// <i>AC Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_AC_CONSOLE
			#define ENABLE_AC_CONSOLE
			#define AC_SELECT		1
			#if   (AC_SELECT == 0)
				#define AC_CONSOLE_PORT		UART_0
			#elif (AC_SELECT == 1)
				#define AC_CONSOLE_PORT		UART_1
			#elif (AC_SELECT == 2)
				#define AC_CONSOLE_PORT		UART_2
			#elif (AC_SELECT == 3)
				#define AC_CONSOLE_PORT		UART_3
			#elif (AC_SELECT == 4)
				#define AC_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>
	
	/* Protect ----------------------------------------------------------------*/
	// <e> Enable Protect Console
		#define EN_PROTECT_CONSOLE	1
		// <o>Protect Console Config
		// <i>Protect Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_PROTECT_CONSOLE
			#define ENABLE_PROTECT_CONSOLE
			#define PROTECT_SELECT		1
			#if   (PROTECT_SELECT == 0)
				#define PROT_CONSOLE_PORT		UART_0
			#elif (PROTECT_SELECT == 1)
				#define PROT_CONSOLE_PORT		UART_1
			#elif (PROTECT_SELECT == 2)
				#define PROT_CONSOLE_PORT		UART_2
			#elif (PROTECT_SELECT == 3)
				#define PROT_CONSOLE_PORT		UART_3
			#elif (PROTECT_SELECT == 4)
				#define PROT_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>
	
	/* Fan ----------------------------------------------------------------*/
	// <e> Enable Fan Console
		#define EN_FAN_CONSOLE	0
		// <o>Fan Console Config
		// <i>Fan Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_FAN_CONSOLE
			#define ENABLE_FAN_CONSOLE
			#define FAN_SELECT		1
			#if   (FAN_SELECT == 0)
				#define FAN_CONSOLE_PORT		UART_0
			#elif (FAN_SELECT == 1)
				#define FAN_CONSOLE_PORT		UART_1
			#elif (FAN_SELECT == 2)
				#define FAN_CONSOLE_PORT		UART_2
			#elif (FAN_SELECT == 3)
				#define FAN_CONSOLE_PORT		UART_3
			#elif (FAN_SELECT == 4)
				#define FAN_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>
	
	/* Handpiece_0 --------------------------------------------------------*/
	// <e> Enable Handpiece 0 Console
		#define EN_HANDPICEC_0_CONSOLE	0
		// <o>Handpiece 0 Console Config
		// <i>Handpiece 0 Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_HANDPIECE_0_CONSOLE
			#define ENABLE_HANDPIECE_0_CONSOLE
			#define HANDPIECE_0_SELECT		1
			#if   (HANDPIECE_0_SELECT == 0)
				#define HANDPIECE_0_CONSOLE_PORT		UART_0
			#elif (HANDPIECE_0_SELECT == 1)
				#define HANDPIECE_0_CONSOLE_PORT		UART_1
			#elif (HANDPIECE_0_SELECT == 2)
				#define HANDPIECE_0_CONSOLE_PORT		UART_2
			#elif (HANDPIECE_0_SELECT == 3)
				#define HANDPIECE_0_CONSOLE_PORT		UART_3
			#elif (HANDPIECE_0_SELECT == 4)
				#define HANDPIECE_0_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>
	
	/* Handpiece_1 --------------------------------------------------------*/
	// <e> Enable Handpiece Console
		#define EN_HANDPICEC_1_CONSOLE	0
		// <o>Handpiece 1 Console Config
		// <i>Handpiece 1 Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		//  <2=> UART_2
		//  <3=> UART_3
		//  <4=> UART_4	
		#if EN_HANDPIECE_1_CONSOLE
			#define ENABLE_HANDPIECE_1_CONSOLE
			#define HANDPIECE_1_SELECT		1
			#if   (HANDPIECE_1_SELECT == 0)
				#define HANDPIECE_1_CONSOLE_PORT		UART_0
			#elif (HANDPIECE_1_SELECT == 1)
				#define HANDPIECE_1_CONSOLE_PORT		UART_1
			#elif (HANDPIECE_1_SELECT == 2)
				#define HANDPIECE_1_CONSOLE_PORT		UART_2
			#elif (HANDPIECE_1_SELECT == 3)
				#define HANDPIECE_1_CONSOLE_PORT		UART_3
			#elif (HANDPIECE_1_SELECT == 4)
				#define HANDPIECE_1_CONSOLE_PORT		UART_4
			#endif
		#endif
	// </e>

/* FAL ------------------------------------------------------------------------*/
// <h>FAL Config
// <i>FAL Enable or Disable
	// <c1>Enable FAL Driver Component
	// <i>Enable FAL Driver Component
	#define	ENABLE_FAL_SUPPORT
	// </c>
	
// </h>

/* EF ------------------------------------------------------------------------*/
// <h>EF Config
// <i>Easy Flash Enable or Disable
	// <c1>Enable EF Driver Component
	// <i>Enable Easy Flash Driver Component
	#define ENABLE_EL_SUPPORT
	// </c>

// </h>

// <e>MCU ADC CH1 Param Config
//  <o>MCU ADC CH1 AF Port
//   <i> Default:PC1
//   <0=> PC1
//   <1=> PC2
#define MSP_ADC_CH1_AF_PORT 0
// </e>

/* VAL ------------------------------------------------------------------------*/
//<h>VAL
//	<o>VAL TYPE
//	<i>1：TYPE0    2:TYPE2
//	<1=>1 <2=>2 
	#define CARD_TYPE	2

//	<o>PRESET VAL
//	<0000-9999>
//	<i> 0 - 9999
	#define BAR_CODE 6666
//</h>

/* SFUD -----------------------------------------------------------------------*/
// <h>SFUD Config
// <i>SFUD Enable or Disable
	// <c1>Enable SFUD Driver Component
	// <i>Enable SFUD Driver Component
	//#define ENABLE_SFUD_SUPPORT
	// </c>
// </h>

/* EF -------------------------------------------------------------------------*/
// <h>EF Config
// <i>Easy Flash Enable or Disable
	// <c1>Enable EF Driver Component
	// <i>Enable Easy Flash Driver Component
	//#define ENABLE_EL_SUPPORT
	// </c>

// </h>

#if 0
	/* Fan --------------------------------------------------------------------*/
	// <o>Fan Console Config
	// <i>FAN Console Uart Select
	//  <0=> UART_0
	//  <1=> UART_1
	//  <2=> UART_2
	//  <3=> UART_3
	//  <4=> UART_4
	#define FAN_SELECT		1
	#if   (FAN_SELECT == 0)
		#define FAN_CONSOLE_PORT		UART_0
	#elif (FAN_SELECT == 1)
		#define FAN_CONSOLE_PORT		UART_1
	#elif (FAN_SELECT == 2)
		#define FAN_CONSOLE_PORT		UART_2
	#elif (FAN_SELECT == 3)
		#define FAN_CONSOLE_PORT		UART_3
	#elif (FAN_SELECT == 4)
		#define FAN_CONSOLE_PORT		UART_4
	#endif
#endif

// <h> External Bus Interface (EBI)

//   <e.13> Enable Chip Select 0 (CSR0)
//     <o.20..31> BA: Base Address <0x0-0xFFF00000:0x100000><#/0x100000>
//                 <i> Start Address for Chip Select Signal
//     <o.7..8>   PAGES: Page Size      <0=> 1M Byte    <1=> 4M Bytes
//                                       <2=> 16M Bytes  <3=> 64M Bytes
//                 <i> Selects Active Bits in Base Address
//     <o.0..1>   DBW: Data Bus Width   <1=> 16-bit     <2=> 8-bit
//     <o.12>     BAT: Byte Access Type <0=> Byte-write
//                                      <1=> Byte-select
//     <e.5>      WSE: Enable Wait State Generation
//       <o.2..4>   NWS: Number of Standard Wait States <1-8><#-1>
//     </e>
//     <o.9..11>  TDF: Data Float Output Time <0-7>
//                 <i> Number of Cycles Added after the Transfer
//   </e>
#define MSP_UART0_RX_MODE 0x00E02F26

/***************************Temperature、Speed********************************/
//<h>Temperature and Speed Config

	//<o>Fan Speed
	//<i>set fan speed
	#define FAN_SPEED	250

	//<o>Temperature Preset Val
	//<0-500>
	//<i>range 0 - 500
	#define TEMP	0
	
//</h>

//<h>String
//	<s>sys_star
//	<i>sys_star ing
	#define SYS_STAR "system start ..."

//	<s.50>sys_check
//	<i>sys_check ing
	#define SYS_CHECK "system check ..."
//</h>

//<h> this is a heading 
//	<e.3>this is an options bit 3
//	</e>
//	<e.2>this is an options bit 2
//	</e>
//	<e.0>this is an options bit 0
//	</e>
	uint8_t tmp=13;	
//</h>

//<h> this is a heading 
//	<i> head start form here!
//	<q> this is single bitenable
	#define  BitEnalbe 1
//</h>

//<h> this is a heading 
//<i> head start form here!
//	<q.0> this is single bitenable bit 0
//	<q.1> this is single bitenable bit 1
//	<q.7> this is single bitenable bit 7
	#define  BitEnalbe 0x00
//</h>

//使用说明
//标题命令字<h> 和 </h>
//<h>和</h>必须成对出现，<h>表示一个段落（组）开始，</h>表示段落（组）结束，如果只有<h>没有</h>系统就会报错。

//使能组<e>和</e>
//和<h>类似，可以勾选则为1，否则为0。通过<e.n> 命令，n表示第几位。

//infomations命令<i>
//当鼠标停留在当前的条目的时候可以显示提示信息。该处可以显示汉字。

//输入命令字<o>
//可以进行数据的输入。
//<min-max>对输入值进行限制。
//<min-max:step>可以跟一个步进值，即每次增加或减少的值。
//<1=> 1 <1=> 2下拉进行选择。

//字符串输入<s>
//<s,limit>对输入字符个数限制。

#endif
