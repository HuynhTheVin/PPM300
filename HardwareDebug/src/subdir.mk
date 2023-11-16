################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/ADS1148.c \
../src/Datatbl.c \
../src/MB85RS64V.c \
../src/PPM.c \
../src/PPM300.c \
../src/RX4571LC.c \
../src/advalue.c \
../src/p_comm0.c \
../src/p_comm1.c \
../src/p_comm12.c \
../src/p_comm_fhost.c \
../src/p_comm_fhost_cmd.c \
../src/p_comm_fhost_dir.c \
../src/p_comm_fhost_eng.c \
../src/p_comm_fhost_joso.c \
../src/p_comm_fhost_mai.c \
../src/p_comm_fhost_maiR.c \
../src/p_comm_fhost_maiW.c \
../src/p_comm_fhost_mon.c \
../src/p_comm_func.c \
../src/p_comm_rtu.c \
../src/p_comm_shinko.c \
../src/p_comm_sub.c \
../src/p_cont.c \
../src/p_cont_fan.c \
../src/p_cont_holiday.c \
../src/p_cont_reikyaku.c \
../src/p_factory.c \
../src/p_init.c \
../src/p_interrupt.c \
../src/p_key.c \
../src/p_math.c \
../src/p_self.c \
../src/p_startup.c \
../src/p_timer_cmt0.c \
../src/p_timer_r0.c 

COMPILER_OBJS += \
src/ADS1148.obj \
src/Datatbl.obj \
src/MB85RS64V.obj \
src/PPM.obj \
src/PPM300.obj \
src/RX4571LC.obj \
src/advalue.obj \
src/p_comm0.obj \
src/p_comm1.obj \
src/p_comm12.obj \
src/p_comm_fhost.obj \
src/p_comm_fhost_cmd.obj \
src/p_comm_fhost_dir.obj \
src/p_comm_fhost_eng.obj \
src/p_comm_fhost_joso.obj \
src/p_comm_fhost_mai.obj \
src/p_comm_fhost_maiR.obj \
src/p_comm_fhost_maiW.obj \
src/p_comm_fhost_mon.obj \
src/p_comm_func.obj \
src/p_comm_rtu.obj \
src/p_comm_shinko.obj \
src/p_comm_sub.obj \
src/p_cont.obj \
src/p_cont_fan.obj \
src/p_cont_holiday.obj \
src/p_cont_reikyaku.obj \
src/p_factory.obj \
src/p_init.obj \
src/p_interrupt.obj \
src/p_key.obj \
src/p_math.obj \
src/p_self.obj \
src/p_startup.obj \
src/p_timer_cmt0.obj \
src/p_timer_r0.obj 

C_DEPS += \
src/ADS1148.d \
src/Datatbl.d \
src/MB85RS64V.d \
src/PPM.d \
src/PPM300.d \
src/RX4571LC.d \
src/advalue.d \
src/p_comm0.d \
src/p_comm1.d \
src/p_comm12.d \
src/p_comm_fhost.d \
src/p_comm_fhost_cmd.d \
src/p_comm_fhost_dir.d \
src/p_comm_fhost_eng.d \
src/p_comm_fhost_joso.d \
src/p_comm_fhost_mai.d \
src/p_comm_fhost_maiR.d \
src/p_comm_fhost_maiW.d \
src/p_comm_fhost_mon.d \
src/p_comm_func.d \
src/p_comm_rtu.d \
src/p_comm_shinko.d \
src/p_comm_sub.d \
src/p_cont.d \
src/p_cont_fan.d \
src/p_cont_holiday.d \
src/p_cont_reikyaku.d \
src/p_factory.d \
src/p_init.d \
src/p_interrupt.d \
src/p_key.d \
src/p_math.d \
src/p_self.d \
src/p_startup.d \
src/p_timer_cmt0.d \
src/p_timer_r0.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\cDepSubCommand.tmp"
	ccrx -subcommand="src\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cSubCommand.tmp"
	ccrx -subcommand="src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

