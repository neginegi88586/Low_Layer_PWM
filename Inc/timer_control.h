/*
 * timer_control.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * タイマー制御の機能を準備するヘッダーファイル。
 * タイマー制御に無関係な機能は実装しないこと。
 */

#ifndef INC_TIMER_CONTROL_H_
#define INC_TIMER_CONTROL_H_

/*
 * ヘッダーファイル参照を行う場所。
 */
#include "error_def.h"
#include "stm32g0xx.h"
/* ヘッダーファイル参照完了 */


/*
 * タイマー制御用の構造体等を宣言する場所。
 * 型を定義して記述すること。
 */
typedef struct
{
	TIM_TypeDef *Inst;
	IRQn_Type TIM_IRQn;
	uint32_t TIM_PSC;
	uint32_t TIM_ARR;
	uint32_t TIM_CR1;
	uint32_t TIM_CR2;
	uint32_t DMA_IT_MODE;
}Timer_Handle_t;		// タイマーの初期化用に構造体を宣言する。
/* タイマー制御構造体宣言完了 */


/*
 * タイマー制御関数を宣言する場所。
 * 割り込みコールバック関数もここで宣言する。
 */
ErrorStatus_t Timer_Conf(Timer_Handle_t *timer_parameter);
ErrorStatus_t Timer_Start_IT(Timer_Handle_t *timer_handle);
void Timer_IT_Handler(Timer_Handle_t *timer_handle);
void Timer_Period_Callback(Timer_Handle_t *timer_handle);
/* タイマー制御関数宣言完了 */


#endif /* INC_TIMER_CONTROL_H_ */
