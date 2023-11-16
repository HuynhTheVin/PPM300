/*
 * p_comm_fhost.c
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */
/* 対ホスト */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"

const uint16_t HOST_BASE_ADDR[][2] = {
    /* Addr   count   @see HOST_ADDR_AREA for more index information */
    {0x0000, 80},  /* 0000H to 004FH DIRECT */
    {0x0080, 39},  /* 0080H to 00A6H DIRECT 時刻*/
    {0x0100, 11},  /* 0100H to 010AH 除霜方式 */
    {0x1000, 218}, /* 1000H to 10D8H ENGINEERING (A0217まで) */
    {0x2000, 109}, /* 2000H to 206CH MONITOR */
    {0x2100, 136}, /* 2100H to 2187H COMMAND */
    {0x3000, 32},  /* 3000H to 301FH MAINTENANCE*/
    {0x30A0, 32},  /* 30A0H to 30BFH MAINTENANCE Write*/
    {0x30C0, 65},  /* 30C0H to 3100H MAINTENANCE Read */
    {0xFFFF, 1}    /* FFFFH PRS */
};
void host_select_erea(void)
{
    int16_t i;
    uint16_t star_adr;
    uint16_t offset;

    for (i = EHOST_ADDR_PRS; i >= 0; i--)
    {
        star_adr = HOST_BASE_ADDR[i][0];

        if (uartp->commadr >= star_adr)
        {
            offset = uartp->commadr - star_adr;
            if (offset < HOST_BASE_ADDR[i][1])
            {
                uartp->erea = i;
                uartp->base_addr = offset;
            }
            else
            {
                /* 領域以外のであれば、OTHERとする */
                uartp->erea = EHOST_ADDR_PRS;
                uartp->base_addr = 0;
            }
            return;
        }
    }
    uartp->erea = EHOST_ADDR_PRS;
    uartp->base_addr = 0;
}
void read_cmd_host(void)
{
    host_select_erea();
    switch (uartp->erea)
    {
    case EHOST_ADDR_DIRECT:
        host_read_direct_data();
        break;
    case EHOST_ADDR_DIRECT_TIME:
        host_read_direct_time_data();
        break;
    case EHOST_ADDR_JOSO:
        host_read_joso_data();
        break;
    case EHOST_ADDR_ENGINEERING:
        host_read_engineering_data();
        break;
    case EHOST_ADDR_MONITOR:
        host_read_monitor_data();
        break;
    case EHOST_ADDR_COMMAND:
        host_read_command_data();
        break;
    case EHOST_ADDR_MAINTENANCE:
        host_read_maintenace_data();
        break;
    case EHOST_ADDR_MAINTENANCE_WRITE:
        host_read_maintenaceW_data();
        break;
    case EHOST_ADDR_MAINTENANCE_READ:
        host_read_maintenaceR_data();
        break;
    case EHOST_ADDR_PRS:
        rd_prs();
    default:
        rdnone();
    }
}

void write_cmd_host(void)
{
    host_select_erea();
    switch (uartp->erea)
    {
    case EHOST_ADDR_DIRECT:
        host_write_direct_data();
        // if (uartp->flg_xerr == NONEACK)
        // {
        //     /* ACK時のみ通知(設定モード中に更新すると表示器の表示が異常) */
        //     KEY_MODE.kchange[EUART0_DIS].bitms.dirt = 1;
        //     KEY_MODE.kchange[EUART1_FACT].bitms.dirt = 1;
        // }
        break;
    case EHOST_ADDR_DIRECT_TIME:
        host_write_direct_time_data();
        break;
    case EHOST_ADDR_JOSO:
        host_write_joso_data();
        break;
    case EHOST_ADDR_ENGINEERING:
        host_write_engineering_data();
        // if (uartp->flg_xerr == NONEACK)
        // {
        //     /* ACK時のみ通知(設定モード中に更新すると表示器の表示が異常) */
        //     KEY_MODE.kchange[EUART0_DIS].bitms.eng = 1;
        //     KEY_MODE.kchange[EUART1_FACT].bitms.eng = 1;
        // }
        break;
    case EHOST_ADDR_MONITOR:
        host_write_monitor_data();
        break;
    case EHOST_ADDR_COMMAND:
        host_write_command_data();
        break;
    case EHOST_ADDR_MAINTENANCE:
        host_write_maintenace_data();
        break;
    case EHOST_ADDR_MAINTENANCE_WRITE:
        host_write_maintenaceW_data();
        break;
    case EHOST_ADDR_MAINTENANCE_READ:
        host_write_maintenaceR_data();
        break;
    case EHOST_ADDR_PRS:
        wr_prs();
    default:
        wrnone();
    }
}

BOOL host_write_status_check(uint16_t set_erea)
{
    /* モードにより設定をチェック */
    switch (KEY_MODE.flg_mode)
    {
    case STANDBYMD:
        break;    /* 送信許可 */
    case UNTENMD: /* 運転モード */
        wrnak4(); /* 設定できない状態 */
        return false;
    default:
        return false;
    }

    switch (set_erea)
    {
    case EHOST_ADDR_DIRECT:
    case EHOST_ADDR_JOSO:
        /* ダイレクトとコマンドは運転中許可・その他運転中無効 */
        /* 許可 */
        break;
    default:
        /* 運転状態により設定をチェック */
        //        if(is_ck_or_pre()){    /*  運転中 */
        //            wrnak4(); /* 設定できない状態 */
        //            return false;
        //        }
        //        if(is_stop_status()){  /* STOP表示中 */
        //            wrnak4(); /* 設定できない状態 */
        //            return false;
        //        }
        break;
    }
    return true;
}
