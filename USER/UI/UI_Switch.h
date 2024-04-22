/**
 * @file UI_Switch.h
 *
 */

#ifndef UI_SWITCH_H
#define UI_SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "UI.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void UI_Switch_Init(void);
void UI_Switch_Task(void);
void UI_Switch_BTN_Write(uint8_t index);
void UI_Switch_WriteState(bool flag);
bool UI_Switch_ButtonHandle(int16_t *Coordinate);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UI_SWITCH_H */
