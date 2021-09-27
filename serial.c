#include "serial.h"
#include "queue.h"
#include <string.h>
#include <stdbool.h>

#define SERIAL_TRANSFER_MAX_DURATION_MS           (20)

typedef enum serial_state_tag 
{
	IDLE = 0, 
	NORMAL 
}serial_state_t ; 

typedef enum timeout_state_tag 
{
	STOP = 0, 
	START   
}timeout_state_t ; 

uint8_t SERIAL_FAULT_CODE_G   ; 

static queue_t transfer_buffer ; 
static queue_t receive_buffer ; 
static serial_state_t receive_state ; 
static serial_state_t transfer_state ; 

void serial_init(void)
{
	
	USART_InitTypeDef  usart_cfgr ;
	GPIO_InitTypeDef gpio_cfgr_pin ;
	
	/*Configure pin a2  */ 
	gpio_cfgr_pin.GPIO_Pin = GPIO_Pin_2 ;
	gpio_cfgr_pin.GPIO_Speed =GPIO_Speed_10MHz; 
	gpio_cfgr_pin.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio_cfgr_pin);
	
	
	/*Configure pin a3 */
	gpio_cfgr_pin.GPIO_Pin = GPIO_Pin_3 ;
	gpio_cfgr_pin.GPIO_Speed =GPIO_Speed_10MHz;
	gpio_cfgr_pin.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(GPIOA, &gpio_cfgr_pin);
	
	/*Remap pins for usart*/
	GPIO_PinRemapConfig(GPIO_Remap_USART2 , ENABLE);
	
	/*Configure usart2 */
	usart_cfgr.USART_BaudRate = 9600 ;
	usart_cfgr.USART_WordLength =  USART_WordLength_8b ;
	usart_cfgr.USART_StopBits = USART_StopBits_1 ;
	usart_cfgr.USART_Parity = USART_Parity_No ;
	usart_cfgr.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;
	usart_cfgr.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	
	USART_Cmd(USART2 , ENABLE );
	USART_Init(USART2 , &usart_cfgr);
	
	queue_init(&transfer_buffer); 
	queue_init(&receive_buffer); 
	
	receive_state = NORMAL ;
	transfer_state = NORMAL ; 
	
	SERIAL_FAULT_CODE_G = 0 ;
	
}

void serial_send(void)
{
	static timeout_state_t timeout_state  = STOP ;
	static uint16_t time_out = 0; 
	uint8_t data = 0; 
	
	switch(transfer_state)
	{
		case IDLE :
		{
			/*Do nothing here !*/
			
			break ; 
		}
		case NORMAL :
		{
			if (SERIAL_FAULT_CODE_G == SERIAL_BUFFER_OUT_OF_SIZE_FAULT )
			{
				transfer_state = IDLE ; 
			}
			else 
			{
				if(timeout_state ==  STOP)
				{
					if(queue_is_empty(&transfer_buffer) == false)
					{
						data = queue_serve(&transfer_buffer) ;
						USART_SendData(USART2,data);
						time_out = 0;
						timeout_state = START ; 
					}
				}
				else if (timeout_state == START)
				{
					time_out += SERIAL_TRANSFER_TASK_PERIOD_MS ;
					if(USART_GetFlagStatus(USART2 , USART_FLAG_TC) == SET)
					{
						time_out =0 ; 
						timeout_state = STOP ;
						USART_ClearFlag(USART2 , USART_FLAG_TC) ;						
					}
					else if (time_out >= SERIAL_TRANSFER_MAX_DURATION_MS)
					{
						time_out =0 ; 
						USART_DeInit(USART2) ;
						timeout_state = STOP;
						transfer_state =  IDLE ;
						SERIAL_FAULT_CODE_G = SERIAL_TIMEOUT_FAULT ;
					} 
				} 
			}
			break ; 
		}
		default:
		{
			/*Should not be here !*/
			break ; 
		}
	}
}

void serial_receive(void)
{
	uint16_t data = 0; 
	
	switch(receive_state)
	{
		case IDLE :
		{
			/*Do nothing here !*/
			break ;
		}
		case NORMAL :
		{
			if ((SERIAL_FAULT_CODE_G == SERIAL_BUFFER_OUT_OF_SIZE_FAULT ) || (SERIAL_FAULT_CODE_G == SERIAL_TIMEOUT_FAULT)) 
			{
				receive_state = IDLE ; 
			}
			else if(USART_GetFlagStatus(USART2 , USART_FLAG_RXNE) == SET)
			{
				data = USART_ReceiveData(USART2);
				queue_append(&receive_buffer ,(uint8_t)data);
				USART_ClearFlag(USART2 , USART_FLAG_RXNE) ;
			}
			else 
			{
				/*Do nothing here !*/
			}
			break ; 
		}
		default :
		{
			/*Should not be here !*/
			break ; 
		}
	}
}

void serial_send_data(uint8_t * string)
{
	
	uint8_t current_index  = 0 ; 
	uint8_t string_size = 0;
	uint8_t buffer_size  = 0; 
	
	string_size = strlen(string);
	
	buffer_size = QUEUE_MAX_SIZE - queue_get_size(&transfer_buffer);
	
	if(string_size <= buffer_size)
	{
		while(string[current_index] != '\0')
		{
			queue_append(&transfer_buffer ,string[current_index]);
			current_index ++ ;
		}
	}
	else 
	{
		SERIAL_FAULT_CODE_G = SERIAL_BUFFER_OUT_OF_SIZE_FAULT ;
	}
	
}

uint8_t serial_get_data(void)
{
	uint8_t ret = SERIAL_NO_CHAR ; 
	
	if(queue_is_empty(&receive_buffer) == false)
	{
		ret = queue_serve(&receive_buffer);
	}
	
	return ret; 
}