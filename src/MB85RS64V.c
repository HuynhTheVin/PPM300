/*
 * MB85RS64V.c
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */
#define EXTERN extern

#include "PPM.h"
#include "MB85RS64V.h"
#define     OPC_WREN    0x06
#define     OPC_WRDI    0x04
#define     OPC_RDSR    0x05
#define     OPC_WRSR    0x01
#define     OPC_READ    0x03
#define     OPC_WRTE    0x02

void skon(void){IO_FRAM_CLOCK_ON;}
void skoff(void){IO_FRAM_CLOCK_OFF;}
void cson(void){IO_FRAM_CS_ON;}
void csoff(void){IO_FRAM_CS_OFF;}
void sion(void){/* OUT  */
    //IO_FRAM_DATA_TO_OUT;
    IO_FRAM_DATA_OUT_ON;
}
void sioff(void){/* OUT  */
    //IO_FRAM_DATA_TO_OUT;
    IO_FRAM_DATA_OUT_OFF;
}

/******************************************************/
void skset(void)/* CSK  __|~~|__ */
{
    skon();            /* clock high                   */
    skoff();           /* clock low                    */
}
/* enable eeprom */
void chip_e(void)
{
    skoff();           /* clock low                    */
    cson();
    sioff();            /* di low */
}
/* disable eeprom */
void chip_d(void)
{
    csoff();
}
void out8(BYTE data){
    BYTE   i;

    for (i = 0; i < 8; i++, data <<= 1) {
        if (data & 0x80){
            sion();
        }else{
            sioff();
        }
        skset();            /* clock high & low active */
    }
}


BYTE inp8(void){
    BYTE   i, data;

    IO_FRAM_DATA_TO_IN;

    data = 0;
    for (i = 0; i < 8; i++) {
        data <<= 1;
        if (IO_FRAM_DATA_IN_ON){
            data++;
        }
        skset();            /* clock high & low active */
    }

    IO_FRAM_DATA_TO_OUT;

    return (data);
}

WORD epr_read(WORD address, BYTE onceByte){
    WORD data = 0;

    chip_e();
    out8(OPC_READ);     /* send Instruction       */
    out8(address >> 8); /* send address A8`A15   */
    out8(address);      /* send address A0`A7    */
    sioff();

    if(onceByte == 0){
        data = inp8() * 0x100;
    }
    data += inp8();
    chip_d();           /* disable eeprom */
    return (data);
}


void epr_wren(void)      /* Send WREN           */
{
    chip_e();
    out8(OPC_WREN);          /* send Instruction    */
    chip_d();
}
void epr_wrdi(void)      /* Send WRDI           */
{
    chip_e();
    out8(OPC_WRDI);          /* send Instruction    */
    chip_d();
}

void epr_write(WORD adr, WORD data, BYTE onceByte){

    chip_e();
    out8(OPC_WRTE);     /* send Instruction         */
    out8(adr >> 8);     /* send address A7`A15     */
    out8(adr);          /* send address A0`A7      */
    if(onceByte==0){
        out8(data >> 8);/* set write high 8 bits    */
    }
    out8(data);         /* set write low 8 bits     */
    sioff();            /* di low                   */
    chip_d();           /* disable eeprom           */
}

WORD get_fram2(WORD address){
    WORD adr;

    adr = address * 2;  /* address ~2 to 16bit data access */
    return epr_read(adr, 0);

}

void put_fram2(WORD address, WORD data){
    WORD adr;

    if(
        get_fram2(address)==data){return;}/* Do not write if the data is the same */
    epr_wren();         /* Send WREN           */
    adr = address * 2;  /* address ~2 to 16bit data access */
    epr_write(adr, data, 0);
    epr_wrdi();         /* write disable       */
}

WORD get_fram1(WORD address){
    WORD adr;

    adr = address;  /* address  to 8bit data access */
    return epr_read(adr, 1);
}

void put_fram1(WORD address, WORD data){
    WORD adr;

    if(get_fram1(address)==data){return;}/* Do not write if the data is the same */
    epr_wren();         /* Send WREN           */
    adr = address;      /* address 8bit data access */
    epr_write(adr, data, 1);
    epr_wrdi();         /* write disable       */
}

