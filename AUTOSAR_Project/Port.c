 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/

#include "Port.h"
#include "Det.h"


#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
/************************************************************************************
* Service Name: Port_Init
*Service ID[hex]:0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
STATIC const Port_Pin_Type * Port_Confg = NULL_PTR;
static uint8 Port_Status = PORT_NOT_INITIALIZED;

void Port_Init(const Port_ConfigType * ConfigPtr )
{
 
  /* Check if port is init or not*/
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
	if (ConfigPtr == NULL_PTR) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		PORT_E_PARAM_CONFIG);
	} 
        else
#endif
{
                volatile uint32 delay = 0;

   SYSCTL_REGCGC2_REG |= 0x3f;
    delay = SYSCTL_REGCGC2_REG; 
              Port_Status = PORT_INITIALIZED;
              uint8 PIN_Index =0;
              
              Port_Confg =  ConfigPtr->Pins;
  
    for(PIN_Index=0 ;PIN_Index <= PORT_CONFIGURED_CHANNLES ;PIN_Index++)
    {
    switch(Port_Confg[PIN_Index].port_num)
    {
      case PORTA: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;      // PORT A Base Address
      break; 
      
      case PORTB: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;        // PORT B Base Address
      break; 
      
      case PORTC: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;        // PORT C Base Address
      break; 
      
      case PORTD: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;        // PORT D Base Address
      break; 
      
      case PORTE: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;        // PORT E Base Address
      break; 
      
      case PORTF: 
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;        // PORT F Base Address
      break; 
    }
    
    /* Enale the clock and star for ports */
    SYSCTL_REGCGC2_REG |= 0x3f;
    delay = SYSCTL_REGCGC2_REG; 
    
      /* If PD7 or PF0 need to open the lock and commit registers */
    
     if(((Port_Confg[PIN_Index].port_num == 3) && (Port_Confg[PIN_Index].pin_num == 7)) || ((Port_Confg[PIN_Index].port_num == 5) && (Port_Confg[PIN_Index].pin_num == 0))) /* PD7 or PF0 */
     {
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                         /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Confg[PIN_Index].pin_num);   /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
     }
     
     /* from PC0 TO PC3 are jtags  */
     else if((Port_Confg[PIN_Index].port_num == 2) && (Port_Confg[PIN_Index].pin_num <= 3))
     {
       /* Do nothing JTAG pins*/
        continue;
     }
     else 
     {
        /*do nothing*/  
     }
    
       if(Mode0 == Port_Confg[PIN_Index].PinMode)
       {
           // clearing the bit to disable alternative function by clearing the GPIOAFSEL Register 
     
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + (PORT_ALT_FUNC_REG_OFFSET)) , (Port_Confg[PIN_Index].pin_num));  
          // clear the PMCx bits for this pins 
         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0X0000000F << ((Port_Confg[PIN_Index].pin_num) * 4));
       }
    
    else 
    {
            // Setting the bit to enable alternative function by clearing the GPIOAFSEL Register 
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + (PORT_ALT_FUNC_REG_OFFSET)) ,Port_Confg[PIN_Index].pin_num);  
            // clear the PMCx bits for this pins 
         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0X0000000F << ((Port_Confg[PIN_Index].pin_num) * 4)); 
            // Set the PMCx bit for this pin
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Port_Confg[PIN_Index].PinMode)&One_Byte_Mask << ((Port_Confg[PIN_Index].pin_num) * 4));      
        
    }
    
        if(Port_Confg[PIN_Index].direction==PORT_PIN_OUT)        
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    // Set bit to be Output
        
         if(Port_Confg[PIN_Index].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Confg[PIN_Index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Confg[PIN_Index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
      } 
   
       else if(Port_Confg[PIN_Index].direction==PORT_PIN_IN)  
        {
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    /* celar bit to be Input */
        
           if(Port_Confg[PIN_Index].resistor == PULL_UP)
            {
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    /* Set bit to be used as Pull up resitor pin */   
            }
         
           else if(Port_Confg[PIN_Index].resistor == PULL_DOWN)     
            {
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    // Set bit to be used as Pull Down resitor pin   
            }
       
           else 
           {
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET),Port_Confg[PIN_Index].pin_num);
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET),Port_Confg[PIN_Index].pin_num); 
           }
        }
       else
       {
       }
        
    if(Port_Confg[PIN_Index].Digital_Value == Digital_Pin)  
    {
        /* Clear bit to disable Analog Function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    
       
       /* Set bit to enable Digital function  */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Confg[PIN_Index].pin_num);       
    }
    else if(Port_Confg[PIN_Index].Digital_Value == Analog_Pin) 
    {
      /* Clear bit to disable digital Function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Confg[PIN_Index].pin_num);      
      
       /* Set bit to enable Analog function  */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Confg[PIN_Index].pin_num);    
      
    }
    
    else 
    {
     /* Do Nothing*/
    }
    
    
    } // for
  }  // else

} // Port Init

#if (PORT_PIN_DIRECTION_CHANGEABLE ==STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
*Service ID[hex]:0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin : Port pin ID number
                   Direction : Port pin direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set the port pin direction 
************************************************************************************/

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
 {
       
     volatile uint32 *Port_Address =NULL_PTR ;
     volatile uint32 delay = 0;
    
	boolean error = FALSE;
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNLES <= Pin)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SET_PIN_MODE_SID , PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        if ( Port_Confg[Pin].ChangableDierction==PORT_PIN_DIR_CHANGEABLE)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_Direction_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
        }
        else
        {
          /* No Action Required */
        }
        
#endif

        {       
  if(FALSE == error)
    if ( Port_Confg[Pin].ChangableDierction==PORT_PIN_DIR_UNCHANGEABLE)
          {
                  return;      
          }
  else {   
     
    switch(Port_Confg[Pin].port_num)
    {
    case PORTA: 
      Port_Address = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;         // PORT A Base Address
      break; 
      
      case PORTB: 
      Port_Address = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;        // PORT B Base Address
      break; 
      
      case PORTC: 
      Port_Address = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;        // PORT C Base Address
      break; 
      
      case PORTD: 
      Port_Address = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;        // PORT D Base Address
      break; 
      
      case PORTE: 
      Port_Address = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;        // PORT E Base Address
      break; 
      
      case PORTF: 
      Port_Address = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;        // PORT F Base Address
      break; 
    }
  
      if(Direction == PORT_PIN_IN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address+PORT_DIR_REG_OFFSET),Pin);    // clear bit to be Input
      
      }
      
        if(Direction == PORT_PIN_OUT)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address+PORT_DIR_REG_OFFSET),Pin);    // Set bit to be Output
      
      }
         
  }      
 }
}

#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]:0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Versioninfo , Pointer to where to store the version information of this module.
* Return value: None
* Description: Set the port pin direction 
************************************************************************************/

void Port_RefreshPortDirection(void)
{
  volatile uint32 *Port_Address =NULL_PTR ;
  volatile uint32 delay = 0;
  boolean error = FALSE;

  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_DIRECTION_SID , PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

#endif

if(FALSE == error)
 {   
     for(int i=0;i<PORT_CONFIGURED_CHANNLES;i++)
        {
          if((Port_Confg[i].port_num == 2) && (Port_Confg[i].pin_num <= 3))
           {
             /* Do nothing JTAG pins*/
                continue;
           }
      else if (Port_Confg[i].ChangableDierction==PORT_PIN_DIR_UNCHANGEABLE)
           {
    switch(Port_Confg->port_num)
    {
    case 0: 
      Port_Address = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;         // PORT A Base Address
      break; 
      
      case 1: 
      Port_Address = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;        // PORT B Base Address
      break; 
      
      case 2: 
      Port_Address = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;        // PORT C Base Address
      break; 
      
      case 3: 
      Port_Address = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;        // PORT D Base Address
      break; 
      
      case 4: 
      Port_Address = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;        // PORT E Base Address
      break; 
      
      case 5: 
      Port_Address = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;        // PORT F Base Address
      break; 
    }
    if(Port_Confg[i].direction==PORT_PIN_OUT)        
      {
                /* Set bit to be Output*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address+PORT_DIR_REG_OFFSET),Port_Confg[i].pin_num);   
      }
    
     else if(Port_Confg[i].direction==PORT_PIN_IN)        
      {
                 /* Set bit to be Input*/
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address+PORT_DIR_REG_OFFSET),Port_Confg[i].pin_num);    
      }
           }
     
    
    else 
    {
    
    }
}
}
}

#if (PORT_VERSION_INFO_API==STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
*Service ID[hex]:0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Versioninfo , Pointer to where to store the version information of this module.
* Return value: None
* Description: Set the port pin direction 
************************************************************************************/

void Port_GetVersionInfo(const Std_VersionInfoType* versioninfo)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
  
    if(NULL_PTR == versioninfo)
    {
     Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    
    }
    else
    {
#endif
      (*(uint16*)versioninfo->vendorID) = (uint16)PORT_VENDOR_ID;
      (*(uint16*)versioninfo->moduleID) = (uint16)PORT_MODULE_ID; 
      (*(uint8*)versioninfo->sw_major_version) = PORT_SW_MAJOR_VERSION;
      (*(uint8*)versioninfo->sw_minor_version) = PORT_SW_MINOR_VERSION;
      (*(uint8*)versioninfo ->sw_patch_version) = PORT_SW_PATCH_VERSION;
    }
}
#endif


/************************************************************************************
* Service Name: Port_SetPinMode
*Service ID[hex]:0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant 
* Parameters (in): Pin : Port pin ID number
* Mode : New Port pin Mode om port pin 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set the port pin Mode 
************************************************************************************/

 void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
    {
             
     volatile uint32 *Port_Address =NULL_PTR ;
     volatile uint32 delay = 0;
    
     boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNLES <= Pin)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SET_PIN_MODE_SID , PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        /* Check if Incorrect Port Pin ID passed */
        if (PORT_E_PARAM_PIN == STD_ON)
        {
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_Direction_SID, PORT_E_PARAM_INVALID_MODE);
        } 
        else
         {
	/* No Action Required */
         }
        
        /* Check if the Pin changable  or not  */
        if (PORT_PIN_DIRECTION_CHANGEABLE == STD_ON)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				Port_SET_PIN_MODE_SID , PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        /* Check if the Mode valid or not valid  */
    
        

#endif        
        {
           Port_Status = PORT_INITIALIZED;
     if(FALSE == error)
	{  
    switch(Port_Confg[Pin].port_num)
    {
      case PORTA: 
      Port_Address = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;         // PORT A Base Address
      break; 
      
      case PORTB: 
      Port_Address = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;        // PORT B Base Address
      break; 
      
      case PORTC: 
      Port_Address = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;        // PORT C Base Address
      break; 
      
      case PORTD: 
      Port_Address = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;        // PORT D Base Address
      break; 
      
      case PORTE: 
      Port_Address = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;        // PORT E Base Address
      break; 
      
      case PORTF: 
      Port_Address = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;        // PORT F Base Address
      break; 
    }
    
    if(Mode == Mode0)
       {
           // clearing the bit to disable alternative function by clearing the GPIOAFSEL Register 
     
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address + (PORT_ALT_FUNC_REG_OFFSET)) , Pin);  
          // clear the PMCx bits for this pins 
         *(volatile uint32 *)((volatile uint8 *)Port_Address + PORT_CTL_REG_OFFSET) &= ~(0X0000000F << (Pin * 4));
       }
    
    else 
    {
      // Setting the bit to enable alternative function by clearing the GPIOAFSEL Register 
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Address + (PORT_ALT_FUNC_REG_OFFSET)) ,Pin);  
        // clear the PMCx bits for this pins 
         *(volatile uint32 *)((volatile uint8 *)Port_Address + PORT_CTL_REG_OFFSET) &= ~(0X0000000F << (Pin * 4)); 
         // Set the PMCx bit for this pin
        *(volatile uint32 *)((volatile uint8 *)Port_Address + PORT_CTL_REG_OFFSET) |= (Mode&One_Byte_Mask << (Pin * 4));      
    
    }
    
        if(Port_Confg[Pin].Digital_Value == Digital_Pin)  
    {
        /* Clear bit to disable Analog Function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin);    
       
       /* Set bit to enable Digital function  */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Pin);       
    }
    else  if(Port_Confg[Pin].Digital_Value == Analog_Pin) 
    {
      /* Clear bit to disable digital Function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Pin);      
      
       /* Set bit to enable Analog function  */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin);    
      
    }
    
    else 
    {
     /* Do Nothing */ 
    }

  }     
 }
}

