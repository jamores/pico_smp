/* 
    Minimal example to use FreeRTOS SMP with task affinity enabled.

    Create TWO very simple tasks and run each on PICOs Cores:
    - C0 : print message to console and blink an LED
    - C1 : print message to console

    note : use minicom to observe console messages
    $ minicom -b 115200 -o -D /dev/ttyACM0

*/

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"

/* DEFINES */
#define TASK_DELAY_C0_MS    500
#define TASK_DELAY_C1_MS    500
#define DEBUG_AFFINITY      1

/* PRIVATE FUNCTIONS :  headers */
static void prvSetupHardware(void);
static void prvTask_C0(void *pvParameters);
static void prvTask_C1(void *pvParameters);

/**/
/* PUBLIC FUNCTIONS */
/**/

/* FreeRTOS callbacks */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

void vApplicationMallocFailedHook(void){
    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName){
    (void)pxTask;
    (void)pcTaskName;
    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}


/** Creates tasks and allocates to a particular PICO core : C0,C1 */
int main(){
    TaskHandle_t xHandle[2];
    
    prvSetupHardware();

    /* Create Tasks */
    xTaskCreate( prvTask_C0, "C0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1 , &(xHandle[0]) );
    xTaskCreate( prvTask_C1, "C1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1 , &(xHandle[1]) );

#if DEBUG_AFFINITY == 1
    vTaskCoreAffinitySet(xHandle[0],(UBaseType_t)(1<<0));
    vTaskCoreAffinitySet(xHandle[1],(UBaseType_t)(1<<1));
#endif

    /* start scheduler */
    printf("starting scheduler on Core : %d",get_core_num());
    vTaskStartScheduler();

}

/**/
/* PRIVATE FUNCTIONS : implementation */
/**/

/** Initialize PICO's required HW */
static void prvSetupHardware(void){
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN,GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
}

/** run something on C0 : print to console and blink an Led */
static void prvTask_C0(void *pvParameters){
    
    while(1){
        printf("Task C0 on %d\n", get_core_num());
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        vTaskDelay(TASK_DELAY_C0_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(TASK_DELAY_C0_MS);
    }
}
/** run something on C1 : print to console */
static void prvTask_C1(void *pvParameters){
    while(1){
        printf("Task C1 on %d\n", get_core_num());
        vTaskDelay(TASK_DELAY_C1_MS);
    }
}