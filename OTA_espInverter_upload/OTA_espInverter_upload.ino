#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <HardwareSerial.h>

HardwareSerial MySerial(1);

const char* ssid ="your wifi ssid";
const char* password = "your password";
// Add your MQTT Broker IP address
const char* mqtt_server = "192.168.1.50";//your mqtt server
char Rxrssi_str[10],bootCount_str[10],RxData_str[10];
int LED = 15,sendmqtt = 0;                              
String DayEnergy = "0";
String data_rx = "no data";
String RxData = "nil",topic;
char c;
int commaIndex = 0,upload_index = 0;
String data_rx_array[40];
int i = 0;

WiFiClient inverterClient; 
PubSubClient client(inverterClient);
#define TX 35 //GPIO 35
#define RX 37 //GPIO 37

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    wait(5000);
    ESP.restart();
  }
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  /////////////////////add normal setup here////////////////
  pinMode(RX, INPUT);  // sets the digital pin  as input 
  pinMode(TX, OUTPUT);  // sets the digital pin  as output
  
  MySerial.setRxBufferSize(512); //1024
  MySerial.begin(115200, SERIAL_8N1, RX, TX);
  wait(1000);
  Serial.println ("OTA ESP SOLAR UART monitor v1");
  client.setServer(mqtt_server,1883);
  client.connect("inverterClient", "mqtt user", "oscar");  
  Serial.println ("Setup mqtt");    
  pinMode(LED, OUTPUT);             // sets onboard LED pin as an output 
  wait(1000);  // Allow the hardware to initialize 
}

void loop() {
  ArduinoOTA.handle();
    digitalWrite(LED, HIGH);           // turn on LED to show esp32 running
    wait(500);
    digitalWrite(LED, LOW);
    Serial.println ("In loop");
    
   if(!client.connected()) {            // Test MQTT client connected
    Serial.print("Goto reconnect() ");
    reconnect();   
    }
  Data_read();
 } // void loop end
