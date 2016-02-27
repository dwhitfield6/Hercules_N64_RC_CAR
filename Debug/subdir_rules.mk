################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
AUDIO.obj: ../AUDIO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="AUDIO.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DAC.obj: ../DAC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="DAC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ECAP.obj: ../ECAP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="ECAP.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

INTERRUPTS.obj: ../INTERRUPTS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="INTERRUPTS.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LED.obj: ../LED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="LED.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MISC.obj: ../MISC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="MISC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

N64.obj: ../N64.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="N64.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

POT.obj: ../POT.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="POT.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SPI.obj: ../SPI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="SPI.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SYSTEM.obj: ../SYSTEM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="SYSTEM.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TEST.obj: ../TEST.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="TEST.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TIMERS.obj: ../TIMERS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="TIMERS.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

USER.obj: ../USER.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="USER.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WAV.obj: ../WAV.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="WAV.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O0 --fp_mode=relaxed --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="C:/Users/pskkd/Documents/GitHub/Hercules_N64_RC_CAR/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --unaligned_access=off --enum_type=packed --gen_opt_info=0 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


