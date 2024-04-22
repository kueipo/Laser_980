/**
 * @file UI_Level.h
 *
 */

#ifndef UI_LEVEL_H
#define UI_LEVEL_H

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
void UI_Level_Init(void);
void UI_Level_Task(void);
bool UI_Level_ButtonHandle(int16_t *Coordinate);
void UI_Level_WriteLevel(uint8_t level);
uint8_t UI_Level_ReadLevel(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UI_LEVEL_H */
