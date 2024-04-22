#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "DEV_Config.h"

// IO方向设置
#define CT_SDA_IN()                      \
    {                                    \
        GPIOB->MODER &= ~(3 << (7 * 2)); \
        GPIOB->MODER |= 0 << 7 * 2;      \
    } // PI3输入模式
#define CT_SDA_OUT()                     \
    {                                    \
        GPIOB->MODER &= ~(3 << (7 * 2)); \
        GPIOB->MODER |= 1 << 7 * 2;      \
    } // PI3输出模式
// IO操作函数
// #define CT_IIC_SCL  PHout(6)  //SCL
// #define CT_IIC_SDA  PIout(3)  //SDA
// #define CT_READ_SDA PIin(3)   //输入SDA

#define CT_IIC_SCL(_value) HAL_GPIO_WritePin(CPT_IIC_SCK, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#define CT_IIC_SDA(_value) HAL_GPIO_WritePin(CPT_IIC_SDA, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#define CT_READ_SDA HAL_GPIO_ReadPin(CPT_IIC_SDA)

// IIC所有操作函数
void CT_IIC_Init(void);                            // 初始化IIC的IO口
void CT_IIC_Start(void);                           // 发送IIC开始信号
void CT_IIC_Stop(void);                            // 发送IIC停止信号
void CT_IIC_Send_Byte(unsigned char txd);          // IIC发送一个字节
unsigned char CT_IIC_Read_Byte(unsigned char ack); // IIC读取一个字节
unsigned char CT_IIC_Wait_Ack(void);               // IIC等待ACK信号
void CT_IIC_Ack(void);                             // IIC发送ACK信号
void CT_IIC_NAck(void);                            // IIC不发送ACK信号

#endif
