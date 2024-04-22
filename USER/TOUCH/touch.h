#ifndef __TOUCH_H__
#define __TOUCH_H__
	    
#include "ft5206.h"	    

//修改说明 
//V1.1 	20170606
//1，新增对GT9271触摸IC的支持
//2，新增对10点触摸的支持
////////////////////////////////////////////////////////////////////////////////// 


#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了
#define CT_MAX_TOUCH 5	   //电容屏支持的点数,固定为5点

//触摸屏控制器
typedef struct
{
	unsigned char (*init)(void);			//初始化触摸屏控制器
	unsigned char (*scan)(unsigned char);	//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);					//触摸屏校准 
	unsigned int x[CT_MAX_TOUCH]; 			//当前坐标
	unsigned int y[CT_MAX_TOUCH];			//电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
											//x[9],y[9]存储第一次按下时的坐标. 
	unsigned int sta;						//笔的状态 
											//b15:按下1/松开0; 
											//b14:0,没有按键按下;1,有按键按下. 
											//b13~b10:保留
											//b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
											//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
											//b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
											//   1,横屏(适合左右为Y坐标,上下为X坐标的TP) 
											//b1~6:保留.
											//b7:0,电阻屏
											//   1,电容屏
	unsigned char touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev; // 触屏控制器在touch.c里面定义

void TP_Adjust(void); // 触摸屏校准

// 电阻屏/电容屏 共用函数
unsigned char TP_Scan(unsigned char tp); // 扫描
unsigned char TP_Init(void);			 // 初始化

#endif
