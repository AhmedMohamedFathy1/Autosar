/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.h
 *
 * Description: Header file for Led Module.
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/
#ifndef LED_H
#define LED_H

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


#include "Std_Types.h"

/* Set the led ON/OFF according to its configuration Positive logic or negative logic */
#define LED_ON  STD_HIGH
#define LED_OFF STD_LOW

/* Set the LED Port */
#define LED_PORT DioConf_LED1_PORT_NUM

/* Set the LED Pin Number */
#define LED_PIN_NUM DioConf_LED1_CHANNEL_NUM


/* Description: Set the LED state to ON */
void LED_setOn(void);

/* Description: Set the LED state to OFF */
void LED_setOff(void);

/*Description: Toggle the LED state */
void LED_toggle(void);

/* Description: Refresh the LED state */
void LED_refreshOutput(void);

#endif /* LED_H */
