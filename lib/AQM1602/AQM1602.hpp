#ifndef LCD_HEADER
#define LCD_HEADER

#include <string>
#include <Arduino.h>
#include <Wire.h>
#include <stdarg.h>

namespace lcd {
	void write_char(byte t_data);
	void write_command(byte t_command);
	void write_string(std::string stringData);
	void init();
	void clear_display();
	void linebreak();
	void return_home_cursor();
}

#endif