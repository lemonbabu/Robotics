#include "U8glib.h"

char ADCval[5];
int adcval;
U8GLIB_SSD1306_128X64 lcd(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  

void draw(void) 
{
  lcd.setFont(u8g_font_osb18);
  lcd.drawStr( 0, 22, "DUET");
  lcd.setFont(u8g_font_unifont);
  lcd.drawStr( 71, 22, ADCval);
  lcd.drawHLine (2,30,100);
  lcd.drawBox (2,40,20,15);
  lcd.drawCircle(40,50,10);
  lcd.drawFrame(70,40,20,15);
  lcd.drawTriangle(100,40,125,40,110,60);
}

void setup(void) 
{
  //lcd.setRot180();   // flip screen, if required
  lcd.setColorIndex(1); // 1 for monochrome
}

void loop(void) 
{
  adcval=analogRead(A1);
  itoa(adcval, ADCval, 10);
  lcd.firstPage(); 
  do {draw();} while( lcd.nextPage() );
  delay(50);
}


