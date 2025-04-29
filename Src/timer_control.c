/*
 * timer_control.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * タイマー制御の機能を準備するソースファイル。
 * タイマー制御に無関係な機能は実装しないこと。
 */

/*
 * ヘッダーファイル参照を行う場所。
 */
#include "timer_control.h"
/* ヘッダーファイル参照完了 */


/*
 * タイマー制御関連の定数を宣言する場所。
 */

/* タイマー制御定数宣言完了 */


/*
 * タイマー制御関連の変数を宣言する場所。
 */

/* タイマー制御変数宣言完了 */


/*
 * タイマー制御関数の本体を定義する場所。
 */
ErrorStatus_t Timer_Conf(Timer_Handle_t *timer_parameter)
{
	TIM_TypeDef *TIMx = timer_parameter->Inst;

	  do{
	    if (((TIMx)->CCER & ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E))) == 0UL)
	    {
	      if(((TIMx)->CCER & ((uint32_t)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE))) == 0UL)
	      {
	        (TIMx)->CR1 &= ~(TIM_CR1_CEN);
	      }
	    }
	  }while(0);

	TIMx->CR1 = (uint32_t)(timer_parameter->TIM_CR1);
	TIMx->ARR = (uint32_t)(timer_parameter->TIM_ARR);
	TIMx->PSC = (uint32_t)(timer_parameter->TIM_PSC);
	TIMx->CR2 = (uint32_t)(timer_parameter->TIM_CR2);

	TIMx->EGR = TIM_EGR_UG;

	if(((TIMx->SR) & TIM_SR_UIF_Msk) == TIM_SR_UIF)
	{
		TIMx->SR &= (~(TIM_SR_UIF));
	}

	return Ret_OK;
}

ErrorStatus_t Timer_Start_IT(Timer_Handle_t *timer_handle)
{
	TIM_TypeDef *TIMx = timer_handle->Inst;

	if((timer_handle->DMA_IT_MODE) != 0x0000)
	{
		NVIC_SetPriority((timer_handle->TIM_IRQn), 0);
		if(NVIC_GetPriority(timer_handle->TIM_IRQn) != 0)
		{
			return Ret_Fail;
		}

		NVIC_EnableIRQ((timer_handle->TIM_IRQn));
	}

	TIMx->DIER = (timer_handle->DMA_IT_MODE);

	TIMx->CR1 |= TIM_CR1_CEN;

	return Ret_OK;
}

void Timer_IT_Handler(Timer_Handle_t *timer_handle)
{
	TIM_TypeDef *TIMx = timer_handle->Inst;

	if(((TIMx->SR) & TIM_SR_UIF_Msk) == TIM_SR_UIF)
	{
		Timer_Period_Callback(timer_handle);
		TIMx->SR &= (~(TIM_SR_UIF));
	}
}
/* タイマー制御関数定義完了 */
