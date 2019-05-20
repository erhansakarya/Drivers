################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
HTU21D_TemperatureHumiditySensor_HAL.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
HTU21D_TemperatureHumiditySensor_HAL.list \


# All Target
all: HTU21D_TemperatureHumiditySensor_HAL.elf secondary-outputs

# Tool invocations
HTU21D_TemperatureHumiditySensor_HAL.elf: $(OBJS) $(USER_OBJS) C:\Users\erhan\github\Drivers\HTU21D_TemperatureHumiditySensor\STM32F1_HAL\HTU21D_TemperatureHumiditySensor_HAL\STM32F103RBTX_FLASH.ld
	arm-none-eabi-gcc -o "HTU21D_TemperatureHumiditySensor_HAL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\erhan\github\Drivers\HTU21D_TemperatureHumiditySensor\STM32F1_HAL\HTU21D_TemperatureHumiditySensor_HAL\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="HTU21D_TemperatureHumiditySensor_HAL.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

HTU21D_TemperatureHumiditySensor_HAL.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "HTU21D_TemperatureHumiditySensor_HAL.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
