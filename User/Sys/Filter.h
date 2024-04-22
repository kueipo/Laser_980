#ifndef _FILTER_H
#define _FILTER_H

#include "main.h"

uint16_t MiddleAverageValueFilter(uint16_t NewData, uint16_t *Queue, uint8_t Length);
uint16_t LimitRangeAverageValueFilter(uint16_t NewData, uint8_t Limit, uint16_t *Queue, uint8_t Length);
uint16_t ArithmeticalAverageValueFilter(uint16_t *Queue, uint8_t Length);

#endif /* _FILTER_H */
