#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//cablefaultiote878@gmail.com
//Info@2021

//for value update
//http://blynk-cloud.com/q4iZZRmln47Weo_vWFW4TyduqPgJlcrz/get/v0

//to controll motor 1=ON 0=OFF
//http://blynk-cloud.com/q4iZZRmln47Weo_vWFW4TyduqPgJlcrz/update/v1?value=0


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "  wkLdseLVk2UG0xYh6OWrBxw0TjNqupt-";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT7";
char pass[] = "123456789";

unsigned int m=0,act=0;

String inputString = ""; 
unsigned char a[200];

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  
}

void loop()
{
  while (Serial.available()) {
    // get the new byte:
    char inChar;
    
    
    //a[m] = (char)Serial.read(); 
    inChar = (char)Serial.read(); 
    
      //Serial.print(inChar);
      
      a[m] = inChar;
      if(a[0] == '*'){if(a[m] == '@'){act = 1;}else{if(m<=200){m++;inputString += inChar;}}}
   
     
  }
  if(act)
  {
    Blynk.virtualWrite(V0, inputString);
    Serial.print(inputString);
    m=0;inputString = " ";
    act = 0;

  }
  Blynk.run();
}
