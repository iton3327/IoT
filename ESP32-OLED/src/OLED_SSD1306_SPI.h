//////////////////////////////////////////////////////////////////////////
// Author: RSP @ Embedded System Lab (ESL), KMUTNB, Thailand
// File: OLED_SSD1306_SPI.h
// Last Modified: 2014-07-13
// Note:
//   This is a C++ class that can be used to interface
//   the Arduino board with the SSD1306-based 128x64 OLED SPI display module.
//////////////////////////////////////////////////////////////////////////

#ifndef __OLED_SSD1306_SPI_H
#define __OLED_SSD1306_SPI_H

#include "Arduino.h"
#include <SPI.h>

namespace esl {
  class OLED_SSD1306_SPI {
    public:
       OLED_SSD1306_SPI( uint8_t dc, uint8_t cs, uint8_t rst, 
                         uint8_t sck, uint8_t mosi ); // use soft-SPI
       OLED_SSD1306_SPI( uint8_t dc, uint8_t cs, uint8_t rst ); // use hardware-SPI
       ~OLED_SSD1306_SPI();
       void init();
       void update();
       void clearBuffer();
       void clearDisplay();
       void displayOnOff( boolean onOff );
       void inverseDisplay( boolean inverse );
       void writeByteToBuffer( uint8_t x, uint8_t y, uint8_t data );
       void drawPixel( uint8_t x, uint8_t y, boolean onOff );
       void drawText( uint8_t x, uint8_t y, const char *text );
       void drawRect( uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 );
       void useBoldFont();
       void useNormalFont();

       static const uint16_t LCD_WIDTH  = 128;
       static const uint16_t LCD_HEIGHT = 64;
       static const uint16_t BUFFER_SIZE = (LCD_WIDTH * LCD_HEIGHT) / 8; // display buffer size

    private:
       uint8_t font_width;
       prog_uchar *font;
       uint8_t *buffer; // display buffer
       boolean use_hw_spi;
       uint8_t dc_pin, rst_pin, cs_pin, sck_pin, mosi_pin;
       void send_cmd( uint8_t );
  };
}

#endif // __OLED_SSD1306_SPI_H

//////////////////////////////////////////////////////////////////////////
