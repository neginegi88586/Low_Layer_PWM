/*
 * interrupt.c
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * 割り込み発生時の処理を記述するソースファイル。
 * 割り込み処理(コールバック関数は割り込み処理に含まれない)以外を記述しない事。
 */

#include "interrupt.h"
#include "main.h"


 /*
  * 割り込み制御用変数を宣言する場所。
  */
extern Timer_Handle_t tim16_handle;
extern Timer_Handle_t tim17_handle;
/* 割り込み制御用変数宣言完了 */

/*
 * 割り込みハンドラ関数を宣言する場所。
 * 実際に呼び出される関数はエイリアス属性を参照のこと。
 */
void NMI_Handler(void) __attribute__((alias("NonMaskable_Int")));
void HardFault_Handler(void) __attribute__((alias("HardFault")));
void SysTick_Handler(void) __attribute__((alias("SystemTimer_Int")));
void TIM16_IRQHandler(void) __attribute__((alias("TIM16_Int")));
void TIM17_IRQHandler(void) __attribute__((alias("TIM17_Int")));
/* 割り込みハンドラ宣言完了 */


/*
 * 割り込みハンドラ関数の本体を定義する場所。
 * 関数名はプロトタイプ宣言時に割り当てたエイリアス属性を参照すること。
 */
void NonMaskable_Int(void)
{
	while(1);
}

void HardFault(void)
{
	while(1);
}

void SystemTimer_Int(void)
{
	Tick_Count();
}

void TIM16_Int(void)
{
	Timer_IT_Handler(&tim16_handle);
}

void TIM17_Int(void)
{
	Timer_IT_Handler(&tim17_handle);
}
