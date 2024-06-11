#include "app_data.h"

#define write_length 128
#define read_length  256
uint8_t w25q64_write_buf[write_length]={0};
uint8_t w25q64_read_buf[read_length]={0};
uint8_t buf[1]={0};
void w25q64_test(void)
{
	uint16_t i=0,j=0;
	for(i=0;i<write_length;i++)
	{
		w25q64_write_buf[i]=0xab;
		j++;
	}
	spi_w25qxx_write_enable();
	spi_w25qxx_erase_sector(W25Qxx_Write_Page_Addr_1,W25Qxx_SECTOR_ERASE_4KB);
	spi_w25qxx_write_page(W25Qxx_Write_Page_Addr_1,w25q64_write_buf,write_length);
	for(i=0;i<write_length;i++)
	{
		w25q64_write_buf[i]=j;
		j++;
	}	
	spi_w25qxx_write_page(W25Qxx_Write_Page_Addr_1+128,w25q64_write_buf,write_length);
	spi_w25qxx_read(W25Qxx_Write_Page_Addr_1,w25q64_read_buf,read_length);
	rt_device_write(Dev_InitStruct.dev_serial_1,0,w25q64_read_buf,sizeof(w25q64_read_buf));

}

