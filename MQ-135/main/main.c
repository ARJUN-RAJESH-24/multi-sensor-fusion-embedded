#include <Arduino.h>

#define MQ135_PIN 34
#define ADC_MAX   4095.0
#define VREF      3.3

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);
}

void loop() {
    int adcValue = analogRead(MQ135_PIN);
    double voltage = (adcValue / ADC_MAX) * VREF;

    Serial.print("MQ135_ADC=");
    Serial.print(adcValue);
    Serial.print(" MQ135_V=");
    Serial.println(voltage, 3);

    delay(2000);
}
