// RA 02 is a Transciever module so pin config same for both sender and reciever,
// Pin config for Arduino UNO
// NSS -- pin 10
// MOSI -- pin 11
// MISO -- pin 12
// SCK -- pin 13
// RESET -- 9
// DIO0 -- 2 ( works on interrupt pins only , UNO has 2,3 as interrupt pins)
// vcc = 3.3V and GND

#include <SPI.h>
#include <LoRa.h>

int trigpin = 5;
int echopin = 6;

float distance;
float duration;

unsigned long prev_millis = 0;
int SyncWord = 0x22;

void setup() 
{
  // put your setup code here, to run once:
  pinMode (trigpin , OUTPUT);
  pinMode (echopin , INPUT);

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  // LoRa.setSpreadingFactor(12);
  // //LoRa.setSignalBandwidth(62.5E3);
  // LoRa.setCodingRate4(8);                   

  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  if (LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa");
    while (1);
  }
}

void loop() 
{

  digitalWrite(trigpin , LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin , LOW);

  
  duration = pulseIn(echopin , HIGH);
  //By default the duration of pulse returned by the module is in microseconds
  distance = duration*0.034/2;

  Serial.print("Sending packet: ");
  Serial.print("Dist = ");
  Serial.print(int(distance));
  Serial.println("cm");  
  
  LoRa.beginPacket();
  LoRa.print("Distance: ");
  LoRa.print(distance);
  LoRa.endPacket();

  if (millis() - prev_millis >= 600000)
  {
    setup();
    prev_millis = millis();
  }

  delay(2000);

}
