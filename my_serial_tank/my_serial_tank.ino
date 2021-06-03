/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};



byte rowPins[ROWS] = {A0,A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(9600);
 
  
}

void loop() 
{
  char customKey;
  char my_char[4];
  int i;
  char in_char = "0";


  lcd.setCursor(0,1);
  lcd.print("SERIAL TANK DEMO");                      


  lcd.setCursor(0,0);
  lcd.print("TURN ON   OUTLET");
    
  Serial.write(0x01);          // SPECIFY  OUTLET VALVE
  Serial.write(0x01);          // TURN ON OUTLET VALVE
    
  delay(3000);

  lcd.setCursor(0,0);
  lcd.print("TURN OFF   OUTLET");
    
  Serial.write(0x01);          // SPECIFY  OUTLET VALVE
  Serial.write(0x01);          // TURN ON OUTLET VALVE
                          
   delay(1000);

   
   while(1);
    
    LCD8_Out(2,1,"TURN ON    INLET");

    Usart_Write(0x00);          // SPECIFY  INLET VALVE
    Usart_Write(0x01);          // TURN ON  INLET VALVE

    delay_ms(10000);

    LCD8_Out(2,1,"TURN OFF   INLET");

    Usart_Write(0x00);          // SPECIFY  INLET VALVE
    Usart_Write(0x00);          // TURN OFF INLET VALVE
    
    LCD8_Out(2,1,"TURN ON   HEATER");

    Usart_Write(0x02);          // SPECIFY  INLET VALVE
    Usart_Write(0x01);          // TURN ON  INLET VALVE

    delay_ms(3000);

    LCD8_Out(2,1,"TURN OFF  HEATER");

    Usart_Write(0x02);          // SPECIFY  INLET VALVE
    Usart_Write(0x00);          // TURN OFF INLET VALVE
    
    LCD8_Out(2,1,"TURN ON   COOLER");

    Usart_Write(0x03);          // SPECIFY  INLET VALVE
    Usart_Write(0x01);          // TURN ON  INLET VALVE

    delay_ms(3000);

    LCD8_Out(2,1,"TURN OFF  COOLER");

    Usart_Write(0x03);          // SPECIFY  INLET VALVE
    Usart_Write(0x00);          // TURN OFF INLET VALVE
    
    LCD8_Out(2,1,"TURN ON  STIRRER");

    Usart_Write(0x04);          // SPECIFY  INLET VALVE
    Usart_Write(0x01);          // TURN ON  INLET VALVE

    delay_ms(3000);

    Lcd8_Out(2,1,"TURN OFF STIRRER");

    Usart_Write(0x04);          // SPECIFY  INLET VALVE
    Usart_Write(0x00);          // TURN OFF INLET VALVE
    
    
    
    Lcd8_Out(2,1,"SEND MAX TEMP AL");

    Usart_Write(0x021);          // SPECIFY   MAX TEMP ALARM
    data = 151;
    Usart_Write((data >> 8) & 0x00FF);      // SEND HIGH BYTE
    Usart_Write( data & 0x00FF );           // SEND LOW BYTE

    delay_ms(3000);

    Lcd8_Out(2,1,"READ MIN TEMP AL");

    Usart_Write(0x31);                // SPECIFY  TANK TEMP

    while (!Usart_Data_Ready()) {}     // wait for data
    highbyte = Usart_Read();          // READ HIGH BYTE
    while (!Usart_Data_Ready()) {}     // wait for data
    lowbyte  = Usart_Read();          // READ LOW BYTE

    data = highbyte;
    data = (data <<8) | lowbyte;

    wordToStr(data, text);
    
    Lcd8_Out(2,1, text);
    Lcd8_Out(2,6, "               ");

    
    while(1);
  
  for (i=0; i<4; i++) {
    my_char[i]= customKeypad.waitForKey();   // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(my_char[i]);
    Serial.println(my_char[i]);
  }
  lcd.setCursor(10,1);
  lcd.print(my_char);
  Serial.println(my_char); 

   do {
    if (Serial.available()){
      in_char = Serial.read();
      delay(10);
      lcd.print(in_char);
      Serial.println(in_char);
    }  
  } while(in_char != 'X'); 


//comeafsdfasdfasdfas
}
