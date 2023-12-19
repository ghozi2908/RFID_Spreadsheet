#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(D5,D6);

const char* ssid = "UNTIRTAKU"; //--> Your wifi name or SSID.
const char* password = "untirtajawara"; //--> Your wifi password.


//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

WiFiClientSecure client; //--> Create a WiFiClientSecure object.

String GAS_ID = "AKfycbxs4FHTLMYL0u4rM8_EYn6OPvWwUuQXyS6qh-ErOdksGNhqcKUHBbkpRS8G9MBRcJXR"; //--> spreadsheet script ID
String n = "Regian";
String i = "1234";
char data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial.begin(9600);
  delay(500);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.

    //----------------------------------------
  }
  //----------------------------------------
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  client.setInsecure();
}

void loop() {
  String nama = "nama : " + n;
  String nim = "nim : " + i;
  Serial.println(nama);
  Serial.println(nim);
  kirim();
  if (n != "" && i != ""){
  sendData(n, i); //--> Calls the sendData Subroutine
  }
  n="";
  i="";
}

// Subroutine for sending data to Google Sheets
void sendData(String nama, String nim) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
    if (!client.connected()) {
      if (!client.connect(host, httpsPort)) {
         Serial.println("connection failed");
         return;
      }
   }

  //----------------------------------------

  //----------------------------------------Processing data and sending data
  String string_nama =  n;
  String string_nim =  i; 
  String url = "/macros/s/" + GAS_ID + "/exec?nama=" + string_nama + "&nim=" + string_nim;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------

  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }

  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 

void kirim(){
  if(serial.available()>0){
  data = serial.read();
      if(data == 'r') {
        n = "Regian";
        i="3332200107.";
      }
      else if(data == 'a') {
        n="Amabel";
        i="3332200018.";
      }
      else if(data == 'k') {
        n="Kelvin";
        i="3332200082.";
      }}
      else {
        n="";
        i="";
      }
}
