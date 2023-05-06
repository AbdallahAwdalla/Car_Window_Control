/**
 ********************************************************************************
 * @file    main
 * @author  Abdallah and 7oda 
 * @date    
 * @brief    Here is where the main function live :) 
 ********************************************************************************
*/
/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
/// \brief Priorities at which the tasks are created
#define TASK_01_PRIORITY		( tskIDLE_PRIORITY + 2 )


/********************************************************************************
 * PRIVATE TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * STATIC VARIABLES
 ********************************************************************************/
static uint8_t myFlag;
/********************************************************************************
 * GLOBAL VARIABLES
 ********************************************************************************/




/********************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ********************************************************************************/

static void Task01( void *pvParameters );
static void MyBlinkyLED_Init( void );

/********************************************************************************
 * FUNCTION NAME:       main
 * \param  [in]         void
 * \param  [out]        int
 * 
 * 
********************************************************************************/
int main( void )
{
    MyBlinkyLED_Init();

    /* Start the two tasks as described in the comments at the top of this file. */
    xTaskCreate( Task01,			        /* The function that implements the task. */
                 "Task01", 					/* The text name assigned to the task - for debug only as it is not used by the kernel. */
                 configMINIMAL_STACK_SIZE, 	/* The size of the stack to allocate to the task. */
                 NULL, 						/* The parameter passed to the task - not used in this simple case. */
                 TASK_01_PRIORITY,          /* The priority assigned to the task. */
                 NULL );					/* The task handle is not required, so NULL is passed. */


    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
    line will never be reached.  If the following line does execute, then
    there was insufficient FreeRTOS heap memory available for the idle and/or
    timer tasks	to be created.  See the memory management section on the
    FreeRTOS web site for more details. */
    for( ;; );
}

/********************************************************************************
 * FUNCTION NAME:       Task01
 * \param  [in]         void *pvParameters
 * \param  [out]        void 
 * 
 * 
********************************************************************************/
static void Task01( void *pvParameters )
{
	uint32_t ulReceivedValue;

	/* Prevent the compiler warning about the unused parameter. */
	( void ) pvParameters;

	for( ;; )
	{
        if (0U ==  myFlag)
        {
            /* Turn on the LED.*/
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }
        else
        {
            /* Turn on the LED.*/
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0u);
        }
        myFlag = (myFlag + 1U) % 2U;
        
		vTaskDelay(1000);
	}
}


/********************************************************************************
 * FUNCTION NAME:       MyBlinkyLED_Init
 * \param  [in]         void *pvParameters
 * \param  [out]        void 
 * 
 * 
********************************************************************************/
static void MyBlinkyLED_Init( void )
{
    
    /* Enable the GPIO port that is used for the on-board LED. */  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* Check if the peripheral access is enabled. */ 
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    /* Enable the GPIO pin for the LED (PF3).  Set the direction as output, and */
    /* enable the GPIO pin for digital function. */
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

}
