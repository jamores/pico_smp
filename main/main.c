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

/* PRIVATE FUNCTIONS : implementation */
static void prvSetupHardware(void){
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN,GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
}
static void prvTask_C0(void *pvParameters){
    
    while(1){
        printf("Task C0 on %d\n", get_core_num());
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        vTaskDelay(TASK_DELAY_C0_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(TASK_DELAY_C0_MS);
    }
}
static void prvTask_C1(void *pvParameters){
    while(1){
        printf("Task C1 on %d\n", get_core_num());
        vTaskDelay(TASK_DELAY_C1_MS);
    }
}