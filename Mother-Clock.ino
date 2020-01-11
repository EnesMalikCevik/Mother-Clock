#include <DS3231.h>
#include <dht.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//LCD module
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
//Temp module
dht DHT;
//Time module
DS3231  rtc(SDA, SCL);

Time t;
#define DHT11_PIN 7
// led lights that indicate weather
int led_cold  = 8;
int led_hot  = 10;
int led_warm=11;
// alarm buzzers
int buzzer1= 3;
int buzzer2= 2;

int Hour;
int Min;
int Sec;



void setup() 
{
  
 
  
  rtc.setTime(13, 54, 0);
  pinMode(led_cold,OUTPUT);
  pinMode(led_hot,OUTPUT);
  pinMode(led_warm,OUTPUT);
  rtc.begin();
  //rtc.setTime(16, 51, 0);
  //pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  //printing opening writing
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome");
  delay(3000);
  
}
 
void loop()
{
 
  int chk = DHT.read11(DHT11_PIN);
  // Storing the temperature in the temp integer
  int temp=DHT.temperature;
  Serial.print("Temperature = ");
  Serial.println(temp);
  lcd.clear();
  //printing temp
  lcd.setCursor(9,0);
  lcd.print("T: ");
  lcd.print(temp );
  
  lcd.setCursor(14,0);
  lcd.print((char)223);
  lcd.print("C");
  
  // printing time
  t = rtc.getTime();
  Serial.println(rtc.getTimeStr());
  lcd.setCursor(0,0);
  lcd.print(rtc.getTimeStr());

  //declaring variables for setting up alarms
  Hour = t.hour;

  Min = t.min;

  Sec = t.sec;

  

  //conditions for different sets of clothing
  if(temp <= 20){
    digitalWrite(led_cold,HIGH);
    digitalWrite(led_hot,LOW);
    digitalWrite(led_warm,LOW);
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("UzunK-Esof-Cor-");
    //UzunK: Uzun kollu tisort (sweatshirt), Esof: Esofman (sweatsuit), Cor: Corap (socks)
    delay(1500);
   
    
    }
  
  else if(DHT.temperature > 20 && DHT.temperature<=27){
    digitalWrite(led_cold,LOW);
    digitalWrite(led_hot,LOW);
    digitalWrite(led_warm,HIGH);
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("TShirt-Esofman"); 
    delay(1500);
  }
  else{
    digitalWrite(led_hot,HIGH);
    digitalWrite(led_cold,LOW);
    digitalWrite(led_warm,LOW);
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("TShirt-Sort"); 
  // Sort: -Shorts-
    delay(1500);
    }
  
  // alarm times
  if( Hour == 11 &&  Min == 30){

    Alarm1();

    Alarm1();

    lcd.clear();

    lcd.print("Alarm 1 ON");

    Alarm1();

    Alarm1();

} 


  if( Hour == 14 &&  Min == 30){

    Alarm2();

    Alarm2();

    lcd.clear();

    lcd.print("Alarm 2 ON");

    Alarm2();

    Alarm2();

} 
 
 
  

 
  
  
 
 }


// alarm functions
void Alarm1()

{

  tone(buzzer1, 400);
  delay(500);

  noTone(buzzer1);
  delay(500);


}

void Alarm2()

{

  tone(buzzer2, 200);
  delay(500);

  noTone(buzzer2);
  delay(500);

}
