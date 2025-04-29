/*
 * gpio.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * IOポート制御の機能を準備するヘッダーファイル。
 * IOポート制御に無関係な機能は実装しないこと。
 */

#ifndef INC_IO_PORT_H_
#define INC_IO_PORT_H_

/*
 * ヘッダーファイル参照を行う場所。
 */
#include "error_def.h"
#include "stm32g0xx.h"
/* ヘッダーファイル参照完了 */


/*
 * IOポート制御用の構造体等を宣言する場所。
 * 型を定義して記述すること。
 */
typedef enum
{
	IO_RST = 0,
	IO_SET
}IO_State_t;		// GPIOの入出力状態を定義する定数列を定義。

typedef struct
{
	GPIO_TypeDef *Inst;		//　GPIOのポートアドレスを格納する。
	uint16_t IO_BIT;		// 使用するピンを1ピン単位で格納する。
	uint32_t IO_MODE;		// 各ピンの機能カテゴリ(出力、入力、オルタネート機能、アナログ)を1ピン単位で格納する(2ビット書式)。
	uint32_t Out_TYPE;		// 出力モードに設定されたピンの出力方式を格納する(1ビット書式)。
	uint32_t Out_SPEED;		// 出力モードに設定されたピンの動作スピードを格納する(2ビット書式)。
	uint32_t PU_PD;			// 入力ピンのプルアップまたはプルダウンを設定し格納する(2ビット書式)。
	uint32_t AF_LOW;		// 0～7ビットのピンでオルタネート機能を使う場合に、機能番号を格納する(4ビット書式)。
	uint32_t AF_HI;			// 8～15ビットのピンでオルタネート機能を使う場合に、機能番号を格納する(4ビット書式)。
}IO_Port_Config_t;
/* IOポート制御構造体等宣言完了 */


/*
 *　IOポート制御関数を宣言する場所。
 */
void IO_Port_Conf(const IO_Port_Config_t *io_port_parameter);		// GPIOの初期化関数。
void IO_Write(GPIO_TypeDef *Port, const uint16_t bit, const IO_State_t bit_Status);		// 出力モードのGPIOピンに任意の出力を設定する関数。
void IO_Toggle(GPIO_TypeDef *Port, const uint16_t bit);		// 出力モードのGPIOピンを反転させる関数。
/* IOポート制御関数宣言完了 */

#endif /* INC_IO_PORT_H_ */
