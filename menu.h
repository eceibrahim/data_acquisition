#ifndef __MENU_H__ 
#define __MENU_H__ 

#define MENU_TASK_PERIOD_MS                (1000)

typedef enum menu_state_tag
{
	IDLE =0 , 
	DISPLAY ,
	WAITING  
}menu_state_t ;

void menu_init(void); 
void menu_update(void);
void menu_set_state(menu_state_t state);

#endif /*__MENU_H__*/
