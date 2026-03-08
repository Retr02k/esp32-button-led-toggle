#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// GPIO pin definitions
#define	BUTTON_PIN 4
#define	LED_PIN 5

// Anti-bounce delay in milliseconds
#define	DEBOUNCE_DELAY_MS 50

/**
 * @brief Detects button press with edge detection
 * @param state Current button state (1 = pressed, 0 = released)
 * @return 1 if button was just pressed, 0 otherwise
 * 
 * This function implements edge detection to trigger only on
 * the rising edge (button press) and prevent multiple triggers
 * while the button is held down.
 */
int button_pressed(int state){
	static int last_state = 0;
	int ret = 0;

	// Detect rising edge(button just pressed)
	if (!last_state && state){
		ret = 1;
	}
	
	last_state = state;
	return ret;
}

/**
 * @brief Toggles the LED state between ON and OFF
 * 
 * Uses a static variable to maintain LED state across function calls.
 * Each call will flip the current state.
 */
void toggle_led(){
	static int led_state = 0;

	// Toggle state
	led_state = !led_state;

	// Apply to GPIO
	gpio_set_level(LED_PIN, led_state);
}

/**
 * @brief Main application entry point
 * 
 * Configures GPIO pins for LED output and button input with pull-down,
 * then enters an infinite loop monitoring button state and toggling LED.
 */
void	app_main(void) {

	printf("ESP32 Starting...\n");

	// Configure LED pin as output
	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

	// Configure button pin as input with pull-down resistor
	gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLDOWN_ONLY);

	printf("GPIO configured. Press button on GPIO %d to light up LED on GPIO %d\n", BUTTON_PIN, LED_PIN);

	// Main loop
	while(1){
		// Read button state
		int	button_state = gpio_get_level(BUTTON_PIN);

		// Check for button press event
		if (button_pressed(button_state)){
			toggle_led();
			printf("Button pressed! LED toggled.\n");
		}

		// Small delayfor debouncing and to preserve cpu hogging
		vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_DELAY_MS));
	}
}