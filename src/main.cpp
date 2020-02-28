// SPDX-License-Identifier: Apache-2.0 OR MPL-2.0

#include <string>
#include <Arduino.h>
#include <RTClib.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#define LEDC_CHANNEL 0
#define LED_PIN 16
#define BUTTON_PIN 17
#define freq 5000
#define resolution 8
uint8_t alerm_hour = 17;
uint8_t alerm_minute = 2;

RTC_DS1307 rtc;
xSemaphoreHandle xLEDContolMutex;

void turnOff(int* arg);
void bright(int* arg);
void vBrightTask(void* arg);

void setup() {
	Serial.begin(115200);

	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}
	if (! rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	ledcSetup(LEDC_CHANNEL, 12800, resolution);
	ledcAttachPin(LED_PIN, LEDC_CHANNEL);
	pinMode(BUTTON_PIN, INPUT);

	xLEDContolMutex = xSemaphoreCreateMutex();
	if(xLEDContolMutex != NULL) {
		xTaskCreatePinnedToCore(vBrightTask, "Task0", 4096, NULL, 1, NULL, 1);
	}
}

void loop() {}

void vBrightTask(void* arg) {
	BaseType_t xStatus;
	const TickType_t xTicksToWait = 1000UL;
	int LEDStatus = 0;
	while (true) {
		DateTime now = rtc.now();
		if (digitalRead(17) == HIGH) {
			turnOff(&LEDStatus);
		} else {
			if (now.hour() == alerm_hour && now.minute() == alerm_minute){
				bright(&LEDStatus);
				LEDStatus++;
			}
		}
	}
}

void turnOff(int* arg) {
	for (int i = *arg; i >= 0; i--){	
		ledcWrite(LEDC_CHANNEL, i);
		delay(100);
	}
	*arg = 0;
}

void bright(int *arg) {
	ledcWrite(LEDC_CHANNEL, *arg);
	if (*arg < 100) {
		delay(100);
	} else {
		delay(5000);
	}
}