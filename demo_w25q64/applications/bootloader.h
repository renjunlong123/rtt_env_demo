#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

/**
 @brief Include
 */
#include "spi_w25q64.h"

/**
 @brief Parm
 */
typedef struct
{
	uint8_t ota_flag;
	
}ota_parm;

extern ota_parm ota_parm_info;

/**
 @brief Function
 */
typedef void (*p_app)(void);
void w25q64_read_ota_parm_info(void);
#endif
