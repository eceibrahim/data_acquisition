#include "os.h"
#include "menu.h"
#include "controller.h"
#include "reporter.h"
#include "serial.h"
#include "led.h"
#include "pclock.h"

int main(void)
{
	os_init(); 
	pclock_init(); 
	menu_init(); 
	serial_init(); 
	led_init(); 
	acquirer_update(); 
	reporter_init(); 
	os_start(); 
	while(1)
	{
		os_sleep(); 
	}
	return 0;
}


