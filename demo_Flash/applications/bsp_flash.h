#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

/**
 @brief Include
 */
#include "dev_init.h"

typedef struct
{
	uint32_t address;
	uint32_t end_address;
	uint16_t length;
	uint32_t w_data[FLASH_DATA_MAX_LENGTH];
	uint32_t r_data_word[FLASH_DATA_MAX_LENGTH];
	uint16_t r_data_halfword[FLASH_DATA_MAX_LENGTH*2];
	uint8_t r_data_byte[FLASH_DATA_MAX_LENGTH*4];
}FlashParm_TypeDef;


/**
 @brief function
 */
uint8_t stm32_hal_flash_write(FlashParm_TypeDef* f_parm);
void stm32_hal_flash_read(FlashParm_TypeDef* f_parm,uint8_t bit);

#endif
