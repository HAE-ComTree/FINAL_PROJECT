################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../ERU_It/ERU_Interrupt.c" 

COMPILED_SRCS += \
"ERU_It/ERU_Interrupt.src" 

C_DEPS += \
"./ERU_It/ERU_Interrupt.d" 

OBJS += \
"ERU_It/ERU_Interrupt.o" 


# Each subdirectory must supply rules for building sources it contributes
"ERU_It/ERU_Interrupt.src":"../ERU_It/ERU_Interrupt.c" "ERU_It/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/Motor_A_B/Motor_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"ERU_It/ERU_Interrupt.o":"ERU_It/ERU_Interrupt.src" "ERU_It/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-ERU_It

clean-ERU_It:
	-$(RM) ./ERU_It/ERU_Interrupt.d ./ERU_It/ERU_Interrupt.o ./ERU_It/ERU_Interrupt.src

.PHONY: clean-ERU_It

