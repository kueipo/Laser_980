//<<< Use Configuration Wizard in Context Menu >>>

#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

/* Board Info ----------------------------------------------------------------*/
// <h>Board Info
// <i>Board info
	
	//	<s.10>Name
	//	<i>Board Name
	#define BOARD_Name "980Por"
	
	// <o>Version
	// <10000-999999>
	// <i>Enter version rang <10000 - 999999>
	#define BSP_VERSION		10000
	
	// <o>Type
	// <i>Type Select
	//  <0=> Master
	//  <1=> Fan
	//  <2=> Portect
	//  <3=> HandlePiece0
	//  <4=> HandlePiece1
		#define TYPE_SELECT		2
		#if   (TYPE_SELECT == 0)
			#define DEVICE_TYPE		DEV_INDEX_MASTER
		#elif (TYPE_SELECT == 1)
			#define DEVICE_TYPE		DEV_INDEX_FAN
		#elif (TYPE_SELECT == 2)
			#define DEVICE_TYPE		DEV_INDEX_PORTECT
		#elif (TYPE_SELECT == 3)
			#define DEVICE_TYPE		DEV_INDEX_HANDLE_0
		#elif (TYPE_SELECT == 4)
			#define DEVICE_TYPE		DEV_INDEX_HANDLE_1
		#else
			#define DEVICE_TYPE		DEV_INDEX_MASTER
		#endif

// </h>

/* SFUD ----------------------------------------------------------------------*/
// <h>SFUD Config
// <i>SFUD Enable or Disable
	// <c1>Enable SFUD Driver Component
	// <i>Enable SFUD Driver Component
	//#define ENABLE_SFUD_SUPPORT
	// </c>

// </h>

/* FAL -----------------------------------------------------------------------*/
// <h>FAL Config
// <i>FAL Enable or Disable
	// <c1>Enable FAL Driver Component
	// <i>Enable FAL Driver Component
	//#define ENABLE_FAL_SUPPORT
	// </c>
	
// </h>

/* EF ------------------------------------------------------------------------*/
// <h>EF Config
// <i>Easy Flash Enable or Disable
	// <c1>Enable EF Driver Component
	// <i>Enable Easy Flash Driver Component
	//#define ENABLE_EL_SUPPORT
	// </c>

// </h>

/* Console -----------------------------------------------------------------------*/
// <h>Console Config
// <i>Console Config
	
	/* Main -------------------------------------------------------------------*/
	// <e> Enable Main Console
	#define EN_MAIN_CONSOLE	1
		// <o>Main Console Config
		// <i>Main Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
		#if EN_MAIN_CONSOLE
			#define ENABLE_MAIN_CONSOLE
			#define MAIN_SELECT		0
			#if   (MAIN_SELECT == 0)
				#define MAIN_CONSOLE_PORT		UART_0
			#elif (MAIN_SELECT == 1)
				#define MAIN_CONSOLE_PORT		UART_1
			#elif (MAIN_SELECT == 2)
				#define MAIN_CONSOLE_PORT		UART_2
			#elif (MAIN_SELECT == 3)
				#define MAIN_CONSOLE_PORT		UART_3
			#elif (MAIN_SELECT == 4)
				#define MAIN_CONSOLE_PORT		UART_4
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
		
	/* Protect ----------------------------------------------------------------*/
	// <e> Enable Protect Console
		#define EN_PROTECT_CONSOLE	0
		// <o>Protect Console Config
		// <i>Protect Console Uart Select
		//  <0=> UART_0
		//  <1=> UART_1
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
	
// </h>

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


//<<< end of configuration section >>>
#endif

/*

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

标题命令字<h> 和 </h>
<h>和</h>必须成对出现，<h>表示一个段落（组）开始，</h>表示段落（组）结束，如果只有<h>没有</h>系统就会报错。

使能组<e>和</e>
和<h>类似，可以勾选则为1，否则为0。通过<e.n> 命令，n表示第几位。

infomations命令<i>
当鼠标停留在当前的条目的时候可以显示提示信息。该处可以显示汉字。

输入命令字<o>
可以进行数据的输入。
<min-max>对输入值进行限制。
<min-max:step>可以跟一个步进值，即每次增加或减少的值。
<1=> 1 <1=> 2下拉进行选择。

字符串输入<s>
<s,limit>对输入字符个数限制。

*/
