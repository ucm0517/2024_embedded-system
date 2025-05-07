/* FreeRTOS includes. */
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//#include "cmsis_os2.h"

/* The task functions prototype*/
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void UARTx_Init(void);
SemaphoreHandle_t mtx;
QueueHandle_t queue;

void LED_GPIO_Init(void) 
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
   /*Configure GPIO pins : PB8 PB9 PB10 PB11*/
   GPIO_InitStructure.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main( void )
{
	/* essential Board initializations */
	SystemInit();
	HAL_Init();	UARTx_Init();	LED_GPIO_Init();

	/* This function initializes the MCU clock, PLL will be used to generate Main MCU clock */
  SystemCoreClockUpdate();
	
	/* Initialize the serial I/O(console ), This function configures Due's CONSOLE_UART */
	printf("FreeRTOS running on STM32F405 Board\n");

	mtx = xSemaphoreCreateMutex();
	queue = xQueueCreate(10, sizeof(unsigned char));
	
	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 240, NULL, 1, NULL );
	
	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running";
unsigned char ch = 'A';

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		
		xSemaphoreTake(mtx, portMAX_DELAY);
		// The critical section begins
		
		if(!xQueueSend(queue, &ch, 200)) {
			printf("\t\t\t-error in sending msg\r\n");
		}
		else {
			printf("%s:SEND-%c\r\n", pcTaskName, ch);
			if( (++ch) > 'Z' ) ch = 'A';
		}

		// The critical section ends

		xSemaphoreGive(mtx);

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
		vTaskDelay(200);						//osDelay(200);
	}
} 
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running";
unsigned char ch_in;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		xSemaphoreTake(mtx, portMAX_DELAY);
		// The critical section begins
		
		if(!xQueueReceive(queue, &ch_in, 300)) {
			printf("\t\t\terror in receiving msg\r\n");
		}
		else {
			printf("\t%s:RECEIVE-%c\r\n", pcTaskName, ch_in);
		}
		
		// The critical section ends

		xSemaphoreGive(mtx);
		
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
		vTaskDelay(300);						//osDelay(300);
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName )
//void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}
