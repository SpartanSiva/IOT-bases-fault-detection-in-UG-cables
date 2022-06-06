#include <LCD_I2C.h>
LCD_I2C lcd(0x27);
#include <Wire.h> 

 #define rac A0
 #define yac A1
 #define bac A2

 
 
#define acload A3
 #define buzzer 7
int spacvalue,cablevalue,racvalue,yacvalue,bacvalue; 
int km2value,km5value,km10value,ac_current;
 void setup ( ) {
   Serial.begin ( 9600 ) ;
  Wire.begin();
  lcd.begin();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home(); 
  lcd.setCursor(0,0);
    lcd.print("UG CABLE FAULT");
    delay(3000);
    lcd.clear();
   pinMode(rac,INPUT);
   pinMode(yac,INPUT);
   pinMode(bac,INPUT);
   pinMode(acload,INPUT);
  pinMode(buzzer,OUTPUT);
      digitalWrite(buzzer,LOW);
 


 }
 void loop ( ) {
   // Reading temperature or humidity may take about 2 seconds because it is a very slow sensor.





//Red  Ac value Sensor.....................................
    
    lcd.setCursor(0,0);
    lcd.print("R :");
//    Serial.print("RAC :");
//    Serial.println(analogRead(rac));
    if(analogRead(rac)<=200)
      {
        racvalue=0;
    lcd.print("0     ");
      }
     else{
      racvalue=230;
      lcd.print("230   ");
      }
   



//yellow Ac value Sensor.....................................
    
    lcd.setCursor(9,0);
    lcd.print("Y :");
    
//    Serial.print("YAC :");
//    Serial.println(analogRead(yac));
    if(analogRead(yac)<=200)
      {
        yacvalue=0;
    lcd.print("0    ");
      }
     else{
      yacvalue=230;
      lcd.print("230  ");}
   



//blue Ac value Sensor.....................................
    
    lcd.setCursor(0,1);
    lcd.print("B :");
    
    Serial.print("BAC :");
    Serial.println(analogRead(bac));
    bacvalue=analogRead(bac);
    bacvalue=map(bacvalue,0,500,0,230);
    lcd.print(bacvalue);

    lcd.setCursor(9,1);
    lcd.print("C :");
    
     ac_current = analogRead(acload);
     Serial.print("AC:");
     Serial.println(ac_current);
  ac_current=map(ac_current,0,172,0,999);
  if(ac_current <= 90){ac_current = 0;}
  else{ac_current = ac_current;}
   if(ac_current <= 9){lcd.print("00");lcd.print(ac_current);}
    else if(ac_current <= 99){lcd.print("0");lcd.print(ac_current);}
    else if(ac_current <= 999){lcd.print(ac_current);}
   if(yacvalue==0||racvalue==0||bacvalue<=230)
   {
    digitalWrite(buzzer,HIGH);
   }
   else
   {
       digitalWrite(buzzer,LOW);
   }
    
senddata();
  delay(1000);
 }

void senddata()
{
  Serial.print('*');
  
  
  if(bacvalue==0 && racvalue==0 && yacvalue==0)
  {
    Serial.println("RYB Phases Disconnected");
  }
  else{
  if(racvalue==230 ){Serial.println("R phase Connected");}
  else{Serial.println("RG Fault");}
// 
//
  if(yacvalue==230 ){Serial.println("Y phase Connected");}
  else{Serial.println("YG Fault");}
//
// 
  if(bacvalue==230 ){Serial.println("B phase Connected");Serial.println(bacvalue);}
  else{Serial.println("BG Fault");Serial.println(bacvalue);}
  }
//
   Serial.println();

if(ac_current>0){Serial.println("CURRENT CONSUMPTION"); Serial.println(ac_current);}
//
Serial.println();
Serial.println();
//
//
 Serial.print('@');
}
