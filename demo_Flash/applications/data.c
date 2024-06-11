#include "data.h"


FlashParm_TypeDef f;
void write_flash(void)
{
	f.address=FLASH_SAVE_START_ADDRESS;
	f.length=FLASH_DATA_LENGTH;
	for(uint8_t i=0;i<FLASH_DATA_LENGTH;i++)
	{
		f.w_data[i]=0x11223344;
	}
	if(stm32_hal_flash_write(&f)==f.length)
	{
		stm32_hal_flash_read(&f,0x32);
		stm32_hal_flash_read(&f,0x16);
		stm32_hal_flash_read(&f,0x8);
	}
}