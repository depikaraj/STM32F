
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED


/*----------------------------------------------------------------------------
 *      Thread 2 : LED thread
 *---------------------------------------------------------------------------*/
 
void thread2 (void const *argument);                 // thread function
osThreadId tid_thread2;                              // thread id
osThreadDef(thread2, osPriorityNormal, 1, 0);        // thread object

int Init_thread2(void) {

  tid_thread2 = osThreadCreate(osThread(thread2), NULL);
  if (!tid_thread2) return(-1);
  
  return(0);
}

void thread2 (void const *argument) {
  
  uint32_t led_num = 1;
  extern osSemaphoreId semaphore;
	
  while (1) {
    osSignalWait(1U, osWaitForever);    // Wait for signal
		
		osSemaphoreWait (semaphore, osWaitForever);//wait for sem
		//got semaphore
		
		/*critical section*/
		
    LED_On(led_num);                    // Turn specified LED on
    osDelay(3000);
    LED_Off(led_num);                   // Turn specified LED off
		
		/*critical section*/
		
    osSemaphoreRelease (semaphore);			//release semaphore
   
  }
}
