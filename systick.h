#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>


typedef struct systick_tag
{
   uint32_t CTRL;       /*!<SysTick control and status register*/
   uint32_t LOAD;       /*!<SysTick reload value register*/
   uint32_t VAL;        /*!<SysTick current value register*/
   uint32_t CALIB;      /*!<SysTick calibration value register*/
}systick_t;

typedef struct systick_timebase_tag
{
  uint32_t clock_source ;         /*!<Specifies the clock source value of SystemTick timer*/
  uint32_t counter_value ;        /*!<Specifies the load value to be loaded into counter register */
}systick_timebase_t;


#define IS_SYSTICK_COUNTER_VALUE(VALUE) ((VALUE >= 0x00000001) && (VALUE <= 0x00FFFFFF))

/** @defgroup Systick clock source
  * @{
  */

#define SYSTICK_CPU_CLOCK_DIV_8  ((uint32_t)(0xFFFFFFFB))
#define SYSTICK_CPU_CLOCK_DIV_1  ((uint32_t)(0x00000004))
#define IS_SYSTICK_CLOCK_SOURCE(SOURCE) ((SOURCE == SYSTICK_CPU_CLOCK_DIV_8) || (SOURCE == SYSTICK_CPU_CLOCK_DIV_1))

/**
  * @}
  */

/** @defgroup Systick timer state
  * @{
  */

#define SYSTICK_OFF  ((uint32_t)(0xFFFFFFFE))
#define SYSTICK_ON   ((uint32_t)(0x00000001))
#define IS_SYSTICK_STATE(STATE)    ((STATE == SYSTICK_OFF) || (STATE == SYSTICK_ON))

/**
  * @}
  */

/** @defgroup Systick interrupt state
  * @{
  */

#define SYSTICK_INTERRUPT_ON  ((uint32_t)(0x00000002))
#define SYSTICK_INTERRUPT_OFF ((uint32_t)(0xFFFFFFFC))
#define IS_SYSTICK_INTERRUPT_STATE(STATE) ((STATE == SYSTICK_INTERRUPT_ON) || (STATE == SYSTICK_INTERRUPT_OFF))

/**
  * @}
  */

/** @defgroup Systick interrupt flag
  * @{
  */

#define SYSTICK_INTERRUPT_FLAG ((uint32_t)(0x00010000))

/**
  * @}
  */


/** @defgroup Systick exported functions
  * @{
  */

void systick_init (systick_timebase_t  * timebase);
void systick_timebase_init(systick_timebase_t  * timebase);
void systick_timebase_setcounter(systick_timebase_t  * timebase , uint32_t value);
void systick_timebase_setclocksource(systick_timebase_t  * timebase , uint32_t source);
uint32_t systick_get_counter(void);
void systick_set_counter(uint32_t counter_value);
uint8_t systick_get_flag_status(void);
void systick_clear_flag(void);
void systick_set_state(uint32_t  state);
uint8_t  systick_get_interrupt_flag(void);
void systick_set_interrupt_state(uint32_t state);
uint32_t systick_get_clibrate_info(void);
uint8_t systick_get_skew_flag (void);
uint8_t systick_get_noref_flag(void);

/**
  * @}
  */


#endif /*__SYSTICK_H__*/