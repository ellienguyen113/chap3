/*Name: Ellie
Date: January 19, 2026

Description: 
Each time the button is pressed and released, the LED switches to the opposite state.
The first button press turns the LED ON, the second press turns it OFF, 
and this ON/OFF pattern continues for every press*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_10
#define BUTTON_PIN GPIO_NUM_4
#define BUTTON_PIN2 GPIO_NUM_5      

#define loop_delay 10 
void app_main(void){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_dis(LED_PIN);
    gpio_pulldown_dis(LED_PIN);
 
    gpio_reset_pin(BUTTON_PIN2);
    gpio_set_direction(BUTTON_PIN2, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN2);
    gpio_pulldown_dis(BUTTON_PIN2);

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_level(BUTTON_PIN,0);
    gpio_pullup_en(BUTTON_PIN);
    gpio_pulldown_dis(BUTTON_PIN);

    bool prev_button1 = true;   // released = 1
    bool curr_button1;
    bool curr_button2;
    bool led_state = false;

    while (1){
        curr_button1 = gpio_get_level(BUTTON_PIN);
        curr_button2 = gpio_get_level(BUTTON_PIN2);

        // Detect falling edge on BUTTON_PIN
        // AND check if BUTTON_PIN2 is pressed (enable)
        if ((curr_button1 == 0) && (prev_button1 == 1) && (curr_button2 == 0))
        {
            led_state = !led_state;
            gpio_set_level(LED_PIN, led_state);
        }
        prev_button1 = curr_button1;
        vTaskDelay(25 / portTICK_PERIOD_MS);
    }

}
