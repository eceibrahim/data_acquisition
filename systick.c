#include "systick.h"

/** @defgroup Peripheral_declaration
  * @{
  */

#define SYSTICK ((volatile systick_t *)(0xE000E010))

/**
  * @}
  */

#define SYSTICK_NOREF_FLAG  ((uint32_t)(0x80000000))
#define SYSTICK_SNEW_FLAG   ((uint32_t)(0x40000000))

static void SYSTICK_ASSERT_FAILED(void) ;

#define SYSTICK_ASSERT(EXPRESSION)  (EXPRESSION) ? (void)(0) : SYSTICK_ASSERT_FAILED()


/** @brief  Initializes the system tick Timer by the specified parameters in
  *         the timebase.
  * @param  systick_timebase_t : pointer to a systick_timebase_t
  *         structure that contains the configuration information for the
  *         system tick peripheral.
  * @retval None
  */
void systick_init (systick_timebase_t  * timebase)
{
  SYSTICK_ASSERT(IS_SYSTICK_COUNTER_VALUE(timebase->counter_value));

  SYSTICK_ASSERT(IS_SYSTICK_CLOCK_SOURCE(timebase->clock_source));

  SYSTICK->LOAD = timebase->counter_value ;

  if(timebase->clock_source == SYSTICK_CPU_CLOCK_DIV_1)
    {
      SYSTICK->CTRL |= SYSTICK_CPU_CLOCK_DIV_1;
    }
  else if (timebase->clock_source == SYSTICK_CPU_CLOCK_DIV_8)
    {
      SYSTICK->CTRL &= SYSTICK_CPU_CLOCK_DIV_8;
    }
  else
    {
      /*Should not be here !*/
    }
}

/** @brief  Fills each timebase members with its default value.
  * @param  timebase : pointer to a systick_timebase_t
  *         structure which will be initialized.
  * @assumption the processor clock is 72MHZ .
  * @retval None
  */
void systick_timebase_init(systick_timebase_t  * timebase)
{

  /* Set default parameters and make the timer flag
   * releases after 1ms if the processor clock is 72MHZ .
   */

  timebase->counter_value = 0x00002327;

  timebase->clock_source = SYSTICK_CPU_CLOCK_DIV_8 ;

}

/** @brief Fills timebase counter_value member
  * @param timebase : pointer to systick_timebase_t structure
  * @param counter_value : holds initial counter value and must be between 0x00000001 and 0x00FFFFFF
  * @retval None
  */
void systick_timebase_setcounter(systick_timebase_t  * timebase , uint32_t value)
{
  SYSTICK_ASSERT(IS_SYSTICK_COUNTER_VALUE(value));

  timebase->counter_value = value ;
}

/** @brief Fills timebase clock_source member
  * @param timebase : pointer to systick_timebase_t structure
  * @param clock_source : holds clock source command and it can one of the folllowing values :
  *        @arg SYSTICK_CPU_CLK_DIV_8
  *        @arg SYSTICK_CPU_CLK_DIV_1
  * @retval None
  */
void systick_timebase_setclocksource(systick_timebase_t  * timebase , uint32_t source)
{
  SYSTICK_ASSERT(IS_SYSTICK_CLOCK_SOURCE(source));

  timebase->clock_source = source ;
}

/** @brief  Gets system tick counter value
  * @param  None
  * @retval System tick counter register value
  */
uint32_t systick_get_counter(void)
{
  uint32_t ret = 0;
  ret = SYSTICK->VAL;
  return ret ;
}

/** @param  Sets system tick counter value
  * @param  counter : Holds counter value
  * @retval None
  */
void systick_set_counter(uint32_t counter_value)
{

  SYSTICK_ASSERT(IS_SYSTICK_COUNTER_VALUE(counter_value));

  SYSTICK->LOAD = counter_value ;
}

/** @brief  Checks whether the system tick  timer has counted to zero or not
  * @param  None
  * @retval The system tick timer flag status (1 or 0)
  */
uint8_t systick_get_flag_status(void)
{
  uint8_t ret = 0;

  ret =  (SYSTICK->CTRL & SYSTICK_INTERRUPT_FLAG) > 0 ? 1 : 0;

  return ret ;
}

/** @brief  Clears system tick timer has counted zero flag
  * @param  None
  * @retval None
  */
void systick_clear_flag(void)
{
  SYSTICK->CTRL &= ~(SYSTICK_INTERRUPT_FLAG);
}

/** @brief Set system tick  Timer state
  * @param state : Holds system tick timer state
  *        @arg SYSTICK_OFF : disable system tick timer
  *        @arg SYSTICK_ON  : enable system tick timer
  * @retval : None
  */
void systick_set_state(uint32_t  state)
{

  SYSTICK_ASSERT(IS_SYSTICK_STATE(state));

  if(state == SYSTICK_OFF)
    {
      SYSTICK->CTRL&=SYSTICK_OFF;
    }
  else if (state == SYSTICK_ON)
    {
      SYSTICK->CTRL|=SYSTICK_ON;
    }
  else
    {
      /*Should not be here !*/
    }
}

/** @brief Sets system tick timer interrupt
  * @param state : Holds the state of system tick timer interrupt
  *        @arg SYSTICK_INTERRUPT_OFF : Disable system tick timer interrupt
  *        @arg SYSTICK_INTERRUPT_ON : Enable system tick timer interrupt
  * @retval None
  */
void systick_set_interrupt_state(uint32_t state)
{

  SYSTICK_ASSERT(IS_SYSTICK_INTERRUPT_STATE(state));

  if(state == SYSTICK_INTERRUPT_OFF)
    {
      SYSTICK->CTRL &= SYSTICK_INTERRUPT_OFF;
    }
  else if (state == SYSTICK_INTERRUPT_ON)
    {
      SYSTICK->CTRL |= SYSTICK_INTERRUPT_ON ;
    }
  else
    {
      /*Should not be here !*/
    }

}

/** @brief  Gets system tick inerrupt status
  * @param  None
  * @retval The system tick inerrupt status (1 or 0).
  */
uint8_t  systick_get_interrupt_flag(void)
{
  uint8_t ret = 0 ;

  ret = (SYSTICK->CTRL & SYSTICK_INTERRUPT_FLAG) > 0 ? 1 : 0;

  return ret ;
}


/** @brief  Gets system tick timer calibration value
  * @param  None
  * @retval System tick calibration register value
  */
uint32_t systick_get_clibrate_info(void)
{
  uint32_t ret =0  ;

  ret =  SYSTICK->CALIB & ((uint32_t)(0x00FFFFFF));

  return ret ;
}

/** @brief  Reads as one and  indicate the suitability of
 *          system tick as a software real time clock.
  * @param  None
  * @retval One if the system tick timer is stable
  */
uint8_t systick_get_skew_flag (void)
{
  uint8_t ret  = 0;

  ret = (SYSTICK->CALIB & SYSTICK_SNEW_FLAG) > 0 ? 1 : 0;

  return ret ;
}

/** @brief  Indicates that a separate reference clock is provided ,
  *         The frequency of this clock is HCLK/8.
  * @param  None
  * @retval zero if the separate reference clock is provided .
  */
uint8_t systick_get_noref_flag(void)
{
  uint8_t ret = 0;

  ret = (SYSTICK->CALIB & SYSTICK_NOREF_FLAG) > 0 ? 1 : 0;

  return ret ;
}

static void SYSTICK_ASSERT_FAILED(void)
{
  /*Disable interrupts */
  __asm("CPSID I") ;

  /*Stay here for ever !*/
  for(;;);
}
