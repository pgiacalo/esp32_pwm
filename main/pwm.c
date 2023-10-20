#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/ledc.h"
#include "hal/ledc_types.h"
#include "esp_log.h"


#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (18)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0

void setup_led(uint32_t freq_hz){
    // Prepare and set configuration of timers that will be used by LED Controller
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_1_BIT, // resolution of PWM duty
        .freq_hz = freq_hz,                 // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,          // timer mode
        .timer_num = LEDC_HS_TIMER           // timer index
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);

    // Prepare individual configuration for each channel of LED Controller by selecting:
    // - controller's channel number
    // - output duty cycle, set initially to 50%
    // - GPIO number where output signal is connected to
    // - speed mode, either high or low
    // - timer servicing selected channel
    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_HS_CH0_CHANNEL,
        .duty       = 1,                     // 50% duty cycle
        .gpio_num   = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_HS_TIMER
    };
    // Set the configuration
    ledc_channel_config(&ledc_channel);

}


void app_main(void)
{
    ESP_LOGI("app_main", "app_main() starting...");
    uint32_t freq_hz = 10000000;
    ESP_LOGI("app_main", "frequency=%lu", freq_hz);
    setup_led(freq_hz);
    while(1){
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }    
}

