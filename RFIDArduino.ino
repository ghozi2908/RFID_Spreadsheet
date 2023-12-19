#include <SPI.h>     //Library SPI
#include <MFRC522.h> //Library MFRC522
#include <SoftwareSerial.h>
SoftwareSerial kirim(2,3);
#define SS_PIN 10    //Deklarasi pin SS
#define RST_PIN 9    //Deklarasi pin RST
MFRC522 mfrc522(SS_PIN, RST_PIN); //Deklarasi pin SS dan RST
  
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  kirim.begin(9600);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Tap Kartu Anda");
}  
void loop() 
{
  if(!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if(!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String uid="";
  Serial.println();
  Serial.print("UID=");
  for(int i=0;i<mfrc522.uid.size;i++)
  {
    Serial.print(mfrc522.uid.uidByte[i]<0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i],HEX);
    uid.concat(String(mfrc522.uid.uidByte[i]<0x10 ? "0" : ""));
    uid.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  uid.toUpperCase();
  if(uid=="D38B8B0D")  //Kode RFID
  {
    Serial.print("Regian Masuk");
    kirim.print("r");
  }
  else if(uid == "A3A79B0D"){
    Serial.print("Kelvin Masuk");
    kirim.print("k");
  }
  else if(uid == "93644D10"){
  Serial.print("Rachel Masuk");
  kirim.print("a");
  }
  else{
  kirim.print(0);  
  }
 uid ="";
delay(1000);
}