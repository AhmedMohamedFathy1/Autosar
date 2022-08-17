 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author:Ahmed Mohamed Fathy
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
#include "Dio.h"
#include "Port_REG.h"


/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio..h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

#define PORT_VENDOR_ID    (1111U)

/* Port Module Id */
#define PORT_MODULE_ID    (120U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)



/*******************************************************************************
 *                      DIO Macro's status                                        *
 *******************************************************************************/
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
#define PORT_E_PARAM_PIN		    (uint8)0x0A

/* Dio_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG                 (uint8)0x0C
   
/* Dio_Init API service called when invalid mode is set */
#define PORT_E_PARAM_INVALID_MODE	    (uint8)0x0D

/* Dio_Init API service called when mode is unchangable */
#define PORT_E_MODE_UNCHANGEABLE	    (uint8)0x0E
   
/* DET code to report Direction is not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B
/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER                (uint8)0x10

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 DIO SWS Document.
 */
#define PORT_E_UNINIT                       (uint8)0xF0

/*******************************************************************************
 *                      API Service Id Macros                                 *
 *******************************************************************************/

   /* Service ID for DIO Init Channel */
#define PORT_INIT_SID 				(uint8)0x00

   /* Service ID for PORT set pin direction  */
#define	PORT_SET_PIN_Direction_SID 		(uint8)0x01
   
   /* Service ID for PORT Refersh pin direction  */
#define	PORT_REFRESH_DIRECTION_SID		(uint8)0x02
   
   /* Service ID for PORT GetVersionInfo */
#define	Port_GET_VERSION_INFO_SID		(uint8)0x03
   
     /* Service ID for PORT set pin Mode  */
#define	Port_SET_PIN_MODE_SID			(uint8)0x04
   
   
      
/*******************************************************************************
 *                                   PIN                                     *
 *******************************************************************************/
   
#define PORT_PIN0 				(Port_PinType)0
#define PORT_PIN1 				(Port_PinType)1
#define PORT_PIN2 				(Port_PinType)2
#define PORT_PIN3 				(Port_PinType)3
#define PORT_PIN4 				(Port_PinType)4
#define PORT_PIN5 				(Port_PinType)5
#define PORT_PIN6 				(Port_PinType)6
#define PORT_PIN7 				(Port_PinType)7

/*******************************************************************************
 *                                   Ports                                     *
 *******************************************************************************/
    
#define PORTA 			   	(uint8)0
#define PORTB 				(uint8)1
#define PORTC 				(uint8)2
#define PORTD 				(uint8)3   
#define PORTE 				(uint8)4
#define PORTF 				(uint8)5   


/* Type definition for Port_PinDirectionType used by the Port APIs */
   /* Description: Enum to hold PIN direction */
typedef enum
{
  PORT_PIN_IN = STD_LOW,
  PORT_PIN_OUT = STD_HIGH
}Port_PinDirectionType;


/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Type definition for Port_PinType used by the Port APIs */

typedef uint32 Port_PinType ; 


/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;
     
/* Description: Enum to hold is dierction changable for PIN or not */

typedef enum
{
  PORT_PIN_DIR_UNCHANGEABLE,PORT_PIN_DIR_CHANGEABLE
  
}Port_PinDirChangeable;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the Mode of pin 
 *      4. the direction of pin --> INPUT or OUTPUT
 *      5. the internal resistor --> Disable, Pull up or Pull down
 *      6. The Intial value STD_HIGH , STD_LOW
 */
typedef struct 
{
    uint8 port_num; 
    uint8 pin_num; 
    Port_PinModeType PinMode; 
    uint8 Digital_Value;
    uint8 direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    Port_PinDirChangeable ChangableDierction;
    
}Port_Pin_Type;

typedef struct 
{
  Port_Pin_Type Pins[PORT_CONFIGURED_CHANNLES]; 
}Port_ConfigType;


  
 
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*  Function to initialze the port */ 

void Port_Init( 
               const Port_ConfigType* ConfigPtr 
               );
/*  Function to set the pin dierction */ 
void Port_SetPinDirection(
                          Port_PinType Pin,
                          Port_PinDirectionType Direction
                          );
/*  Function to refersh the port configuration */ 
void Port_RefreshPortDirection(
                               void 
                               );

/*  Function to set the pin Mode */ 

#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinMode( 
                     Port_PinType Pin, 
                     Port_PinModeType Mode 
                     );
#endif

void Port_SetPinMode( 
                     Port_PinType Pin, 
                     Port_PinModeType Mode);
/*  Function to Autosar version */ 

#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( 
                          const Std_VersionInfoType* versioninfo 
                         );
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
