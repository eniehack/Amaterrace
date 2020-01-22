#include <Arduino.h>
#include <RTClib.h>
#include <string>
#include <inttypes.h>
#include "../lib/AQM1602/AQM1602.hpp"
#define LEDC_CHANNEL 0
#define LED 16
#define freq 5000
#define resolution 8
const uint8_t alerm_hour = 18;
const uint8_t alerm_minutes = 5;

RTC_DS1307 rtc;

void display_time(DateTime);

void setup() {
	while (!Serial);
	Serial.begin(115200);

	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}

	if (! rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
	} else {
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	lcd::init();
}

void loop() {
	DateTime now = rtc.now();
    if (now.minute() == alerm_minutes && now.hour() == alerm_hour) {
		for (int i = 0; i < 255; i++){
			if (i < 100) {
				Serial.println(i, DEC);
				ledcWrite(LEDC_CHANNEL, i);
				delay(5000);
			} else {
				Serial.println(i, DEC);
				ledcWrite(LEDC_CHANNEL, i);
				delay(100);
			}
			display_time(now);
		}
		ledcWrite(LEDC_CHANNEL, 0);
	} else {
		display_time(now);
		delay(1000);
	}
}

void display_time(DateTime now) {
	char l1[9], l2[9];
	sprintf(l1, "%u/%u/%u", now.year(), now.month(), now.day()); 
	sprintf(l2, "%u:%u:%u", now.hour(), now.minute(), now.second());
	std::string str1(l1, 9);
	std::string str2(l2, 9);
	lcd::clear_display();
	lcd::return_home_cursor();
	lcd::write_string(str1);
	lcd::linebreak();
	lcd::write_string(str2);
}