################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./AUDIO.obj" \
"./DAC.obj" \
"./ECAP.obj" \
"./INTERRUPTS.obj" \
"./LED.obj" \
"./MISC.obj" \
"./N64.obj" \
"./POT.obj" \
"./SPI.obj" \
"./SYSTEM.obj" \
"./TEST.obj" \
"./TIMERS.obj" \
"./USER.obj" \
"./WAV.obj" \
"./main.obj" \
"./source/HL_epc.obj" \
"./source/HL_errata.obj" \
"./source/HL_esm.obj" \
"./source/HL_gio.obj" \
"./source/HL_nmpu.obj" \
"./source/HL_notification.obj" \
"./source/HL_pinmux.obj" \
"./source/HL_sys_core.obj" \
"./source/HL_sys_dma.obj" \
"./source/HL_sys_intvecs.obj" \
"./source/HL_sys_mpu.obj" \
"./source/HL_sys_pcr.obj" \
"./source/HL_sys_phantom.obj" \
"./source/HL_sys_pmm.obj" \
"./source/HL_sys_pmu.obj" \
"./source/HL_sys_startup.obj" \
"./source/HL_sys_vim.obj" \
"./source/HL_system.obj" \
"../Linker/HL_sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include Linker/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include Linker/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Hercules_N64_RC_CAR.out \

EXE_OUTPUTS__QUOTED += \
"Hercules_N64_RC_CAR.out" \

BIN_OUTPUTS += \
Hercules_N64_RC_CAR.hex \

BIN_OUTPUTS__QUOTED += \
"Hercules_N64_RC_CAR.hex" \


# All Target
all: Hercules_N64_RC_CAR.out

# Tool invocations
Hercules_N64_RC_CAR.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=on --enum_type=packed --gen_opt_info=0 -z -m"Hercules_N64_RC_CAR.map" --heap_size=0x800 --stack_size=0x800 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" -i"C:/Users/dwhitfield/Documents/GitHub/Hercules_N64_RC_CAR/Linker" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="Hercules_N64_RC_CAR_linkInfo.xml" --rom_model --be32 -o "Hercules_N64_RC_CAR.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Hercules_N64_RC_CAR.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armhex"  -o "Hercules_N64_RC_CAR.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "AUDIO.pp" "DAC.pp" "ECAP.pp" "INTERRUPTS.pp" "LED.pp" "MISC.pp" "N64.pp" "POT.pp" "SPI.pp" "SYSTEM.pp" "TEST.pp" "TIMERS.pp" "USER.pp" "WAV.pp" "main.pp" "source\HL_epc.pp" "source\HL_errata.pp" "source\HL_esm.pp" "source\HL_gio.pp" "source\HL_nmpu.pp" "source\HL_notification.pp" "source\HL_pinmux.pp" "source\HL_sys_dma.pp" "source\HL_sys_pcr.pp" "source\HL_sys_phantom.pp" "source\HL_sys_pmm.pp" "source\HL_sys_startup.pp" "source\HL_sys_vim.pp" "source\HL_system.pp" 
	-$(RM) "AUDIO.obj" "DAC.obj" "ECAP.obj" "INTERRUPTS.obj" "LED.obj" "MISC.obj" "N64.obj" "POT.obj" "SPI.obj" "SYSTEM.obj" "TEST.obj" "TIMERS.obj" "USER.obj" "WAV.obj" "main.obj" "source\HL_epc.obj" "source\HL_errata.obj" "source\HL_esm.obj" "source\HL_gio.obj" "source\HL_nmpu.obj" "source\HL_notification.obj" "source\HL_pinmux.obj" "source\HL_sys_core.obj" "source\HL_sys_dma.obj" "source\HL_sys_intvecs.obj" "source\HL_sys_mpu.obj" "source\HL_sys_pcr.obj" "source\HL_sys_phantom.obj" "source\HL_sys_pmm.obj" "source\HL_sys_pmu.obj" "source\HL_sys_startup.obj" "source\HL_sys_vim.obj" "source\HL_system.obj" 
	-$(RM) "source\HL_sys_core.pp" "source\HL_sys_intvecs.pp" "source\HL_sys_mpu.pp" "source\HL_sys_pmu.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

