################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/rx113/mcu_clocks.c \
../src/smc_gen/r_bsp/mcu/rx113/mcu_init.c \
../src/smc_gen/r_bsp/mcu/rx113/mcu_interrupts.c \
../src/smc_gen/r_bsp/mcu/rx113/vecttbl.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/rx113/mcu_clocks.obj \
src/smc_gen/r_bsp/mcu/rx113/mcu_init.obj \
src/smc_gen/r_bsp/mcu/rx113/mcu_interrupts.obj \
src/smc_gen/r_bsp/mcu/rx113/vecttbl.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/rx113/mcu_clocks.d \
src/smc_gen/r_bsp/mcu/rx113/mcu_init.d \
src/smc_gen/r_bsp/mcu/rx113/mcu_interrupts.d \
src/smc_gen/r_bsp/mcu/rx113/vecttbl.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/rx113/%.obj: ../src/smc_gen/r_bsp/mcu/rx113/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\mcu\rx113\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rx113\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx113\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_bsp\mcu\rx113\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rx113\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx113\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

