#ifndef __U_MACRO_H
#define __U_MACRO_H

#define True  0
#define Error 1

/**
 @brief thread macro
 */
/*main thread macro*/
#define _main_th_name                         "main"
#define _main_th_stack_size                   512
#define _main_th_priority                     15
#define _main_th_stick                        5
/*serial_2_rx thread macro*/
#define _serial_2_rx_th_name                  "serial_2_rx"
#define _serial_2_rx_th_stack_size            256
#define _serial_2_rx_th_priority              15
#define _serial_2_rx_th_stick                 5
/*serial_2_tx thread macro*/
#define _serial_2_tx_th_name                  "serial_2_tx"
#define _serial_2_tx_th_stack_size            256
#define _serial_2_tx_th_priority              15
#define _serial_2_tx_th_stick                 5

/**
 @brief parm macro
 */
/*serial*/
#define serial_2_rx_buf_size 128
#define serial_2_tx_buf_size 128

/**
 @brief IO macro
 */
/*程序运行指示灯 PB12*/
#define _IO_RUN_STU_PORT                GPIOB
    #define _IO_RUN_STU                 GPIO_PIN_12
    #define _IO_RUN_STU_H               HAL_GPIO_WritePin(_IO_RUN_STU_PORT,_IO_RUN_STU, GPIO_PIN_SET)
    #define _IO_RUN_STU_L               HAL_GPIO_WritePin(_IO_RUN_STU_PORT,_IO_RUN_STU, GPIO_PIN_RESET)
#endif

