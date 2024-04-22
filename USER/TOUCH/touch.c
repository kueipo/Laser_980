#include "touch.h" 
#include "delay.h"

//修改说明 
//V1.1 	20170606
//1，新增对GT9271触摸IC的支持
//2，新增对10点触摸的支持
//////////////////////////////////////////////////////////////////////////////////

_m_tp_dev tp_dev = {
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
// 默认为touchtype=0的数据.
// u8 CMD_RDX=0XD0;
// u8 CMD_RDY=0X90;

//////////////////////////////////////////////////////////////////////////////////
// 触摸按键扫描
// tp:0,屏幕坐标;1,物理坐标(校准等特殊场合用)
// 返回值:当前触屏状态.
// 0,触屏无触摸;1,触屏有触摸
unsigned char TP_Scan(unsigned char tp)
{
	return 1;
}

void TP_Adjust(void)
{
	return;
}

// 触摸屏初始化
// 返回值:0,没有进行校准
//        1,进行过校准
unsigned char TP_Init(void)
{
	FT5206_Init();
	tp_dev.scan = FT5206_Scan; // 扫描函数指向GT9147触摸屏扫描
	tp_dev.touchtype |= 0X80;  // 电容屏
	//	tp_dev.touchtype |= lcddev.dir&0X01;//横屏还是竖屏
	return 1;
}
