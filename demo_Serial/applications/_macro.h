#ifndef ___MACRO_H
#define ___MACRO_H

/*Return Value*/
#define _Error 		0x00
#define _OK			0xff

/*Flag Value*/
#define flag_Error 		0x0a
#define flag_OK		 	0x0b

/*Dev name*/
#define DEV_SERIAL_1_NAME					"uart1"
#define DEV_SERIAL_2_NAME				  	"uart2"
#define SERIAL_1_RX_SEM_NAME 				"serial_1_rx_sem"
#define SERIAL_1_TX_SEM_NAME 				"serial_1_tx_sem"
#define SERIAL_2_RX_SEM_NAME 				"serial_2_rx_sem"
#define SERIAL_2_TX_SEM_NAME 				"serial_2_tx_sem"

/*serial*/
#define serial_1_rx_buf_size 						128
#define serial_2_rx_buf_size 						128


/**
 @brief thread macro
 */
 /*main thread macro*/
#define _main_th_name                       "main"
#define _main_th_stack_size                 512
#define _main_th_priority                   20
#define _main_th_stick                      5
/*serial_rx thread macro*/
#define _serial_rx_th_name                  "serial_rx"
#define _serial_rx_th_stack_size            256
#define _serial_rx_th_priority              10
#define _serial_rx_th_stick                 5
/*serial_tx thread macro*/
#define _serial_tx_th_name                  "serial_tx"
#define _serial_tx_th_stack_size            256
#define _serial_tx_th_priority              10
#define _serial_tx_th_stick                 5


#endif
