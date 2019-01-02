#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "my bulb wifi"
#define APPSK  "1234567890"
#endif

// ap ssid name
const char *ssid = APSSID;
// ap ssid password
const char *password = APPSK;
// status of bulb if it's on or off
bool bulbState = false;
// ip address of ap
IPAddress myIP;

// create web server on port 80
ESP8266WebServer server(80);


/**
  * print menu and state of bulb
  * @return {void}
*/
void printState(){
  if(bulbState){
    server.send(200, "text/html", "current state: on<br/><a href='/on'>on</a><br/><a href='/off'>off</a>");
  }else{
    server.send(200, "text/html", "current state: off<br/><a href='/on'>on</a><br/><a href='/off'>off</a>");
  }
}

/**
  * handle path /
  * @return {void}
*/
void handleRoot() {
  printState();
}

/**
  * handle path /on
  * @return {void}
*/
void handleOn() {
  bulbState = true;
  digitalWrite(5, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  printState();
}

/**
  * handle path /off
  * @return {void}
*/
void handleOff() {
  bulbState = false;
  digitalWrite(5, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  printState();
}

/**
  * on start
  * @return {void}
*/
void setup() {
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.softAP(ssid, password);
  myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

/**
  * do loop
  * @return {void}
*/
void loop() {
  
  server.handleClient();
}
