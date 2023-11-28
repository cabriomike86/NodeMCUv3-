#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ESP8266WiFi.h"
const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm
#include <LCDGraph.h>


// start of settings for LCD1602 with I2C
#define LCD_ADDRESS 0x27
#define LCD_ROWS 2
#define LCD_COLS 16
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
LCDGraph<float, LiquidCrystal_I2C> graph(8, 0); // We want to store floats in this case

int count =0;

int scanDelayTime = 1000;
int wiFiDisplayTime = 3000;

void setup() {
  // Set WiFi to station mode and 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();//disconnect from an AP if it was previously connected
  lcd.init();  
  lcd.begin(16,2);  
  lcd.backlight();
  graph.begin(&lcd);
  lcd.print(F("ESP8266"));
  lcd.setCursor(0,1);
  lcd.print("Wifi Scan");  
  delay(2000); 
}


void loop() {
 // Robojax D1 Mini LCD-1602-I2C  WiFi Scan

// WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  lcd.clear();// clear previous values from screen
  lcd.print("scan done");     
  if (n == 0) {
    lcd.print("No WiFI found");   
  } else {
    lcd.setCursor(0,1);
    lcd.print(n);
    lcd.print( " AP found");
    for (int i = 0; i < n; ++i) {

      // Print SSID and RSSI for each network found
      lcd.clear();// clear previous values from screen
      lcd.setCursor(0,0);
      lcd.print(i+1);      
      lcd.print(") "); 
      lcd.print(WiFi.SSID(i));     
      lcd.setCursor(0,1);        
      lcd.print("Signal: ");      
      lcd.print(dBmtoPercentage(WiFi.RSSI(i))); 
      lcd.print("%"); 
      delay(wiFiDisplayTime);
    }
  }  

  delay(scanDelayTime); 
}// loop end


/*
 * Written by Ahmad Shamshiri
  * with lots of research, this sources was used:
 * https://support.randomsolutions.nl/827069-Best-dBm-Values-for-Wifi 
 * This is approximate percentage calculation of RSSI
 * Wifi Signal Strength Calculation
 * Written Aug 08, 2019 at 21:45 in Ajax, Ontario, Canada
 */

int dBmtoPercentage(int dBm)
{
  int quality;
    if(dBm <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(dBm >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (dBm + 100);
   }

     return quality;
}//dBmtoPercentage
 