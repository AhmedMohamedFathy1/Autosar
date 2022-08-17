 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H


/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Precompile and Post Build option for setting the Pin direction,
   according to its mode E.g. a pin used for an ADC must be configured
   to be an in port. */
#define PORT_PIN_DIRECTION                    (STD_ON)

/* Precompile and Post Build option for changing a Pin
   direction during runtime */
#define PORT_PIN_DIRECTION_CHANGEABLE         (STD_ON)

/* Precompile and Post Build option for setting initial Pin mode
   to be ADC, DIO, LIN, .. */
#define PORT_PIN_INITIAL_MODE                 (STD_ON)

/* Precompile and Post Build option for setting
   Port Pin Level value from Port pin list. */
#define PORT_PIN_LEVEL_VALUE                  (STD_ON)

/* Precompile and Post Build option for setting Pin mode
to be ADC, DIO, LIN, .. */
#define PORT_PIN_MODE                         (STD_ON)

/* Precompile and Post Build option for Port pin mode changeability */
#define PORT_PIN_MODE_CHANGEABLE              (STD_ON)

   /* Number of pins in the Microcontroller*/
#define PORT_CONFIGURED_CHANNLES              (43U)
     
   
#define PORT_PIN_LEVEL_HIGH                  STD_HIGH
#define PORT_PIN_LEVEL_LOW                   STD_LOW

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

#define One_Byte_Mask    0x0f   // Byte (1111) for masking 
   
   
/* Port Pin MODE value  */
#define PORT_PIN_MODE_NOT_USED	(11U)
#define PORT_PIN_MODE_TRIGGER_ADC	(12U)

#define PORT_PIN_MODE_ADC		(0U)
#define PORT_PIN_MODE_DIO		(uint8)(0x01)
#define PORT_PIN_MODE_CAN		(2U)
#define PORT_PIN_MODE_GPT		(3U)
#define PORT_PIN_MODE_WDG		(4U)
#define PORT_PIN_MODE_FLEXRAY	        (5U)
#define PORT_PIN_MODE_ICU		(6U)
#define PORT_PIN_MODE_LIN		(7U)
#define PORT_PIN_MODE_MEM		(8U)
#define PORT_PIN_MODE_PWM		(9U)
#define PORT_PIN_MODE_SPI		(10U)

   
   /****    Modes   ****/

#define Mode0		(0U)
#define Mode1		(1u)
#define Mode2		(2U)
#define Mode3		(3U)
#define Mode4		(4U)
#define Mode5	        (5U)
#define Mode6		(6U)
#define Mode7		(7U)
#define Mode8		(8U)
#define Mode9		(9U)
#define Mode14		(14U)
     
#define Port_Default_Mode  (0u)   
     
    /****   Digital Values ****/ 
     
#define Digital_Pin   STD_HIGH
#define Analog_Pin    STD_LOW    
     
   
   /****    Port A  ****/

#define PortA_Pin0    (uint32)0
#define PortA_Pin1    (uint32)1
#define PortA_Pin2    (uint32)2
#define PortA_Pin3    (uint32)3
#define PortA_Pin4    (uint32)4
#define PortA_Pin5    (uint32)5
#define PortA_Pin6    (uint32)6
#define PortA_Pin7    (uint32)7
    
    /****    Port B  ****/

#define PortB_Pin0    (uint32)8
#define PortB_Pin1    (uint32)9
#define PortB_Pin2    (uint32)10
#define PortB_Pin3    (uint32)11
#define PortB_Pin4    (uint32)12
#define PortB_Pin5    (uint32)13
#define PortB_Pin6    (uint32)14
#define PortB_Pin7    (uint32)15
    
    /****    Port C  ****/

#define PortC_Pin0    (uint32)16
#define PortC_Pin1    (uint32)17
#define PortC_Pin2    (uint32)18
#define PortC_Pin3    (uint32)19   
#define PortC_Pin4    (uint32)20
#define PortC_Pin5    (uint32)21
#define PortC_Pin6    (uint32)22
#define PortC_Pin7    (uint32)23
   
    /****    Port D  ****/

#define PortD_Pin0    (uint32)24
#define PortD_Pin1    (uint32)25
#define PortD_Pin2    (uint32)26
#define PortD_Pin3    (uint32)27
#define PortD_Pin4    (uint32)28
#define PortD_Pin5    (uint32)29
#define PortD_Pin6    (uint32)30
#define PortD_Pin7    (uint32)31
    
   /****    Port E  ****/

#define PortE_Pin0    (uint32)32
#define PortE_Pin1    (uint32)33
#define PortE_Pin2    (uint32)34
#define PortE_Pin3    (uint32)35
#define PortE_Pin4    (uint32)36
#define PortE_Pin5    (uint32)37


    /****    Port F  ****/

#define PortF_Pin0    (uint32)38
#define PortF_Pin1    (uint32)39
#define PortF_Pin2    (uint32)40
#define PortF_Pin3    (uint32)41
#define PortF_Pin4    (uint32)42





       
     
#endif /* PORT_CFG_H */