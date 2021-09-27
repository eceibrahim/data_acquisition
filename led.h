#ifndef __LED_H__ 
#define __LED_H__

#define LED_TASK_PERIOD_MS               (1000)

typedef enum led_state_tag 
{
	OFF = 0, 
	ON 
}led_state_t ; 

void led_init(void);
void led_update(void);
void led_set_state(led_state_t state);
led_state_t led_get_state(void); 

#endif /*__LED_H__*/