/*
 * p_comm_fhost_eng.c
 *
 *  Created on: 2023/06/27
 *      Author: VINH-NT
 */
/* 対HOST-ENGINEERINGエリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"

void disp_eng_make_phase(uint16_t base_addr){
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = uartp->id - PH_DATA0;  /* 通信項目のフェースは同じ順 */
    if(uartp->phase>=PH_DATAMAX){
        uartp->phase = PH_DUMMY;
    }
}
/**
 * @brief Processing the response to a read command
 *
 */
void host_read_engineering_data(void)
{
    disp_eng_make_phase(uartp->base_addr);

    if (uartp->phase >= PH_DATAMAX)
    {
        rdnone();
        return;
    }

    if (is_yoyaku(uartp->phase))
    {
        rdyaku();
        return;
    }
    else
    {
        comret_dt(get_para(uartp->phase));
        //     switch (uartp->phase){
        // case PH_P53:  /*  通信機器番号  */
        // case PH_P54:  /*  通信速度  */
        //     rdyaku();
        //     return;
        // default:
        //     comret_dt(get_para(uartp->phase));
        // }
    }
}

void write_engineering_sub(void){
    int16_t data;
    int16_t odt;

    data = cmkdat();
    odt = get_para(uartp->phase);
    if(limit_check(get_min(uartp->phase), get_max(uartp->phase), data)){
        if(data!=odt){
            set_para(uartp->phase,data);
            //wr_data_change_para(uartp->phase,data,odt); check 上下限値設定 
        }
        wryaku();
    }else{
        wrnak3();
    }
}
/**
 * @brief Processing the response to a write command
 * 
 */
void host_write_engineering_data(void){
    disp_eng_make_phase(uartp->base_addr);

    if(uartp->phase >= PH_DATAMAX){
        wrnone(); return;
    }

    if(host_write_status_check(uartp->erea)){
        if(is_yoyaku(uartp->phase)){
            wryaku(); return;
        }else{
             write_engineering_sub();
            // switch (uartp->phase){
            // case PH_P53:  /*  通信機器番号  */
            // case PH_P54:  /*  通信速度  */
            //     wryaku(); return;
            // default:
            //     write_engineering_sub();
            // }
        }
    }
}