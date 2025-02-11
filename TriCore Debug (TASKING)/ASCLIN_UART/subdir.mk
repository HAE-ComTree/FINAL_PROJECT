################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../ASCLIN_UART/ASCLIN_UART.c" 

COMPILED_SRCS += \
"ASCLIN_UART/ASCLIN_UART.src" 

C_DEPS += \
"./ASCLIN_UART/ASCLIN_UART.d" 

OBJS += \
"ASCLIN_UART/ASCLIN_UART.o" 


# Each subdirectory must supply rules for building sources it contributes
"ASCLIN_UART/ASCLIN_UART.src":"../ASCLIN_UART/ASCLIN_UART.c" "ASCLIN_UART/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/tngkr/Desktop/motor_example/Motor_ex3_PI_control/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"ASCLIN_UART/ASCLIN_UART.o":"ASCLIN_UART/ASCLIN_UART.src" "ASCLIN_UART/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-ASCLIN_UART

clean-ASCLIN_UART:
	-$(RM) ./ASCLIN_UART/ASCLIN_UART.d ./ASCLIN_UART/ASCLIN_UART.o ./ASCLIN_UART/ASCLIN_UART.src

.PHONY: clean-ASCLIN_UART

