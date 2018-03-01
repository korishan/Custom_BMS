#include <Wire.h>
#include "Arduino.h"

#include "declares.h"
#include "constants.h"

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI


void oled_loop()
{
  // picture loop
  oled.firstPage();  
  do {
    draw();
  } while( oled.nextPage() );
  
  // rebuild the picture after some delay
  delay(1000);
}

void draw(void)
{
  // graphic commands to redraw the complete screen should be placed here
  oled.setFont(u8g_font_unifont);
  oled.drawStr( 0, 20, "Hello World!");
}

