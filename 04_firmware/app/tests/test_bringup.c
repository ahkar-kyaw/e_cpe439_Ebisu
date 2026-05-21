#include "test_bringup.h"

#include "cmsis_os2.h"
#include "main.h"

static osThreadId_t test_bringup_task_handle;

static const osThreadAttr_t test_bringup_task_attributes = {
    .name = "test_bringup",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
};

static void test_bringup_task(void *argument)
{
    (void)argument;

    for (;;)
    {
        HAL_GPIO_TogglePin(led_status_GPIO_Port, led_status_Pin);
        osDelay(500);
    }
}

void test_bringup_start(void)
{
    test_bringup_task_handle = osThreadNew(
        test_bringup_task,
        NULL,
        &test_bringup_task_attributes
    );

    if (test_bringup_task_handle == NULL)
    {
        Error_Handler();
    }
}