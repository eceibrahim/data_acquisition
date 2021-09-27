#ifndef __SERIAL_H__ 
#define __SERIAL_H__

#include "Main.h"

#define SERIAL_TRANSFER_TASK_PERIOD_MS          (20)
#define SERIAL_RECEIVE_TASK_PERIOD_MS           (20)  

#define SERIAL_NO_CHAR                          (0x12)

#define SERIAL_TIMEOUT_FAULT                    (1)
#define SERIAL_BUFFER_OUT_OF_SIZE_FAULT         (2)

void serial_init(void);
void serial_send(void); 
void serial_receive(void);
void serial_send_data(uint8_t * string);
uint8_t serial_get_data(void);

#endif /*__SERIAL_H__*/
