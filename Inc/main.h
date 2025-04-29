/*
 * main.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 *  <重要>:	このファイルを必ず「main.c」で参照すること。
 */

#ifndef MAIN_H_
#define MAIN_H_


/* ヘッダーファイル参照を宣言する場所。
 * マイコン標準の機能を制御するヘッダーファイルをここで呼び出す。
 * 上記以外を制御するヘッダーは「main.c」で呼び出すこと。
 */
#include "clock_control.h"
#include "timer_control.h"
#include "io_port.h"
/* ヘッダーファイル参照宣言完了 */


/*
 * エラー処理関数を宣言する場所。
 */
void Program_Error(void);
/* エラー処理関数宣言完了 */


#endif /* MAIN_H_ */
