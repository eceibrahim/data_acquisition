# data_acquisition
This is "data acquisition "application with the ability of error handling :

# Software Tools : 

1-Keil uVersion5 "IDE"

# Hardware :
1-Stm32f103c8  "blue pill board"

2-Usb to ttl serial converter 

# System description :
1- PC keyboard  is a system input .

2- One interrupt system .

3- For all minor cycles , sum(WCET of tasks) < system tick .

4- output of the system will be :

"Menu : 

O - Open the led . 

C - Close the led . 

? : " 

Here the user should enter 'O' or 'o' to open the led , 'C' or 'c' to close the led and after entering the character . the application

will send to the user the status of the led .

if the user enter 'o' or 'O' , led will be opened  and "Led is opened ." massage will be sent to PC .

if the user enter 'c' or 'C' , led will be  closed  and "Led is closed ." massage will be sent to PC .

# Errors :
1- Out of buffer size error .

2- Time out error .

# Recovery action :
1- Turn on/off led with rate 1/100  HZ . 

# Peripherals :

1- USART2 

2- RCC 

3- GPIO
