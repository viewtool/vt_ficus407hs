/**
  ******************************************************************************
  * @file    stm32fxxx_it.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides all exceptions handler and peripherals interrupt
  *          service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32fxxx_it.h"
#include <string.h>
extern void I2C1_EV_IRQ_Handler(void);
extern void I2C2_EV_IRQ_Handler(void);
extern void TIM6_DAC_IRQ_Handler(void);
extern void DMA2_Stream0_IRQ_Handler(void);
extern void TIM2_IRQ_Handler(void);
extern void TIM3_IRQ_Handler(void);
extern void CAN1_RX0_IRQ_Handler(void);
extern void CAN1_RX1_IRQ_Handler(void);
extern void CAN2_RX0_IRQ_Handler(void);
extern void CAN2_RX1_IRQ_Handler(void);
extern void TIM4_IRQ_Handler(void);
extern void TIM5_IRQ_Handler(void);
extern void DMA2_Stream3_IRQ_Handler(void);
extern void DMA2_Stream4_IRQ_Handler(void);
extern void USART1_IRQ_Handler(void);
extern void USART2_IRQ_Handler(void);
extern void USART3_IRQ_Handler(void);
extern void OTG_HS_IRQ_Handler(void);
extern void OTG_FS_IRQ_Handler(void);
extern void OTG_HS_EP1_IN_IRQ_Handler(void);
extern void OTG_HS_EP1_OUT_IRQ_Handler(void);
extern void OS_SVC_Handler(void);
extern void OS_PendSV_Handler(void);
extern void OS_SysTick_Handler(void);

/******************************************************************************/
/*             Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
    OS_SVC_Handler();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
    
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
     OS_PendSV_Handler();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
   OS_SysTick_Handler();
}

void I2C1_EV_IRQHandler(void)
{
	I2C1_EV_IRQ_Handler();
}
void I2C2_EV_IRQHandler(void)
{
	I2C2_EV_IRQ_Handler();
}
void TIM6_DAC_IRQHandler(void)
{
	TIM6_DAC_IRQ_Handler();
}
void DMA2_Stream0_IRQHandler(void)
{
	DMA2_Stream0_IRQ_Handler();
}
void TIM2_IRQHandler(void)
{
	TIM2_IRQ_Handler();
}
void TIM3_IRQHandler(void)
{
	TIM3_IRQ_Handler();
}
void CAN1_RX0_IRQHandler(void)
{
	CAN1_RX0_IRQ_Handler();
}
void CAN1_RX1_IRQHandler(void)
{
	CAN1_RX1_IRQ_Handler();
}
void CAN2_RX0_IRQHandler(void)
{
	CAN2_RX0_IRQ_Handler();
}
void CAN2_RX1_IRQHandler(void)
{
	CAN2_RX1_IRQ_Handler();
}
void TIM4_IRQHandler(void)
{
	TIM4_IRQ_Handler();
}
void TIM5_IRQHandler(void)
{
	TIM5_IRQ_Handler();
}
void DMA2_Stream3_IRQHandler(void)
{
	DMA2_Stream3_IRQ_Handler();
}
void DMA2_Stream4_IRQHandler(void)
{
	DMA2_Stream4_IRQ_Handler();
}
void USART1_IRQHandler(void)
{
	USART1_IRQ_Handler();
}
void USART2_IRQHandler(void)
{
	USART2_IRQ_Handler();
}
void USART3_IRQHandler(void)
{
	USART3_IRQ_Handler();
}
void OTG_HS_IRQHandler(void)
{
	OTG_HS_IRQ_Handler();
}
void OTG_FS_IRQHandler(void)
{
	OTG_FS_IRQ_Handler();
}
void OTG_HS_EP1_IN_IRQHandler(void)
{
	OTG_HS_EP1_IN_IRQ_Handler();
}
void OTG_HS_EP1_OUT_IRQHandler(void)
{
	OTG_HS_EP1_OUT_IRQ_Handler();
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
