/*
 * clock_control.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * システムクロック制御の機能を準備するヘッダーファイル。
 * システムクロック制御に無関係な機能は実装しないこと。
 */

#ifndef INC_CLOCK_CONTROL_H_
#define INC_CLOCK_CONTROL_H_

/*
 * ヘッダーファイル参照を行う場所。
 * マイコン標準の機能レジスタが定義されたもの、及びエラー種類が定義されたものをここで呼び出す。
 */
#include "error_def.h"
#include "stm32g0xx.h"
/* ヘッダーファイル参照完了 */


/*
 * クロック制御用の構造体等を宣言する場所。
 * 型を定義して記述すること。
 */
typedef enum
{
	PLLSRC_NONE = 0x00,
	PLLSRC_HSI = 0x02,
	PLLSRC_HSE = 0x03
}PLLSource_t;				//　PLLのクロックソース設定用に定数列を宣言する。


typedef struct
{
	uint8_t PLL_SRC;
	uint32_t PLL_EN;
	uint8_t PLLN;
	uint8_t PLLM;
	uint8_t PLLR;
	uint8_t PLLQ;
	uint8_t PLLP;
}PLL_Config_t;			//　PLL使用時の設定用に構造体を宣言する。

typedef struct
{
	uint32_t OSC_TYP;
	uint8_t HSI_DIV;
	uint8_t HSI_CAL;
	PLL_Config_t PLL;
}OSC_Config_t;			//　各種発振器の初期化及び起動用に構造体を宣言する。

typedef struct
{
	uint8_t MCO_PSC;
	uint8_t MCO_SEL;
	uint8_t APB_PSC;
	uint8_t AHB_PSC;
	uint8_t SysCLK_SRC;
}Clock_Config_t;		//　各種クロック供給の初期化及び開始用に構造体を宣言する。
/* クロック制御構造体等宣言完了 */


/*
 * クロック制御変数を持ち出せる様に定義する場所。
 */
extern __IO uint32_t sys_tick_counter;
/* クロック制御変数持ち出し可能化完了 */


/*
 * クロック制御関数を宣言する場所。
 */
ErrorStatus_t System_Config(const uint32_t tick_prio);		//　システムタイマーの初期化及び設定を行う。
void Tick_Count(void);			//　システムタイマーのカウンターをインクリメントする。
void Program_Delay(const uint32_t delay_time);		//　システムタイマーを使って待機時間を作る。
ErrorStatus_t OSC_Conf(const OSC_Config_t* osc_parameter);		//　発振器の初期化及び起動を行う。
ErrorStatus_t CLK_Conf(const Clock_Config_t* clk_parameter, const uint8_t f_latency);		//　クロック供給の初期化及び開始を行う。
/* クロック制御関数宣言完了 */


#endif /* INC_CLOCK_CONTROL_H_ */
