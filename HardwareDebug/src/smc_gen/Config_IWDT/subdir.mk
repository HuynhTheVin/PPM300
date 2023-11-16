################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/Config_IWDT/Config_IWDT.c \
../src/smc_gen/Config_IWDT/Config_IWDT_user.c 

COMPILER_OBJS += \
src/smc_gen/Config_IWDT/Config_IWDT.obj \
src/smc_gen/Config_IWDT/Config_IWDT_user.obj 

C_DEPS += \
src/smc_gen/Config_IWDT/Config_IWDT.d \
src/smc_gen/Config_IWDT/Config_IWDT_user.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/Config_IWDT/%.obj: ../src/smc_gen/Config_IWDT/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\Config_IWDT\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\Config_IWDT\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\Config_IWDT\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\Config_IWDT\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\Config_IWDT\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\Config_IWDT\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

