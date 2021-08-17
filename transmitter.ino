#include <mcp_can.h>
#include <SPI.h>
#include <dht.h>

dht DHT;

// Sensors used Accelerationmeasurement, temperature sesnors

const int SPI_CS_PIN = 10;
const int AccpinX = 4;
const int AccpinY = 5;
const int dhtpin  = A0;


MCP_CAN CAN(SPI_CS_PIN); // Chip select

void setup() {
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        Serial.println("CAN BUS Module failed to start");
        Serial.println(" Try again");
        delay(100);
    }
    Serial.println("CAN BUS Module started.");

  float x;
  float y;


 // x = analogRead(AccpinX);
 // y = analogRead(AccpinY);

 // while(DHT.read11(dhtpin) < 52)
 //  {
 // t = DHT.read11(dhtpin);
 //  }
    for (int i=0; i <256; i++){
    Serial.println("-----------------------------");
  x = analogRead(AccpinX);
  y = analogRead(AccpinY);

    while(DHT.read11(dhtpin) < 52)
   {
DHT.read11(dhtpin);
   }
   else
   {
    Serial.println("Error");    
   }
     // Place data to be sent in output buffer
       byte bufout[3] = {analogWrite(x),analogWrite(y),Serial.print(DHT.temperature)};
  
      // Sending:  ID = 0x05, standard frame, data len = 3, data in bufout
      CAN.sendMsgBuf(0x05, 0, 3, bufout);
      Serial.print("Packet sequence # ");
      Serial.println(i);
      for(int i = 0; i<3; i++){
          Serial.print(bufout[i]);
          Serial.print("\t"); 
      }
      Serial.println();
      delay(100);       // slow things down
    }

void loop(){}
