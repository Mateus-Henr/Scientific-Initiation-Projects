################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
easylink/%.obj: ../easylink/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"F:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O3 --include_path="F:/Scientific-Initiation-Projects/MoveStructsRx" --include_path="F:/Scientific-Initiation-Projects/MoveStructsRx/Debug" --include_path="F:/ti/ccs1110/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source" --include_path="F:/ti/ccs1110/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/kernel/tirtos7/packages" --include_path="F:/ti/ccs1110/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source/ti/posix/ccs" --include_path="F:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="easylink/$(basename $(<F)).d_raw" --include_path="F:/Scientific-Initiation-Projects/MoveStructsRx/Debug/syscfg" --obj_directory="easylink" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


