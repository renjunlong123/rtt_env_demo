CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m3)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "C:/Users/Administrator/Downloads/env_released_1.3.5/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_ASM_COMPILER "C:/Users/Administrator/Downloads/env_released_1.3.5/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "C:/Users/Administrator/Downloads/env_released_1.3.5/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-g++.exe")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "C:/Users/Administrator/Downloads/env_released_1.3.5/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe")
SET(CMAKE_SIZE "C:/Users/Administrator/Downloads/env_released_1.3.5/env-windows-v1.3.5/tools/ConEmu/ConEmu/../../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-size.exe")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/link.lds")

SET(CMAKE_CXX_STANDARD 14)
PROJECT(rtthread C CXX ASM)
INCLUDE_DIRECTORIES(
	applications
	rt-thread/components/libc/compilers/common/include
	rt-thread/components/libc/compilers/newlib
	rt-thread/components/drivers/include
	board
	board/CubeMX_Config/Inc
	board/ports
	libraries/HAL_Drivers/drivers
	libraries/HAL_Drivers/drivers/config
	libraries/HAL_Drivers
	libraries/HAL_Drivers/CMSIS/Include
	.
	rt-thread/include
	rt-thread/libcpu/arm/common
	rt-thread/libcpu/arm/cortex-m3
	libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Include
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Inc
	rt-thread/components/libc/posix/io/epoll
	rt-thread/components/libc/posix/io/eventfd
	rt-thread/components/libc/posix/io/poll
	rt-thread/components/libc/posix/ipc
)

ADD_DEFINITIONS(
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-DSTM32F103xB
	-DUSE_HAL_DRIVER
	-D_POSIX_C_SOURCE=1
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	applications/main.c
	rt-thread/components/libc/compilers/common/cctype.c
	rt-thread/components/libc/compilers/common/cstdlib.c
	rt-thread/components/libc/compilers/common/cstring.c
	rt-thread/components/libc/compilers/common/ctime.c
	rt-thread/components/libc/compilers/common/cunistd.c
	rt-thread/components/libc/compilers/common/cwchar.c
	rt-thread/components/libc/compilers/newlib/syscalls.c
	rt-thread/components/drivers/core/device.c
	rt-thread/components/drivers/ipc/completion.c
	rt-thread/components/drivers/ipc/dataqueue.c
	rt-thread/components/drivers/ipc/pipe.c
	rt-thread/components/drivers/ipc/ringblk_buf.c
	rt-thread/components/drivers/ipc/ringbuffer.c
	rt-thread/components/drivers/ipc/waitqueue.c
	rt-thread/components/drivers/ipc/workqueue.c
	rt-thread/components/drivers/pin/pin.c
	rt-thread/components/drivers/serial/serial.c
	rt-thread/components/drivers/watchdog/watchdog.c
	board/CubeMX_Config/Src/stm32f1xx_hal_msp.c
	board/board.c
	libraries/HAL_Drivers/drivers/drv_gpio.c
	libraries/HAL_Drivers/drivers/drv_usart.c
	libraries/HAL_Drivers/drivers/drv_wdt.c
	libraries/HAL_Drivers/drv_common.c
	libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s
	rt-thread/src/clock.c
	rt-thread/src/components.c
	rt-thread/src/idle.c
	rt-thread/src/ipc.c
	rt-thread/src/irq.c
	rt-thread/src/klibc/kstdio.c
	rt-thread/src/klibc/kstring.c
	rt-thread/src/kservice.c
	rt-thread/src/mem.c
	rt-thread/src/memheap.c
	rt-thread/src/mempool.c
	rt-thread/src/object.c
	rt-thread/src/scheduler_comm.c
	rt-thread/src/scheduler_up.c
	rt-thread/src/thread.c
	rt-thread/src/timer.c
	rt-thread/libcpu/arm/common/atomic_arm.c
	rt-thread/libcpu/arm/common/div0.c
	rt-thread/libcpu/arm/common/showmem.c
	rt-thread/libcpu/arm/cortex-m3/context_gcc.S
	rt-thread/libcpu/arm/cortex-m3/cpuport.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
	libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_wwdg.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
	libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)