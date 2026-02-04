#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include "ThingSpeak.h"

#define SECRET_SSID "YOUR_WIFI"		// add your WiFi network name
#define SECRET_PASS "YOUR_PASSWORD"	// add with your WiFi password
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
WiFiClient  client;


#define SECRET_CH_ID  "YOUR_ID"		// add your channel number
#define SECRET_WRITE_APIKEY "YOUR_THINGSPEAK_API_KEY"   // add your channel write API Key
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED SSD1306 address (thường là 0x3C)
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define ONE_WIRE_BUS 33
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() 
{
  Serial.begin(115200);
  Serial.println("SSD1306 OLED Test Start");
  pinMode(32, INPUT);
  Wire.begin(22, 21);  // SDA, SCL — đổi nếu bạn dùng chân khác
  sensors.begin();
  // ===== OLED INIT =====
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) 
  {
    Serial.println("Failed to initialize SSD1306!");
    for(;;);
  }
 //Wifi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

//thingspeak
ThingSpeak.begin(client);

  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP());


//OLED START
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // ===== TEST 1: Text cơ bản =====
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("OLED SSD1306 Test");
  display.println("Hello ESP32!");
  display.display();
  delay(1500);

  // ===== TEST 2: Fill screen =====
  display.clearDisplay();
  display.fillRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();
  delay(800);

  display.clearDisplay();

  // ===== TEST 3: Draw shapes =====
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.drawCircle(64, 32, 20, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 0, SSD1306_WHITE);
  display.display();
  delay(1500);

  // ===== TEST 4: FPS test =====
  display.clearDisplay();
  for (int i = 0; i < 100; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Frame: ");
    display.println(i);
    display.drawCircle(random(10,120), random(10,50), 5, SSD1306_WHITE);
    display.display();}
    display.clearDisplay();
}

void loop() 
{
sensors.requestTemperatures();
  float T = sensors.getTempCByIndex(0);   
  float TDS = analogRead(32);   

   display.setTextSize(1);
  display.setCursor(0, 0);
display.print ("Nhiet do: ");
 display.setCursor(60, 0);
display.print (T);
display.setCursor(90, 0);
  display.print ("do C");
display.setCursor(0, 30);
display.print("Chi so TDS: ");
display.setCursor(70, 30);
display.print (TDS);
display.setCursor(90, 30);
display.print (" ppm");
display.display();

  Serial.print ("Nhiet do : ");
  Serial.print (T);
  Serial.print (" °C      ");
  Serial.print("Chi so TDS: ");
  Serial.print(TDS);
Serial.println (" ppm");

ThingSpeak.setField(1, TDS);
ThingSpeak.setField(2, T);       
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  display.clearDisplay();

  delay (15000);
}
