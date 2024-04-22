/**
 * @file UI.h
 *
 */

#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "UI_Switch.h"
#include "UI_Level.h"
#include "UI_Paint.h"
#include "UI/UI_Img_Map.h"

#include "app/APP_Common.h"

/*********************
 *      DEFINES
 *********************/
#define LCD_WIDTH    240
#define LCD_HEIGHT   240

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/
typedef struct {
	int16_t start_x;
    int16_t start_y;
    int16_t end_x;
    int16_t end_y;
} _Button_Coordinate;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void UI_Init(void);
void UI_Task(void);
void UI_Switch_Next(void);
void UI_Switch_Last(void);
uint8_t UI_Read_PageID(void);
void UI_BTN_Handle(void);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UI_H */
