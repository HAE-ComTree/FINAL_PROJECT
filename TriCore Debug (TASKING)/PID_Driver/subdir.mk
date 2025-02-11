################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../PID_Driver/Encoder.c" \
"../PID_Driver/GTM_ATOM_PWM.c" \
"../PID_Driver/It_Handler.c" \
"../PID_Driver/PID_CON.c" \
"../PID_Driver/STM_Interrupt.c" \
"../PID_Driver/Set_Driving_Mode.c" 

COMPILED_SRCS += \
"PID_Driver/Encoder.src" \
"PID_Driver/GTM_ATOM_PWM.src" \
"PID_Driver/It_Handler.src" \
"PID_Driver/PID_CON.src" \
"PID_Driver/STM_Interrupt.src" \
"PID_Driver/Set_Driving_Mode.src" 

C_DEPS += \
"./PID_Driver/Encoder.d" \
"./PID_Driver/GTM_ATOM_PWM.d" \
"./PID_Driver/It_Handler.d" \
"./PID_Driver/PID_CON.d" \
"./PID_Driver/STM_Interrupt.d" \
"./PID_Driver/Set_Driving_Mode.d" 

OBJS += \
"PID_Driver/Encoder.o" \
"PID_Driver/GTM_ATOM_PWM.o" \
"PID_Driver/It_Handler.o" \
"PID_Driver/PID_CON.o" \
"PID_Driver/STM_Interrupt.o" \
"PID_Driver/Set_Driving_Mode.o" 


# Each subdirectory must supply rules for building sources it contributes
"PID_Driver/Encoder.src":"../PID_Driver/Encoder.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/Encoder.o":"PID_Driver/Encoder.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PID_Driver/GTM_ATOM_PWM.src":"../PID_Driver/GTM_ATOM_PWM.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/GTM_ATOM_PWM.o":"PID_Driver/GTM_ATOM_PWM.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PID_Driver/It_Handler.src":"../PID_Driver/It_Handler.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/It_Handler.o":"PID_Driver/It_Handler.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PID_Driver/PID_CON.src":"../PID_Driver/PID_CON.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/PID_CON.o":"PID_Driver/PID_CON.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PID_Driver/STM_Interrupt.src":"../PID_Driver/STM_Interrupt.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/STM_Interrupt.o":"PID_Driver/STM_Interrupt.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"PID_Driver/Set_Driving_Mode.src":"../PID_Driver/Set_Driving_Mode.c" "PID_Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PID_Driver/Set_Driving_Mode.o":"PID_Driver/Set_Driving_Mode.src" "PID_Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-PID_Driver

clean-PID_Driver:
	-$(RM) ./PID_Driver/Encoder.d ./PID_Driver/Encoder.o ./PID_Driver/Encoder.src ./PID_Driver/GTM_ATOM_PWM.d ./PID_Driver/GTM_ATOM_PWM.o ./PID_Driver/GTM_ATOM_PWM.src ./PID_Driver/It_Handler.d ./PID_Driver/It_Handler.o ./PID_Driver/It_Handler.src ./PID_Driver/PID_CON.d ./PID_Driver/PID_CON.o ./PID_Driver/PID_CON.src ./PID_Driver/STM_Interrupt.d ./PID_Driver/STM_Interrupt.o ./PID_Driver/STM_Interrupt.src ./PID_Driver/Set_Driving_Mode.d ./PID_Driver/Set_Driving_Mode.o ./PID_Driver/Set_Driving_Mode.src

.PHONY: clean-PID_Driver

