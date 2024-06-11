#include "bootloader.h"

ota_parm ota_parm_info;
p_app load_app;
void bootloader_brance(void);
void iap_load_app(uint32_t address);

/*读取ota，判断是否ota升级*/
void w25q64_read_ota_parm_info(void)
{
#define OTA_PARM_INFO_SIZE sizeof(ota_parm_info)
	uint8_t ota_flag=0xff;
	memset(&ota_parm_info,0,OTA_PARM_INFO_SIZE);
	spi_w25qxx_read(OTA_FLAG_ADDR,&ota_parm_info,OTA_PARM_INFO_SIZE);
	if(ota_parm_info.ota_flag==OTA_FLAG)
	{
#ifdef BOOTLOART_LOG
		ota_flag=1;
		rt_device_write(Dev_InitStruct.dev_serial_1,0,&ota_flag,sizeof(ota_flag));
#endif
		/*跳转分支*/
		bootloader_brance();
	}
	else
	{
#ifdef BOOTLOART_LOG
		ota_flag=0;
		rt_device_write(Dev_InitStruct.dev_serial_1,0,&ota_flag,sizeof(ota_flag));
#endif
		iap_load_app(STM32_A_PAGE_ADDR);
	}
}

void bootloader_brance(void)
{
	
}
/*设置sp指针*/
__asm void msr_sp(uint32_t address)
{
	MSR MSP,r0/*address保存在r0中*/
	BX r14    /*链接寄存器，保存子函数跳转的返回值*/
}

/*设置pc指针*/
void iap_load_app(uint32_t address)
{
	/*判断栈指针是否合法*/
	if((*(__IO uint32_t*)address>0x20000000)&&(*(__IO uint32_t*)address<0x20000000+0x5000))
	{
		msr_sp(address);
		/*利用函数地址设置pc指针*/
		load_app=(p_app)(*(__IO uint32_t*)(address+4));/*load_app执行复位地址*/
		/*关闭所有中断*/
		__disable_irq();
		load_app();
	}
}
