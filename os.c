#include "os.h"
#include "systick.h"
#include "menu.h"
#include "controller.h"
#include "led.h"
#include "reporter.h"
#include "serial.h"

extern void SysTick_Handler(void) ;

void os_init(void)
{
	systick_timebase_t time ; 
	
	systick_timebase_setclocksource(&time , SYSTICK_CPU_CLOCK_DIV_8) ;
	
	systick_timebase_setcounter(&time , 179999);
	
	systick_init(&time); 
}

void os_start(void) 
{
	systick_set_interrupt_state(SYSTICK_INTERRUPT_ON);
	systick_set_state(SYSTICK_ON);
}

void os_sleep(void)
{
	__asm("WFI");
}

void SysTick_Handler(void)
{
	serial_receive(); 
	menu_update(); 
	serial_send(); 
	led_update(); 
	acquirer_update(); 
	reporter_update(); 
}