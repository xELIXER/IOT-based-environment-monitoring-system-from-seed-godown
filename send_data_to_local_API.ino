#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <DallasTemperature.h>
#include <OneWire.h>
//#include <WiFi.h>
#include <ESP8266HTTPClient.h>

#define ONE_WIRE_BUS 4  //D1 pin of nodemcu
#define maxi 5
#define mini 16
#define sensor_id 1
const uint16_t port = 8080;
const char * host = "192.168.43.224";

OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire); 
WiFiServer server(80);
ESP8266WiFiMulti WiFiMulti;
//IPAddress local_server(74,125,115,105);
WiFiClient client;
bool Connected;
String header;          

void setup(void)
{
  Serial.begin(9600); 
  sensors.begin();
  pinMode(maxi, OUTPUT);
  pinMode(mini, OUTPUT);
  WiFiManager wifiManager;
  wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,52), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect("Blackjack","12345678");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  Serial.println("Client connecting on port 8080");
  Connected = false;
}

void loop(void)
{ 
  WiFiClient client= server.available();
  sensors.requestTemperatures();  
  float temp;
  temp= sensors.getTempCByIndex(0); 
  Serial.println("Temperature is: ");
  Serial.println(temp);
  if(client.connect(host, port)){
    Serial.println("Connected to local server!");
    Serial.println("Sending data to local server!");
    String request = "GET /" + String(temp) + " HTTP/1.1";
    client.println(request);
    Serial.println("Connected to local server!");
  }
  Serial.println("Waiting for 5 sec...");
  delay(5000);
}

