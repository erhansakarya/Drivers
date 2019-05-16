################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
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
TTP223B_CatalexTouchSensor_STM32F7_HAL.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TTP223B_CatalexTouchSensor_STM32F7_HAL.list \


# All Target
all: TTP223B_CatalexTouchSensor_STM32F7_HAL.elf secondary-outputs

# Tool invocations
TTP223B_CatalexTouchSensor_STM32F7_HAL.elf: $(OBJS) $(USER_OBJS) C:\Users\erhan\github\Drivers\CatalexTTP223B_TouchSensor\STM32F7_HAL\TTP223B_CatalexTouchSensor_STM32F7_HAL\STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "TTP223B_CatalexTouchSensor_STM32F7_HAL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\erhan\github\Drivers\CatalexTTP223B_TouchSensor\STM32F7_HAL\TTP223B_CatalexTouchSensor_STM32F7_HAL\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TTP223B_CatalexTouchSensor_STM32F7_HAL.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TTP223B_CatalexTouchSensor_STM32F7_HAL.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TTP223B_CatalexTouchSensor_STM32F7_HAL.list"
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
