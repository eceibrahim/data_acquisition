#ifndef __PORT_H__
#define __PORT_H__

#define MODULE_LED       (1)
#define MODULE_REPORTER  (1)

#if MODULE_LED 
#define LED_PORT                               GPIOA
#define LED_PIN                                GPIO_Pin_4
#endif /*MODULE_LED*/

#if MODULE_REPORTER                 
#define REPORTER_BUFFER_OUT_OF_SIZE_PORT       GPIOA
#define REPORTER_BUFFER_OUT_OF_SIZE_PIN        GPIO_Pin_5
#define REPORTER_TIME_OUT_PORT                 GPIOA
#define REPORTER_TIME_OUT_PIN                  GPIO_Pin_6
#endif /*__REPORTER_H__*/

#endif /*__PORT_H__*/
