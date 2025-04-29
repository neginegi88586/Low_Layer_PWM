/*
 * clock_control.c
 *
 *  作成日: 2025/03/02
 *		作成者: ネギもやし
 *
 * システムクロック制御の機能を準備・提供するソースファイル。
 * システムクロック制御に無関係な機能は実装しないこと。
 */

/*
 * ヘッダーファイル参照を行う場所。
 */
#include "clock_control.h"
/* ヘッダーファイル参照完了 */


/*
 * クロック制御関連の定数を宣言する場所。
 */
const uint32_t HSI_TIMEOUT_VALUE					= (2U);
const uint32_t PLL_TIMEOUT_VALUE					= (2U);

const uint32_t CLK_SWS_TIMEOUT_VALUE		= (5000U);
/* クロック制御定数宣言完了 */

/*
 * クロック制御関連の変数を宣言する場所。
 * システムタイマー制御変数もここで宣言する。
 */
extern uint32_t SystemCoreClock;

__IO uint32_t sys_tick_counter = 0;
uint32_t sys_tick_priority = (1UL << __NVIC_PRIO_BITS);
/* クロック制御変数宣言完了 */


/*
 * クロック制御関数の本体を定義する場所。
 */
ErrorStatus_t System_Config(const uint32_t tick_prio)
{
	uint32_t tick = ((uint32_t)(SystemCoreClock / 1000));
	if(SysTick_Config(tick) != Ret_OK)
	{
		return Ret_Error;
	}
	else
	{
		if(tick_prio < (1UL << __NVIC_PRIO_BITS))
		{
			NVIC_SetPriority(SysTick_IRQn, tick_prio);
			sys_tick_priority = tick_prio;
		}
		else
		{
			return Ret_Error;
		}
	}

	return Ret_OK;
}

void Tick_Count(void)
{
	sys_tick_counter += 1;
}

void Program_Delay(const uint32_t delay_time)
{
	uint32_t start_tick;
	if((sys_tick_counter + delay_time) > 4294967290)
	{
		sys_tick_counter = 0;
	}

	start_tick = sys_tick_counter;
	while((sys_tick_counter - start_tick) < delay_time);
}

ErrorStatus_t OSC_Conf(const OSC_Config_t* osc_parameter)
{
	uint32_t start_tick;
	uint32_t tmp_sysclk_src;
	uint32_t tmp_pllclk_cfg;

	if(((osc_parameter->OSC_TYP) & RCC_CR_HSION) == RCC_CR_HSION)
	{
		tmp_sysclk_src = ((RCC->CFGR) & RCC_CFGR_SWS);
		tmp_pllclk_cfg = ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC));

		if(((tmp_sysclk_src == RCC_CFGR_SWS_1) && (tmp_pllclk_cfg == RCC_PLLCFGR_PLLSRC_HSI)) || tmp_sysclk_src == 0x00U)
		{
			if(((RCC->CR) & RCC_CR_HSIRDY) != 0 && ((osc_parameter->OSC_TYP) & RCC_CR_HSION) == 0x00)
			{
				return Ret_Error;
			}
			else
			{

			}
		}
	}

	if((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLLRCLK)
	{
		if(((osc_parameter->OSC_TYP) & RCC_CR_PLLON) == RCC_CR_PLLON)
		{
			RCC->CR &= (~(RCC_CR_PLLON));

			start_tick = sys_tick_counter;
			while(((RCC->CR) & RCC_CR_PLLRDY) == RCC_CR_PLLRDY)
			{
				if((sys_tick_counter - start_tick) > PLL_TIMEOUT_VALUE)
				{
					return Ret_Timeout;
				}
			}

			RCC->PLLCFGR = (((osc_parameter->PLL.PLLR) << RCC_PLLCFGR_PLLR_Pos)| ((osc_parameter->PLL.PLL_EN) & RCC_PLLCFGR_PLLREN_Msk) |
					((osc_parameter->PLL.PLLQ) << RCC_PLLCFGR_PLLQ_Pos) | ((osc_parameter->PLL.PLL_EN) & RCC_PLLCFGR_PLLQEN_Msk) |
					((osc_parameter->PLL.PLLP) << RCC_PLLCFGR_PLLP_Pos) | ((osc_parameter->PLL.PLL_EN) & RCC_PLLCFGR_PLLPEN_Msk) |
					((osc_parameter->PLL.PLLN) << RCC_PLLCFGR_PLLN_Pos) | ((osc_parameter->PLL.PLLM) << RCC_PLLCFGR_PLLM_Pos) | ((osc_parameter->PLL.PLL_SRC)));

			RCC->CR |= RCC_CR_PLLON;

			start_tick = sys_tick_counter;
			while(((RCC->CR) & RCC_CR_PLLRDY) != RCC_CR_PLLRDY)
			{
				if((sys_tick_counter - start_tick) > PLL_TIMEOUT_VALUE)
				{
					return Ret_Timeout;
				}
			}
		}
	}

	return Ret_OK;
}

ErrorStatus_t CLK_Conf(const Clock_Config_t* clk_parameter, const uint8_t f_latency)
{
	uint32_t start_tick;

	if(f_latency > ((FLASH->ACR) & FLASH_ACR_LATENCY))
	{
		FLASH->ACR |= (f_latency & FLASH_ACR_LATENCY);

		start_tick = sys_tick_counter;
		while(((FLASH->ACR) & FLASH_ACR_LATENCY) != f_latency)
		{
			if((sys_tick_counter - start_tick) > CLK_SWS_TIMEOUT_VALUE)
			{
				return Ret_Timeout;
			}
		}
	}

	if(((clk_parameter->SysCLK_SRC) & RCC_CFGR_SW_Msk) == RCC_CFGR_SW_1)
	{
		MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, (RCC_CFGR_PPRE_0 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_2));
		MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, clk_parameter->AHB_PSC << 8);

		if(((RCC->CR) & RCC_CR_PLLRDY_Msk) == 0)
		{
			return Ret_Error;
		}

		MODIFY_REG(RCC->CFGR, RCC_CFGR_SW_Msk, (clk_parameter->SysCLK_SRC) << RCC_CFGR_SW_Pos);

		start_tick = sys_tick_counter;

		while(((RCC->CFGR) & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLLRCLK)
		{
			if((sys_tick_counter - start_tick) > CLK_SWS_TIMEOUT_VALUE)
			{
				return Ret_Timeout;
			}
		}
	}

	SystemCoreClockUpdate();


	return System_Config(sys_tick_priority);
}
/* クロック制御関数定義完了 */
