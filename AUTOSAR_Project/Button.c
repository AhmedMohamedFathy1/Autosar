/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.c
 *
 * Description: Source file for Button Module.
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/

#include "Dio.h"
#include "Button.h"


/* Global variable to hold the button state */
static uint8 g_button_state = BUTTON_RELEASED;





/************************************************************************************
* Service Name: BUTTON_getState
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void).
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to get the button s.
************************************************************************************/

uint8 BUTTON_getState(void)
{
    return g_button_state;
}

/************************************************************************************
* Service Name: BUTTON_refreshState
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None(void).
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refersh the button state.
************************************************************************************/

void BUTTON_refreshState(void)
{
    uint8 state = Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX);
    
    /* Count the number of Pressed times increment if the switch pressed for 20 ms */
    static uint8 g_Pressed_Count  = Initial_Pressed_Number;

    /* Count the number of Released times increment if the switch released for 20 ms */
    static uint8 g_Released_Count = Initial_Pressed_Number;
    
    if(state == BUTTON_PRESSED)
    {
        g_Pressed_Count++;
	g_Released_Count = Initial_Pressed_Number;
    }
    else
    {
	g_Released_Count++;
	g_Pressed_Count = Initial_Pressed_Number;
    }

    if(g_Pressed_Count == Final_Pressed_Number)
    {
	g_button_state = BUTTON_PRESSED;
	g_Pressed_Count       = Initial_Pressed_Number;
	g_Released_Count      = Initial_Pressed_Number;
    }
    else if(g_Released_Count == Final_Pressed_Number)
    {
	g_button_state = BUTTON_RELEASED;
	g_Released_Count      = Initial_Pressed_Number;
	g_Pressed_Count       = Initial_Pressed_Number;
    }
}

