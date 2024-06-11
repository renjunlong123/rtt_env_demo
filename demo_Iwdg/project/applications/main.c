/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     balanceTWK   first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#include "u_macro.h"
#endif /* RT_USING_NANO */
#include <string.h>
#include "main.h"
#include "stm32f1xx_hal_iwdg.h"

rt_device_t serial_2_dev;
rt_uint8_t flag=0;
rt_thread_t _main_thread,_serial_2_rx_thread;
rt_sem_t Serial_2_rx_sem;
IWDG_HandleTypeDef hiwdg;

static void serial_init(void);
static rt_err_t Serial_2_Rx_CallBack(rt_device_t dev,rt_size_t size);
static void _main_th_entrance(void *parameter);
static void _serial_2_rx_th_entrance(void *parameter);
static void MX_IWDG_Init(void);

uint8_t buf_1[3]={01,02,03};

int main(void)
{
	serial_init();
//	MX_IWDG_Init();
//	rt_device_write(serial_2_dev,0,buf_1,3);
	Serial_2_rx_sem=rt_sem_create("serial_2_tx_sem",0,RT_IPC_FLAG_PRIO);
	if(Serial_2_rx_sem==RT_NULL)
	{
		flag=1;
	}
	/*main thread create*/
	_main_thread=rt_thread_create(_main_th_name,_main_th_entrance,RT_NULL,_main_th_stack_size
					,_main_th_priority,_main_th_stick);
	if(_main_thread)
	{
			rt_thread_startup(_main_thread);
	}
	/*serial 2 rx thread create*/
	_serial_2_rx_thread=rt_thread_create(_serial_2_rx_th_name,_serial_2_rx_th_entrance,RT_NULL,_serial_2_rx_th_stack_size
					,_serial_2_rx_th_priority,_serial_2_rx_th_stick);
	if(_serial_2_rx_thread)
	{
			rt_thread_startup(_serial_2_rx_thread);
	}

}

 
 
static void MX_IWDG_Init(void)
{
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg)!= HAL_OK)
  {
    //Error_Handler();
  }
}

static void _main_th_entrance(void *parameter)
{
    for(;;)
    {

    }
}
/*serial rx thread entrance*/
static void _serial_2_rx_th_entrance(void *parameter)
{
	rt_uint8_t buf[50];
	rt_uint8_t len;
    for(;;)
    {
			if(rt_sem_take(Serial_2_rx_sem,100))
			{
				len=rt_device_read(serial_2_dev,0,buf,sizeof(buf));
				rt_device_write(serial_2_dev,0,buf,len);
				memset(buf,0,sizeof(buf));
				//rt_sem_release(Serial_2_tx_sem);
			}
    }
}






static void serial_init(void)
{
#define SERIAL_2_NAME_DEV 	"uart2"
	struct serial_configure serial_2_cfg=RT_SERIAL_CONFIG_DEFAULT;
	serial_2_dev=rt_device_find(SERIAL_2_NAME_DEV);
	if(serial_2_dev)
	{
		serial_2_cfg.baud_rate=BAUD_RATE_115200;
		serial_2_cfg.data_bits=DATA_BITS_8;
		serial_2_cfg.stop_bits=STOP_BITS_1;
		
		serial_2_cfg.bufsz=128;
		serial_2_cfg.flowcontrol=PARITY_NONE;

		rt_device_control(serial_2_dev,RT_DEVICE_CTRL_CONFIG,&serial_2_cfg);
		rt_device_open(serial_2_dev,RT_DEVICE_FLAG_RDWR|RT_DEVICE_FLAG_DMA_RX);
		rt_device_set_rx_indicate(serial_2_dev,Serial_2_Rx_CallBack);
	}
}

static rt_err_t Serial_2_Rx_CallBack(rt_device_t dev,rt_size_t size)
{
	rt_sem_release(Serial_2_rx_sem);
	return RT_EOK;
}

