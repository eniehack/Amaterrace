#include "AQM1602.hpp"
#define LCD_ADDRESS 0x3E
#define BUFFER 16

void lcd::write_command(byte t_command) {
	Wire.beginTransmission(LCD_ADDRESS);
	Wire.write(0x00);
	Wire.write(t_command);
	Wire.endTransmission();
	delay(10);
}

void lcd::clear_display() {
	lcd::write_command(0x01);
	delay(2);
}

void lcd::return_home_cursor() {
	lcd::write_command(0x02);
	delay(2);
}

void lcd::linebreak() {
	lcd::write_command(0xC0);
}

void lcd::write_char(byte t_data) {
	Wire.beginTransmission(LCD_ADDRESS);
	Wire.write(0x40);
	Wire.write(t_data);
	Wire.endTransmission();
	delay(1);
}

void lcd::write_string(std::string stringData) {
	Serial.println("writeStringToLCD");
	for (int i = 0; i < stringData.size(); i++) {
		lcd::write_char(stringData.at(i));
	}
}

void lcd::init() {
	Serial.println("initLCD");
	delay(100);
	lcd::write_command(0x38);
	delay(20);
	lcd::write_command(0x39);
	delay(20);
	lcd::write_command(0x14);
	delay(20);
	lcd::write_command(0x73);
	delay(20);
	lcd::write_command(0x56);
	delay(20);
	lcd::write_command(0x6C);
	delay(20);
	lcd::write_command(0x38);
	delay(20);
	lcd::write_command(0x01);
	delay(20);
	lcd::write_command(0x0C);
	delay(20);
	lcd::write_command(0x06);
	delay(20);

	Serial.println("finished init");
}