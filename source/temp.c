#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "peripherals.h"

#define DEMO_ADC_BASE ADC0_BASE
#define DEMO_ADC_CHANNEL_GROUP 0U // For ADCs with channel groups (like Kinetis)
#define DEMO_ADC_CHANNEL      ADC0_TEMP  // The actual analog channel number (e.g., AD0_0)
                                  // You'll need to look up which physical pin maps to which ADC channel
                                  // in your MCU's datasheet or MCUXpresso's Pins tool.

uint32_t get_adc_reading(void) {
	return ADC16_GetChannelConversionValue(DEMO_ADC_BASE, DEMO_ADC_CHANNEL_GROUP);
}

int get_temp_state(void) {
	int raw_adc_value = get_adc_reading();

	float voltage = (float) raw_adc_value * (3.3f / 4096.0f); // 4096.0f for 12-bit resolution (2^12)
	float temperatureC = (voltage - 0.5f) * 100.0f;
	float temperatureF = (temperatureC * 9.0f / 5.0f) + 32.0f;

	PRINTF("Raw ADC: %d\tVoltage: %.3f V\tTemp: %.2f C | %.2f F\r\n", raw_adc_value, voltage,
			temperatureC, temperatureF);

	return 0;
}
