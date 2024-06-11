#include "app_u.h"


Serial_Value Serial_ValueStruct={0};

static void _main_th_entrance(void *parameter);
static void _serial_rx_th_entrance(void *parameter);
static void _serial_tx_th_entrance(void *parameter);

/*init*/
uint8_t u_init(void)
{
	io_init();
	if(Serial_Init(115200)==_Error)
	{
		return _Error;
	}
	if(spi_w25qxx_init()==_OK)
	{
		//w25q64_read_ota_parm_info();
	}
	else
	{
		return _Error;
	}
	if(RT_Sem_Init()==_Error)
	{
		return _Error;
	}
	rt_thread_mdelay(1000);
	return _OK;
}

/*thread init*/
uint8_t rt_create_thread_init(void)
{
	Flag_Struct.Rt_Thread_Init_flag=0;
	/*main thread create*/
	RT_Thread_InitStruct._main_thread=rt_thread_create(_main_th_name,_main_th_entrance,RT_NULL,_main_th_stack_size
					,_main_th_priority,_main_th_stick);
	if(RT_Thread_InitStruct._main_thread)
	{
			rt_thread_startup(RT_Thread_InitStruct._main_thread);
	}
	else
	{
		Flag_Struct.Rt_Thread_Init_flag=flag_Error;
	}
	/*serial rx thread create*/
	RT_Thread_InitStruct._serial_rx_thread=rt_thread_create(_serial_rx_th_name,_serial_rx_th_entrance,RT_NULL,_serial_rx_th_stack_size
					,_serial_rx_th_priority,_serial_rx_th_stick);
	if(RT_Thread_InitStruct._serial_rx_thread)
	{
			rt_thread_startup(RT_Thread_InitStruct._serial_rx_thread);
	}
	else
	{
		Flag_Struct.Rt_Thread_Init_flag=flag_Error;
	}
	/*serial tx thread create*/
	RT_Thread_InitStruct._serial_tx_thread=rt_thread_create(_serial_tx_th_name,_serial_tx_th_entrance,RT_NULL,_serial_tx_th_stack_size
					,_serial_tx_th_priority,_serial_tx_th_stick);
	if(RT_Thread_InitStruct._serial_tx_thread)
	{
			rt_thread_startup(RT_Thread_InitStruct._serial_tx_thread);
	}
	else
	{
		Flag_Struct.Rt_Thread_Init_flag=flag_Error;
	}
	return ((Flag_Struct.Rt_Thread_Init_flag==flag_Error)?_Error:_OK);
}


/*thread entrance*/
static void _main_th_entrance(void *parameter)
{
#if 0
	w25q64_test();
#endif
	for(;;)
	{
		
	}
}
static void _serial_rx_th_entrance(void *parameter)
{
	for(;;)
	{
		if(rt_sem_take(RT_Thread_InitStruct.Serial_1_rx_sem,100)==RT_EOK)
		{
			Serial_ValueStruct.serial_1_rx_length=rt_device_read(Dev_InitStruct.dev_serial_1,0,Serial_ValueStruct.serial_1_rx_buf
							,serial_1_rx_buf_size);
			rt_sem_release(RT_Thread_InitStruct.Serial_1_tx_sem);
		}
	}
}
static void _serial_tx_th_entrance(void *parameter)
{
	for(;;)
	{
		if(rt_sem_take(RT_Thread_InitStruct.Serial_1_tx_sem,100)==RT_EOK)
		{
			rt_device_write(Dev_InitStruct.dev_serial_1,0,Serial_ValueStruct.serial_1_rx_buf
							,Serial_ValueStruct.serial_1_rx_length);
			memset(Serial_ValueStruct.serial_1_rx_buf,0,Serial_ValueStruct.serial_1_rx_length);
		}
	}
}
