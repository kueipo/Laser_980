
#include "Sys/Filter.h"

// 递推中位值平均滤波法
// 1.方法
// 递推中位值平均滤波法,相当于“中位值滤波法”+“递推平均滤波法”。
// 这种方法是,把连续N(Length)个采样值看成一个队列,队列的长度为N。
// 每次采样到一个新数据放入队尾,并扔掉原来队首的一次数据(先进先出原则)。
// 把队列中的N个数据先去掉一个最大值和一个最小值,然后计算N-2个数据的平均值。
// 2.优点
// 融合了两种滤波法的优点。对于偶然出现的脉冲性干扰,可消除由其引起的采样值偏差。
// 3.缺点
// 由于需要开设队列存储历次采样数据,因此比较消耗RAM。
uint16_t MiddleAverageValueFilter(uint16_t NewData, uint16_t *Queue, uint8_t Length)
{
	uint16_t max;
	uint16_t min;
	uint32_t sum;
	uint8_t i;

	Queue[0] = NewData;
	max = Queue[0];
	min = Queue[0];
	sum = Queue[0];
	
	for (i = Length - 1; i != 0; i--)
	{
		if (Queue[i] > max)
			max = Queue[i];
		else if (Queue[i] < min)
			min = Queue[i];

		sum += Queue[i];
		Queue[i] = Queue[i - 1];
	}

	i = Length - 2;
	sum = sum - max - min + i / 2; // 说明:+(i-2)/2的目的是为了四舍五入
	sum /= i;

	return (uint16_t)sum;
}

// 限幅平均滤波法
// 1.方法
// 相当于“限幅滤波法”+“递推平均滤波法”。每次采样到的新数据先进行限幅处理,再送入队列进行递推平均滤波处理。
// 2.优点
// 融合了两种滤波法的优点。对于偶然出现的脉冲性干扰,可消除由于脉冲干扰所引起的采样值偏差。
// 3.缺点
// 由于需要开设队列存储历次采样数据,因此比较消耗RAM。
uint16_t LimitRangeAverageValueFilter(uint16_t NewData, uint8_t Limit, uint16_t *Queue, uint8_t Length)
{
	uint8_t i;
	uint32_t sum = 0;

	Queue[0] = NewData;

#if 0
	if (((Queue[0] - Queue[1]) > Limit) || ((Queue[1] - Queue[0]) > Limit))
		Queue[0] = Queue[1];
#else	
	if ((Queue[0] - Queue[1]) > Limit)
		Queue[0] = Queue[1] + Limit;
	else if ((Queue[1] - Queue[0]) > Limit)
		Queue[0] = Queue[1] - Limit;
#endif	

	for (i = Length - 1; i != 0; i--)
	{
		sum += Queue[i];
		Queue[i] = Queue[i - 1];
	}
	sum /= Length;

	return (uint16_t)sum;
}

// 算术平均滤波法
// 1.方法
// 连续取N(Length)个采样值进行算术平均运算。N值较大时,信号平滑度较高,但灵敏度较低;N值较小时,信号平滑度较低,但灵敏度较高。
// N值的选取:对于一般流量,N=12;对于压力,N=4.
// 2.优点
// 适用于对一般具有随机干扰的信号进行滤波。这种信号的特点是有一个平均值,信号在某一数值范围附近上下波动。
// 3,缺点
// 对于测量速度较慢或要求数据计算速度较快的实时控制不适用。由于需要开设队列存储历次采样数据,因此比较消耗RAM
uint16_t ArithmeticalAverageValueFilter(uint16_t *Queue, uint8_t Length)
{
	uint8_t i;
	uint32_t sum = 0;

	for (i = 0; i < Length; i++)
	{
		sum += Queue[i];
	}
	sum /= Length;

	return (uint16_t)sum;
}
