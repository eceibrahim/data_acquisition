#include "led.h"
#include "gpio.h"
#include "Port.h"
#include "os.h"

#define LED_TASK_PHASE_20MS             (65516)

static led_state_t led_state ; 

void led_init(void)
{
	gpio_init_portpin (LED_PORT , LED_PIN ,GPIO_Output);
	gpio_set_portpinstate(LED_PORT  , LED_PIN , OFF);
	led_state = OFF ; 
}

void led_update(void)
{
	static uint16_t counter_ms = LED_TASK_PHASE_20MS ; 
	
	counter_ms +=OS_TICK_MS ; 
	if(counter_ms != LED_TASK_PERIOD_MS )
	{
		return ; 
	}
	counter_ms = 0;
	
	gpio_set_portpinstate(LED_PORT , LED_PIN , led_state);
	
}

void led_set_state(led_state_t state)
{
	led_state = state ;
}

led_state_t led_get_state(void)
{
	led_state_t ret ; 
	ret = led_state; 
	return ret; 
}
