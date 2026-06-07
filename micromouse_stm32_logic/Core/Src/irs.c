/*
 * irs.c
 */

#include "main.h"
#include "irs.h"
#include "delay.h"

// This is the buffer that will get filled up with all the measurements
uint16_t adc_buf[NUM_SAMPLES];
// "boolean" variable to keep say when the ADC has finished filling up the buffer
uint8_t complete = 0;

/*
 This function should handle everything for reading a specific IR
 First turn on the correct IR emitter
 Wait for a small amount of time (at least 20 us) so the photodiode can react
 Then read the correct receiver
 Lastly turn off the emitter
 */
uint16_t readIR(IR ir)
{
	GPIO_TypeDef* PORT;
	uint16_t PIN;
    switch(ir)
    {
        case IR_LEFT:
            PORT = Left_Emitter_GPIO_Port;
            PIN = Left_Emitter_Pin;
            break;

        case IR_FRONT_LEFT:
        	PORT = Front_Left_Emitter_GPIO_Port;
        	PIN = Front_Left_Emitter_Pin;
            break;

        case IR_FRONT_RIGHT:
        	PORT = Front_Right_Emitter_GPIO_Port;
        	PIN = Front_Right_Emitter_Pin;
            break;

        case IR_RIGHT:
        	PORT = Right_Emitter_GPIO_Port;
        	PIN = Right_Emitter_Pin;
            break;

        default:
            return 0;
    }
    HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_SET);
	delayMicroseconds(20);
	uint16_t res = analogRead(ir);
	HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_RESET);
	return res;
}

/*
 Implement the following 4 functions to read each IR
 Hint: Each function may just be one line
 */
uint16_t readLeftIR(void)
{
	return readIR(IR_LEFT);
}

uint16_t readFrontLeftIR(void)
{
	return readIR(IR_FRONT_LEFT);
}

uint16_t readFrontRightIR(void)
{
	return readIR(IR_FRONT_RIGHT);
}


uint16_t readRightIR(void)
{
	return readIR(IR_RIGHT);
}

/*
 This function reads the specific channel of the ADC corresponding to the correct IR
 You should not have to edit this function
 */
uint16_t analogRead(IR ir)
{
    ADC_ChannelConfTypeDef sConfig = {0}; //this initializes the IR ADC [Analog to Digital Converter]
    ADC_HandleTypeDef *hadc1_ptr = Get_HADC1_Ptr(); //this is a pointer to your hal_adc
    //this pointer will also be used to read the analog value, val = HAL_ADC_GetValue(hadc1_ptr);

    //this picks the IR direction to choose the right ADC.
    switch(ir)
    {
        case IR_LEFT:
            sConfig.Channel = ADC_CHANNEL_13;
            break;
        case IR_FRONT_LEFT:
            sConfig.Channel = ADC_CHANNEL_12;
            break;
        case IR_FRONT_RIGHT:
            sConfig.Channel = ADC_CHANNEL_11;
            break;
        case IR_RIGHT:
            sConfig.Channel = ADC_CHANNEL_10;
            break;
        default:
            return 0;
    }

    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    // make sure everything was set up correctly
    if (HAL_ADC_ConfigChannel(hadc1_ptr, &sConfig) != HAL_OK)
    {
        return 0;
    }
    
    complete = 0;

    // start filling up the ADC buffer
    HAL_ADC_Start_DMA(hadc1_ptr, (uint32_t*)adc_buf, NUM_SAMPLES);

    // wait for the buffer to become full
    while (complete == 0)
    {
        continue;
    }

    uint32_t sum = 0;
    // calculate the sum of the measurements in order to calculate the average
    uint16_t measurement = 0;
    while(measurement < NUM_SAMPLES) //this takes multiple measurements
    {
        sum += adc_buf[measurement];
        ++measurement;
    }

    return sum/NUM_SAMPLES;
}

/*
 This function is called when the ADC buffer is filled
 It stops the ADC and changes our "complete" variable to be "true"
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    // stop the ADC
    HAL_ADC_Stop_DMA(hadc);
    complete = 1;
}
