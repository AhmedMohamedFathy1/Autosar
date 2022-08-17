 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Gpt Driver Registers
 *
 * Author: Ahmed Mohamed Fathy
 ******************************************************************************/

#ifndef GPT_REGS_H
#define GPT_REGS_H

#include "Std_Types.h"

#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/* NVIC  register */
#define NVIC_SYSTEM_PRI3_REG      (*((volatile uint32 *)0xE000ED20))

#endif /* GPT_REGS_H */