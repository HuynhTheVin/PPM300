/*
 * PPM.c
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */

#define EXTERN
#include "r_smc_entry.h"
#include "PPM.H"
#include "p_prototype.h"
/**
 * @brief Set the kchange eng object
 *
 */
void set_kchange_eng(void){
    for (BYTE i = 0; i < EUART_MAX; i++)
    {
        KEY_MODE.kchange[i].bitms.eng = 1;
    }
}
/**
 * @brief Set the kchange dirt object
 * 
 */
void set_kchange_dirt(void){
    for (BYTE i = 0; i < EUART_MAX; i++)
    {
        KEY_MODE.kchange[i].bitms.dirt = 1;
    }
}