################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Programming/TI/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O3 --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx" --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx/Debug" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/kernel/tirtos7/packages" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source/ti/posix/ccs" --include_path="C:/Programming/TI/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-258066767: ../config.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/Programming/TI/CCS/ccs/utils/sysconfig_1.12.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/.metadata/product.json" --script "C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx/config.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_easylink_config.h: build-258066767 ../config.syscfg
syscfg/ti_easylink_config.c: build-258066767
syscfg/ti_devices_config.c: build-258066767
syscfg/ti_radio_config.c: build-258066767
syscfg/ti_radio_config.h: build-258066767
syscfg/ti_drivers_config.c: build-258066767
syscfg/ti_drivers_config.h: build-258066767
syscfg/ti_utils_build_linker.cmd.genlibs: build-258066767
syscfg/syscfg_c.rov.xs: build-258066767
syscfg/ti_utils_runtime_model.gv: build-258066767
syscfg/ti_utils_runtime_Makefile: build-258066767
syscfg/ti_sysbios_config.h: build-258066767
syscfg/ti_sysbios_config.c: build-258066767
syscfg/: build-258066767

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Programming/TI/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O3 --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx" --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx/Debug" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/kernel/tirtos7/packages" --include_path="C:/ti/simplelink_cc13xx_cc26xx_sdk_6_10_00_29/source/ti/posix/ccs" --include_path="C:/Programming/TI/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=DeviceFamily_CC13X2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Projects/CCS/Scientific-Initiation-Projects/BlinkAtFrequencyRx/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


