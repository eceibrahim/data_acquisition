#include "menu.h"
#include "serial.h"
#include "Main.h"
#include "led.h"
#include "os.h"

static menu_state_t menu_state ; 

void menu_init(void)
{
	menu_state = DISPLAY ;
}

void menu_update(void)
{
	uint8_t data  = 0 ;
	static uint16_t counter_ms   = 0; 
	
	counter_ms += OS_TICK_MS ;  
	if(counter_ms != MENU_TASK_PERIOD_MS)
	{
		return ;
	}
	counter_ms =0 ;
	
	switch(menu_state)
	{
		case IDLE :
		{
			/*Do nothing here !*/
			break;
		}
		case DISPLAY :
		{
			serial_send_data("\rMenu :\n");
			serial_send_data("\rO - Open the led .\n"); 
			serial_send_data("\rC - Close the led .\n\n");
			serial_send_data("\r? : ");
			
			menu_state = WAITING ; 
			break ; 
		}
		case WAITING :
		{
			data = serial_get_data();
			if(data != SERIAL_NO_CHAR)
			{
				switch(data)
				{
					case 'O' :
					case 'o' :
					{
						
						/*Send data to serial */
						serial_send_data("O\n\rLed is opened .\n\n");
						led_set_state(ON);
						break ;
					}
					case 'C' :
					case 'c' :
					{
						/*Reset the led pin*/
						
						/*Send data to serial */
						serial_send_data("C\n\rLed is closed .\n\n");
						led_set_state(OFF);
						break ;
					}
					default :
					{
						/*Should not be here !*/
						break ;
					}
				}
				menu_state = DISPLAY ; 
			}
			break; 
		}
		default :
		{
			/*Should not be here !*/
			break ;
		}
	}
}

void menu_set_state(menu_state_t state)
{
	menu_state = state; 
}
