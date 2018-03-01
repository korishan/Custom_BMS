#include <Wire.h>

#include "declares.h"
#include "constants.h"

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here
  oled.setFont(u8g_font_unifont);
  oled.drawStr( 0, 20, "Hello World!");
}

