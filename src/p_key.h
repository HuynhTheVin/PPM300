/*
 * p_key.h
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */

#ifndef P_KEY_H_
#define P_KEY_H_

#include "p_mainh.h"


#define DIGNUM 10  /* 10ms外部入力取り込む */

#define K_RES_OK           0x00   /* (有効キー) */
#define K_RES_NG_COMMON    0x0F   /* (無効キー) */
#define K_RES_NG_DOR       0x01   /* (無効キー) ドア中 */
#define K_RES_NG_KEY       0x04   /* (無効キー) 設定モード中 */
#define K_RES_NG_AT        0x05   /* (無効キー) 設定できない状態 */
#define K_RES_NG_PIP       0x15   /* (無効キー) 無効キー要求 */

void exitchk(void);
void command(void);
void extcommandsub(void);
BYTE ie_KEYSTART(void);
void ie_KEYSTOP(void);
uint8_t start_unten(void);
uint8_t start_reitou_unten(void);
uint8_t start_reitouzou_unten(void);
void stop_sub(void);
#endif /* P_KEY_H_ */
