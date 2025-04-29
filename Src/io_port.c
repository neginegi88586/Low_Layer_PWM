/*
 * gpio.h
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * IOポート制御の機能を準備・提供するソースファイル。
 * IOポート制御に無関係な機能は実装しないこと。
 */



/*
 * ヘッダーファイル参照を行う場所。
 */
#include "io_port.h"
/* ヘッダーファイル参照完了 */


/*
 * IOポート制御関連の定数を宣言する場所。
 */
const uint8_t SHIFT_NUM_2[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};		//MODEレジスタ、OSPEEDレジスタ、PUPDレジスタを設定する際に使う。
const uint8_t SHIFT_NUM_4[] = {0, 4, 8, 12, 16, 20, 24, 28};
/* IOポート制御定数宣言完了 */


/*
 * IOポート制御関数の本体を定義する場所。
 */
void IO_Port_Conf(const IO_Port_Config_t *io_port_parameter)
{
	GPIO_TypeDef *IO_PORTx = io_port_parameter->Inst;

	for(uint8_t i = 0; i < 16; i++)
	{
		if(((io_port_parameter->IO_BIT) & (1 << i)) == (1 << i))
		{
			if(((IO_PORTx->MODER) & (0x3 << SHIFT_NUM_2[i])) != ((io_port_parameter->IO_MODE) & (0x3 << SHIFT_NUM_2[i])))
			{
				IO_PORTx->MODER &= (~(0x3 << SHIFT_NUM_2[i]));
				IO_PORTx->MODER |= ((io_port_parameter->IO_MODE) & (0x3 << SHIFT_NUM_2[i]));
			}
			if(((IO_PORTx->OTYPER) & (1 << i)) != ((io_port_parameter->Out_TYPE) & (1 << i)))
			{
				IO_PORTx->OTYPER &= (~(1 << i));
				IO_PORTx->OTYPER |= ((io_port_parameter->Out_TYPE) & (1 << i));
			}
			if(((IO_PORTx->OSPEEDR) & (0x3 << SHIFT_NUM_2[i])) != ((io_port_parameter->Out_SPEED) & (0x3 << SHIFT_NUM_2[i])))
			{
				IO_PORTx->OSPEEDR &= (~(0x3 << SHIFT_NUM_2[i]));
				IO_PORTx->OSPEEDR |= ((io_port_parameter->Out_SPEED) & (0x3 << SHIFT_NUM_2[i]));
			}

			if(((IO_PORTx->MODER) & (0x3 << SHIFT_NUM_2[i])) == (0x2 << SHIFT_NUM_2[i]))
			{
				// オルタネート機能を使う際に実装する。
			}
		}
	}
}

void IO_Write(GPIO_TypeDef *Port, const uint16_t bit, const IO_State_t bit_Status)
{
	if(bit_Status != IO_RST)
	{
		Port->ODR |= bit;
	}
	else
	{
		Port->ODR &= (~(bit));
	}
}

void IO_Toggle(GPIO_TypeDef *Port, const uint16_t bit)
{
	Port->ODR ^= bit;
}
/* IOポート制御関数定義完了 */
