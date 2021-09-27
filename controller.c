#include "controller.h"
#include "os.h"
#include "led.h"
#include "serial.h"
#include "menu.h"
#include "reporter.h"

#define ACQUIRER_TASK_PHASE_40MS        (65496)

extern uint8_t SERIAL_FAULT_CODE_G   ; 

void acquirer_init(void)
{
	/*Dummy function .*/
}

void acquirer_update(void)
{
	static uint16_t counter_ms = ACQUIRER_TASK_PHASE_40MS;
	
	counter_ms += OS_TICK_MS ; 
	if(counter_ms != ACQUIRER_TASK_PERIOD_MS)
	{
		return ;
	}
	counter_ms =0 ; 
	
	if((SERIAL_FAULT_CODE_G == SERIAL_TIMEOUT_FAULT) || (SERIAL_FAULT_CODE_G == SERIAL_BUFFER_OUT_OF_SIZE_FAULT))
	{
		reporter_set_state(FAULT); 
		menu_set_state(IDLE);   
		led_set_state(OFF) ; 
	}
}