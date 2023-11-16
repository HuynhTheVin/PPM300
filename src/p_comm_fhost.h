/*
 * p_comm_fhost.h
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#ifndef P_COMM_FHOST_H_
#define P_COMM_FHOST_H_
//#include "p_mainh.h"
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void host_read_direct_data(void);
void host_read_direct_time_data(void);
void host_read_monitor_data(void);
void host_read_joso_data(void);
void host_read_command_data(void);
void host_read_engineering_data(void);
void host_read_maintenace_data(void);
void host_read_maintenaceR_data(void);
void host_read_maintenaceW_data(void);
void read_cmd_host(void);

void host_write_direct_data(void);
void host_write_direct_time_data(void);
void host_write_monitor_data(void);
void host_write_joso_data(void);
void host_write_command_data(void);
void host_write_engineering_data(void);
void host_write_maintenace_data(void);
void host_write_maintenaceR_data(void);
void host_write_maintenaceW_data(void);
void write_cmd_host(void);
BOOL host_write_status_check(uint16_t set_erea);

enum HOST_ADDR_AREA{
    EHOST_ADDR_DIRECT,
    EHOST_ADDR_DIRECT_TIME,
    EHOST_ADDR_JOSO,
    EHOST_ADDR_ENGINEERING,
    EHOST_ADDR_MONITOR,
    EHOST_ADDR_COMMAND,
    EHOST_ADDR_MAINTENANCE,
    EHOST_ADDR_MAINTENANCE_WRITE,
    EHOST_ADDR_MAINTENANCE_READ,
    EHOST_ADDR_PRS
};
enum FACTORY_MODE {
    MD_STANDBY,     /* 0 PVSV */
    MD_FACT     /* 1 factory */
};


#endif /* P_COMM_FHOST_H_ */
