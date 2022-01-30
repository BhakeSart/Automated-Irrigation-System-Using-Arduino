

#include<LiquidCrystal.h>


#define echo 9
#define trigger 10
#define tank_pump 4
#define watering_pump 13
#define moisture_sensor A0
#define tempPin A1
long duration;
int distance;
int moisture_value;
int distance_percent;
int moist_percent;
float temp;
LiquidCrystal lcd(12,11,8,7,6,5);


void setup1()
{
  pinMode(tempPin, INPUT);
  Serial.begin(9600);
}

void loop1() 
{
temp = analogRead(tempPin);
temp = (temp *5.0*100.0)/1024.0; 
Serial.println(temp);
delay(1000);
}



//LCD DISPLAY
void setup () 
{
lcd.begin(20,4);
Serial.begin(9600);
pinMode(echo,INPUT);
pinMode(moisture_sensor,INPUT);
pinMode(trigger,OUTPUT);
digitalWrite(trigger,LOW);
pinMode(watering_pump,OUTPUT);
pinMode(tank_pump,OUTPUT);
digitalWrite(watering_pump,LOW);
digitalWrite(tank_pump,LOW);
lcd.setCursor(0,0);
lcd.print("AUTOMATED IRRIGATION");
lcd.setCursor(0,1);
lcd.print("SYSTEM");
lcd.setCursor(0,2);
lcd.print("BY-B10 GROUP"); 
delay(3000);
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print("WELCOME");
delay(1000);
lcd.clear();
}



// WATER LEVEL SENSOR.
void loop()
{
digitalWrite(trigger,LOW);
delayMicroseconds(2);
digitalWrite(trigger,HIGH);
delayMicroseconds(10); 
digitalWrite(trigger,LOW);
duration=pulseIn(echo,HIGH);
distance=duration*0.017; 
distance_percent=map( distance,0,1023,0,100);
moisture_value= analogRead(moisture_sensor);
moist_percent=map(moisture_value,0,1023,0,100);
condition();
loop1();
}


//MAIN WORKING
void condition()
{
if (distance_percent>50 && moist_percent<70)
{
LCD_3();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,HIGH);
delay(1000);
}

else if (distance_percent<65 &&moist_percent>85)
{
LCD_2();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,LOW);
delay(1000);
}

else if (distance_percent>65 &&moist_percent>85)
{
LCD_4();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,LOW);
delay(1000);
}

else if (distance_percent<65 &&moist_percent<85)
{
LCD_1();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,HIGH);
delay(1000);
}
}


//DIFFRENT LCD DISPLAY FUNCTIONS
void LCD_1()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("WATER PUMP:");
lcd.print("ON");
lcd.setCursor(0,3);
lcd.print("TANK PUMP:");
lcd.print("ON");
}

void LCD_2()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("WATER PUMP:");
lcd.print("OFF");
lcd.setCursor(0,3);
lcd.print("TANK PUMP:");
lcd.print("ON");
}
  
void LCD_3()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("WATER PUMP:");
lcd.print("ON");
lcd.setCursor(0,3);
lcd.print("TANK PUMP:");
lcd.print("OFF");
}

void LCD_4()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("WATER PUMP:");
lcd.print("OFF");
lcd.setCursor(0,3);
lcd.print("TANK PUMP:");
lcd.print("OFF");
}
