################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/board/generic_rx113/hwsetup.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/board/generic_rx113/hwsetup.obj 

C_DEPS += \
src/smc_gen/r_bsp/board/generic_rx113/hwsetup.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/board/generic_rx113/%.obj: ../src/smc_gen/r_bsp/board/generic_rx113/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\board\generic_rx113\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rx113\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx113\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_bsp\board\generic_rx113\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rx113\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx113\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

