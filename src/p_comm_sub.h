/*
 * p_comm_sub.h
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */

#ifndef P_COMM_SUB_H_
#define P_COMM_SUB_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"
//#include "PPM.h"
extern const uint8_t txwietbl[];
extern const uint8_t mrtuwitbl[];

void clr_tx(void);
void clr_rx(void);
void txbegin(void);
uint16_t cmkdat(void);
void comret_dt(int16_t i);
void readcmd(uint16_t ad);
void readcmdblk(void);
void wrsetcmdblk(void);
void wrsetcmd(uint16_t ad);
void uartm_comm(void);

#define STX         0x02
#define ETX         0x03
#define ENQ         0x05
#define ACK         0x06
#define NAK         0x15
#define PLC_LF      0x0A
#define PLC_CR      0x0D
#define ADRESTOP    4
#define DATATOP     8
#define DEVISNO     0x20

enum eprotocol{
    EPRO_SHINKO,
    EPRO_ASCII,
    EPRO_RTU
};

enum espeed{
    ESP_9600,
    ESP_19200,
    ESP_38400,
    ESP_57600
};

enum euartn{
    EUART0_HOST,
    EUART1_DIS,
    EUART5_BLE,
	EUART12_CONS,
    EUART_MAX
};

enum xec {
    NOER,NOTCOMM,FSTEP,SOVER,ATSTAT,SETSTAT,SUMERROR,NONEACK
};
enum rxst {
    RXCLR,RXHEAD,RXDELIMIT,RXSTANDBY
};
#define BLKSIZE_WR          123  /* ブロックライトの上限データ数(対表示器) */
#define BLKSIZE_RD          125  /* ブロックリードの上限データ数(対表示器) */
#define BLKSIZE_HOST_WR      20  /* ブロックライトの上限データ数(対ホスト) */
#define BLKSIZE_HOST_RD     100  /* ブロックリードの上限データ数(対ホスト) */
#define BFCAP_RX_MAX 550
#define BFCAP_TX_MAX 550
#define MIn_min          0  /* ブロックライトの上限データ数(対表示器) */

#define BLKSIZE_RD          125  /* ブロックリードの上限データ数(対表示器) */
/* UART */
struct UART_WORK{
    uint8_t  uartnumber;
    uint8_t  flg_xerr;
    uint8_t  flg_bxerr;          /* ブロック通信での最初のエラーコードバックアップ */
    uint16_t commblock;          /* 対象データグループ */
    uint16_t commitem;           /* 対象データ項目 */
    uint16_t commadr;            /* 対象データ項目 */
    uint16_t datatop;            /* データトップindex */
    uint8_t  itempo;             /* ブロック通信の処理Chカウンタ */
    uint8_t  datasuu;            /* データ数 */
    uint8_t  flg_rx;
    uint16_t  rxpo;              /* Rx Poiner */
    uint16_t  txpo;              /* Tx Poiner */
    uint16_t  rxcn;              /* Tx データのRxCounter */
    int16_t  txwis;              /* Tx Start wait timer */
//  int16_t  txwie;              /* Tx End wait timer */
    uint8_t  rxbff[BFCAP_RX_MAX];/* Rx Buffer */
    uint8_t  txbff[BFCAP_TX_MAX];/* Tx Buffer */
    uint16_t  flg_txlen;         /* Tx Send データ変換時のポインタ */
    uint16_t  flg_rxlen;         /* Rx Send データ変換時のポインタ */
    uint8_t  moddev;             /* 受信機器番号 */
    uint16_t modadr;             /* データ項目アドレス */
    uint8_t moditem;             /* 機能コード */
    uint8_t modlast;             /* RTUモードの最終コード */
    uint8_t modnum;              /* 複数データ数 */
    uint8_t modtim2;             /* 3.5文字のウェイトタイマ */
    int16_t modbdt;              /* 読取りの応答データ */
    int16_t modtim;              /* １秒のタイムアウトタイマ */
    union U_COM_CHANGE
    {
        uint16_t data;
        struct
        {
            uint16_t value_change:1;     /* B0 設定値変更の有無フラグ */
        }bitms;
    }Dmy_change;

    /* プログラム用中間値 */
    uint16_t erea;
    uint16_t base_addr;
    uint16_t menu;
    uint16_t memory;
    uint16_t step;
    uint16_t id;
    uint16_t phase;

    /* 通信設定値 */
    uint16_t set_device;
    uint16_t set_speed;
    uint16_t set_databit;
    uint16_t set_protocol;

    union UFLG
    {
        uint16_t data;
        struct
        {
            uint16_t protocol:3;     // プロトコル選択。パスワードで切替対応後
            uint16_t sending:1;      // 自器応答中フラグ  0:未     1:送信中
            uint16_t enable_internal_cmd:1;  // 内部コマンド有効  0:無効     1:有効
            uint16_t change_dev:1;  // 機器番号変更要求  0:無効     1:有効
            uint16_t change_para:1; // パラメーター変更要求  0:無効     1:有効


        }bitms;
    }cflg;
};

#endif /* P_COMM_SUB_H_ */
