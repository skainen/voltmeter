// BLYNKIN TIEDOT OLTAVA ALUSSA!! jotta blynk toimii
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLi-jllI5M"
#define BLYNK_DEVICE_NAME "Jännitteen mittaus"
#define BLYNK_AUTH_TOKEN "FtZn4hatIFHDeegLW9x3wacSi5LamWFM"
//
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WebServer.h>

// Auth token löytyy blynkistä kun luot uuden projektin
char auth[] = "FtZn4hatIFHDeegLW9x3wacSi5LamWFM";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


   BlynkTimer timer;
   uint8_t LEDpin = 27; // Ledi / hälytys pinniin 27
   int ai = analogRead(A3); // AnalogInput pinni. Luetaan luku josta saadaan laskettua jännite (loopissa)
   float vout = 0.0;
   float jannite = 0.0;
   float R1 = 11940.0; // Ensimmäisen vastuksen arvo 12k ohmia
   float R2 = 1495.0; // Toisen vastuksen arvo 1.5k ohmia


  //WiFi
  char ssid[] = "";
  char password[] = "";
  WebServer server(80);


void setup() {
  timer.setInterval(5000L, myTimerEvent); // Blynkin aliohjelma
  Serial.begin(115200);
  delay(100);
  pinMode(LEDpin, OUTPUT); // Ledi / hälytys

  //Wifi-asetukset
    Serial.println("Yhdistetään ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Yhdistetty!");
    Serial.print("IP-osoite: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP serveri käynnistetty");
    
// OLED
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0X3D)){ // Näytön osoite lukee takaosassa(0X3D)
    Serial.println(F("SSD1306 epäonnistui"));
    for(;;); // forever loop
    }
    display.display();
// Päivittää näytön
  display.clearDisplay();
  delay(2000);

// Blynkin käynnistys
  Blynk.begin(auth, ssid, password);


}


// OLED aliohjelma
void tulostusOled(uint8_t x, uint8_t y, String str){
  display.clearDisplay();  // putsaa näytön
  display.setCursor(x, y);  // asettaa koordinaatit x,y
  display.println(str);
  display.display();  // näyttö päälle
}



void loop() {
   Blynk.run();
    timer.run(); //
    delay(2000);

    server.handleClient();
    ai = analogRead(A3);
   vout = (ai * 3) / (4095.0);

/*
 * Todellisen jännitteen kalibrointi.
 * Luetaan A3 pinnistä lukema, joka on ilman vastuksia enimmillään 4095.
 * Otetaan huomioon vastusten vaikutus lukemaan. (R2/(R1+R2)) Muuttujat annettu koodin alussa.
 * Muuttamalla kerrointa pyritään saamaan todellisen jännitteen arvo näytölle.
 * 
 */
   if(ai >= 2000){
  jannite = vout / (R2/(R1+R2))*1.205;
   }
   else if(ai >= 1950 && ai <= 1999){
    jannite = vout / (R2/(R1+R2))*1.207;
   }
   else if(ai >= 1900 && ai <= 1949){
    jannite = vout / (R2/(R1+R2))*1.209;
   }
   else if(ai >= 1850 && ai <= 1899){
    jannite = vout / (R2/(R1+R2))*1.211;
   }
    else if(ai >= 1800 && ai <= 1849){
    jannite = vout / (R2/(R1+R2))*1.212;
   }
    else if(ai >= 1750 && ai <= 1799){
    jannite = vout / (R2/(R1+R2))*1.214;
   }
    else if(ai >= 1700 && ai <= 1749){
    jannite = vout / (R2/(R1+R2))*1.216;
   }
    else if(ai >= 1650 && ai <= 1699){
    jannite = vout / (R2/(R1+R2))*1.219;
   }
    else if(ai >= 1600 && ai <= 1649){
    jannite = vout / (R2/(R1+R2))*1.221;
   }
    else if(ai >= 1550 && ai <= 1599){
    jannite = vout / (R2/(R1+R2))*1.224;
   }
    else if(ai >= 1500 && ai <= 1549){
    jannite = vout / (R2/(R1+R2))*1.227;
   }
    else if(ai >= 1450 && ai <= 1499){
    jannite = vout / (R2/(R1+R2))*1.232;
   }
      else if(ai >= 1400 && ai <= 1449){
    jannite = vout / (R2/(R1+R2))*1.236;
   }
   else if(ai >= 1350 && ai <= 1399){
    jannite = vout / (R2/(R1+R2))*1.241;
   }
   else if(ai >= 1300 && ai <= 1349){
    jannite = vout / (R2/(R1+R2))*1.246;
   }
    else if(ai >= 1250 && ai <= 1299){
    jannite = vout / (R2/(R1+R2))*1.254;
   }
    else if(ai >= 1200 && ai <= 1249){
    jannite = vout / (R2/(R1+R2))*1.262;
   }
    else if(ai >= 1150 && ai <= 1199){
    jannite = vout / (R2/(R1+R2))*1.265;
   }
    else if(ai >= 1100 && ai <= 1149){
    jannite = vout / (R2/(R1+R2))*1.275;
   }
    else if(ai >= 1050 && ai <= 1099){
    jannite = vout / (R2/(R1+R2))*1.2805;
   }
    else if(ai >= 1000 && ai <= 1049){
    jannite = vout / (R2/(R1+R2))*1.3;
    }
       else if(ai >= 950 && ai <= 999){
    jannite = vout / (R2/(R1+R2))*1.305;
   }
   else if(ai >= 900 && ai <= 949){
    jannite = vout / (R2/(R1+R2))*1.315;
   }
   else if(ai >= 850 && ai <= 899){
    jannite = vout / (R2/(R1+R2))*1.32;
   }
    else if(ai >= 800 && ai <= 849){
    jannite = vout / (R2/(R1+R2))*1.335;
   }
    else if(ai >= 750 && ai <= 799){
    jannite = vout / (R2/(R1+R2))*1.355;
   }
    else if(ai >= 700 && ai <= 749){
    jannite = vout / (R2/(R1+R2))*1.374;
   }
    else if(ai >= 650 && ai <= 699){
    jannite = vout / (R2/(R1+R2))*1.392;
   }
    else if(ai >= 600 && ai <= 649){
    jannite = vout / (R2/(R1+R2))*1.413;
   }
    else if(ai >= 550 && ai <= 599){
    jannite = vout / (R2/(R1+R2))*1.43;
   }
    else if(ai >= 500 && ai <= 549){
    jannite = vout / (R2/(R1+R2))*1.46;
   }
    else if(ai >= 450 && ai <= 499){
    jannite = vout / (R2/(R1+R2))*1.55;
   }
      else if(ai >= 400 && ai <= 449){
    jannite = vout / (R2/(R1+R2))*1.58;
   }
   else if(ai >= 350 && ai <= 399){
    jannite = vout / (R2/(R1+R2))*1.6;
   }
   else if(ai >= 300 && ai <= 349){
    jannite = vout / (R2/(R1+R2))*1.63;
   }
    else if(ai >= 250 && ai <= 299){
    jannite = vout / (R2/(R1+R2))*1.82;
   }
    else if(ai >= 200 && ai <= 249){
    jannite = vout / (R2/(R1+R2))*1.84;
   }
    else if(ai >= 150 && ai <= 199){
    jannite = vout / (R2/(R1+R2))*1.82;
   }
    else if(ai >= 100 && ai <= 149){
    jannite = vout / (R2/(R1+R2))*2.65;
   }
    else if(ai <= 99){
      jannite = 0.0;
    }

// A3 saaman lukeman ja todellisen jännitteen tulostus sarjamonitoriin.
  Serial.print(jannite);
  Serial.println(" volttia");
  Serial.println(ai);
  
// OLED näytön tulostus
display.setCursor(0,0);
display.setTextSize(1);
display.setTextColor(WHITE);
display.print("J");
display.print((char)132); // ä
display.print("nnite ");
display.setCursor(10,20);
display.setTextSize(2);
display.setTextColor(WHITE);
display.print(jannite);
display.print(" V");
display.display();
delay(500);
display.clearDisplay();
delay(500);

// Hälytys
if (jannite <= 10){
  digitalWrite(LEDpin, HIGH);
}
else{
  digitalWrite(LEDpin, LOW);
}
  
}

// Blynk aliohjelma
 void myTimerEvent(){
    Blynk.virtualWrite(V7,jannite);
   }

// Serverin aliohjelmat
   void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(ai,jannite)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

// Webbisivu
String SendHTML(float ai,float jannite){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta charset='UTF-8'; http-equiv='refresh' content='10'>\n";
  ptr +="<title>Jännitteen mittaus</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Laitteen jännitemittaus</h1>\n";
  ptr +="<p><b>Jännite: </b>";
  ptr +=jannite;
  ptr +=" V</p>";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
