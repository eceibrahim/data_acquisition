#ifndef __REPORTER_H__ 
#define __REPORTER_H__ 

#define REPORTER_TASK_PERIOD_MS          (100) 

typedef enum reporter_state_tag
{
	NO_FAULT ,
	FAULT 
}reporter_state_t; 

void reporter_init(void); 
void reporter_update(void);
void reporter_set_state(reporter_state_t state) ; 

#endif /*__REPORTER_H__*/
