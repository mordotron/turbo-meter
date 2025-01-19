#include "SPI.h"
#include "TFT_eSPI.h"


TFT_eSPI tft = TFT_eSPI();

#define xcenter 160
#define ycenter 160
#define fullangle 270
#define radius 160
#define width_ring 50
#define backangle 90
#define incr  6
#define seg_count 48


uint8_t angle ;
float pressure ;

uint16_t color ;
long unsigned int frame_time ;

uint16_t in_x [seg_count];
uint16_t in_y [seg_count];

uint16_t mid_x [seg_count];
uint16_t mid_y [seg_count];

uint16_t out_x [seg_count];
uint16_t out_y [seg_count];


uint16_t rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

void setup() {

  tft.init();
  tft.fillScreen(TFT_BLACK);
    
    for (uint16_t i = 0; i <= 46; i++ ) {

    float sx = -sin(i*6*0.0174532925);
    float sy = cos(i*6*0.0174532925);
   

    
    in_x[i] = sx * (radius - width_ring ) + xcenter ;
   // DUMP(in_x[i]);
    in_y[i] = sy * (radius - width_ring ) + ycenter ;
    //DUMP(in_y[i]);

    // mid_x  [i] = sx * (radius - width_ring ) / 2  + xcenter;
    // mid_y  [i] = sy * (radius - width_ring ) / 2  + ycenter;
   
    out_x[i] = sx * radius + xcenter ;
    //DUMP(out_x[i]);
    out_y[i] = sy * radius + ycenter ;
    //DUMP(out_y[i]);
   // DUMP(in_x[0]);
   

        }

    //angle = 0 ;
   
    
    }


void loop() {



  angle = map(analogRead(34), 0, 4095, 0, 45) ;

      for (uint8_t i = 15 ; i <= 45; i++ ) 
      {
      if (i < angle ) 
      color = rainbow (map(angle, 15, 45, 70, 127));
      else color = 0 ;
      
          tft.fillTriangle(in_x[i],    in_y[i],    out_x[i], out_y[i], in_x[i+1],  in_y[i+1],  color);         
          tft.fillTriangle(in_x[i+1],  in_y[i+1],  out_x[i], out_y[i], out_x[i+1], out_y[i+1], color);
      }

      for (uint8_t i = 15 ; i > 0; i-- ) 
      {
      if (i > angle ) 
      color = rainbow (map(angle, 15, 0, 35, 0));
      else color = 0 ;
          
          
          tft.fillTriangle(in_x[i],    in_y[i],    out_x[i], out_y[i], in_x[i-1],  in_y[i-1],  color);         
          tft.fillTriangle(in_x[i-1],  in_y[i-1],  out_x[i], out_y[i], out_x[i-1], out_y[i-1], color);
      }







  tft.fillRect (50, 350, 50, 30, TFT_BLACK );
  tft.setCursor(50, 350);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  pressure = ( angle - 15 ) / 15.0 ;
  tft.println( pressure );
}
