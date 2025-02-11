################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../PI/GTM_ATOM_PWM.c" \
"../PI/PID_CON.c" \
"../PI/STM_Interrupt.c" 

COMPILED_SRCS += \
"PI/GTM_ATOM_PWM.src" \
"PI/PID_CON.src" \
"PI/STM_Interrupt.src" 

C_DEPS += \
"./PI/GTM_ATOM_PWM.d" \
"./PI/PID_CON.d" \
"./PI/STM_Interrupt.d" 

OBJS += \
"PI/GTM_ATOM_PWM.o" \
"PI/PID_CON.o" \
"PI/STM_Interrupt.o" 


# Each subdirectory must supply rules for building sources it contributes
"PI/GTM_ATOM_PWM.src":"../PI/GTM_ATOM_PWM.c" "PI/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PI/GTM_ATOM_PWM.o":"PI/GTM_ATOM_PWM.src" "PI/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PI/PID_CON.src":"../PI/PID_CON.c" "PI/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PI/PID_CON.o":"PI/PID_CON.src" "PI/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PI/STM_Interrupt.src":"../PI/STM_Interrupt.c" "PI/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PI/STM_Interrupt.o":"PI/STM_Interrupt.src" "PI/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-PI

clean-PI:
	-$(RM) ./PI/GTM_ATOM_PWM.d ./PI/GTM_ATOM_PWM.o ./PI/GTM_ATOM_PWM.src ./PI/PID_CON.d ./PI/PID_CON.o ./PI/PID_CON.src ./PI/STM_Interrupt.d ./PI/STM_Interrupt.o ./PI/STM_Interrupt.src

.PHONY: clean-PI

