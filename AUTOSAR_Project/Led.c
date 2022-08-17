/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/
#include "Dio.h"
#include "Led.h"

/* LED Configurations Structure */

/************************************************************************************
* Service Name: LED_setOn
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to led on.
************************************************************************************/
void LED_setOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/************************************************************************************
* Service Name: LED_setOff
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to led off.
************************************************************************************/
void LED_setOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/************************************************************************************
* Service Name: LED_refreshOutput
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to referesh led state.
************************************************************************************/
void LED_refreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* re-write the same value */
}

/************************************************************************************
* Service Name: LED_toggle
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to toggle the led.
************************************************************************************/
void LED_toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

/*********************************************************************************************/
