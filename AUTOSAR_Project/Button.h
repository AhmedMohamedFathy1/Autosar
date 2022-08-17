/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.h
 *
 * Description: Header file for Button Module.
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

/* Id for the company in the AUTOSAR
 *  example Ahmed Mohamed Fathy's ID = 1111 :) */
#define DIO_VENDOR_ID    (1111U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_AR_RELEASE_PATCH_VERSION   (3U)


/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Dio_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"


#include "Std_Types.h"

/* Button State according to its configuration PULL UP/Down */
#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH

/* Set the Button Port */
#define BUTTON_PORT DioConf_SW1_PORT_NUM

/* Set the Button Pin Number */
#define BUTTON_PIN_NUM DioConf_SW1_CHANNEL_NUM

#define  Initial_Pressed_Number    (0u) 

#define  Final_Pressed_Number    (3u) 


/* 
 * Description: 1. Fill the button configurations structure 
 *              2. Set the PIN direction which the button is connected as INPUT pin
 *              3. Set the pin internal resistor as pull-up resistor 
 */

/* Description: Read the Button state Pressed/Released */
uint8 BUTTON_getState(void);

/* 
 * Description: This function is called every 20ms by Os Task and it responsible for Updating 
 *              the BUTTON State. it should be in a PRESSED State if the button is pressed for 60ms.
 *		and it should be in a RELEASED State if the button is released for 60ms.
 */   
void BUTTON_refreshState(void);


/* Function for DIO Get Version Info API */
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

    
#endif /* BUTTON_H */
