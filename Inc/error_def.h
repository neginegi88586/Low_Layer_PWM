/*
 * error_def.h
 *
 *  Created on: Mar 2, 2025
 *      Author: idune
 */

#ifndef INC_ERROR_DEF_H_
#define INC_ERROR_DEF_H_


typedef enum
{
	Ret_OK = 0,
	Ret_Error,
	Ret_Fail,
	Ret_Busy,
	Ret_Timeout
}ErrorStatus_t;		//エラーハンドリング用の定数と型を一括で宣言する。


#endif /* INC_ERROR_DEF_H_ */
