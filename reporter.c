#include "reporter.h"
#include "serial.h"
#include "Port.h"
#include "os.h"
#include "gpio.h"

#define REPORTER_TASK_PHASE_60MS          (196)


extern uint8_t SERIAL_FAULT_CODE_G ; 
static reporter_state_t reporter_state ; 

void reporter_init(void)
{
	reporter_state = NO_FAULT ;
	
	gpio_init_portpin(REPORTER_BUFFER_OUT_OF_SIZE_PORT ,REPORTER_BUFFER_OUT_OF_SIZE_PIN ,GPIO_Output);
	gpio_init_portpin(REPORTER_TIME_OUT_PORT , REPORTER_TIME_OUT_PIN , GPIO_Output);
	
	gpio_set_portpinstate(REPORTER_BUFFER_OUT_OF_SIZE_PORT , REPORTER_BUFFER_OUT_OF_SIZE_PIN  , 0);
	gpio_set_portpinstate(REPORTER_TIME_OUT_PORT ,REPORTER_TIME_OUT_PIN , 0 );
	
}	

void reporter_update(void)
{
	static uint8_t state = 0; 
	static uint8_t counter_ms = REPORTER_TASK_PHASE_60MS ;
	
	counter_ms += OS_TICK_MS ;
	if(counter_ms != REPORTER_TASK_PERIOD_MS)
	{
		return ;
	}
	
	counter_ms = 0; 
	
	switch(reporter_state)
	{
		case NO_FAULT :
		{
			/*Do nothing here*/
			break ;
		}
		case FAULT :
		{
			
			state ^= 1 ;
			
			if(SERIAL_FAULT_CODE_G == SERIAL_BUFFER_OUT_OF_SIZE_FAULT)
			{
				gpio_set_portpinstate(REPORTER_BUFFER_OUT_OF_SIZE_PORT , REPORTER_BUFFER_OUT_OF_SIZE_PIN  , state);
			}
			else if (SERIAL_FAULT_CODE_G == SERIAL_TIMEOUT_FAULT)
			{
				gpio_set_portpinstate(REPORTER_TIME_OUT_PORT , REPORTER_TIME_OUT_PIN  , state);
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

void reporter_set_state(reporter_state_t state) 
{
	reporter_state = state ; 
}