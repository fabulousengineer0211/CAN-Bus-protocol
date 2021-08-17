#include <SPI.h>
#include <mcp_can.h>

const int spiCSPin = 10;
const int ledPin = 5; // With protection resistor

MCP_CAN CAN(spiCSPin);

void setup(){
    Serial.begin(115200);
    pinMode(ledPin,OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) { 
        Serial.println("CAN BUS Module failed to start");
        Serial.println(" Try again");
        delay(100);
    }
    Serial.println("CAN BUS Module started.");
}

void loop(){
    byte len = 0;
    byte bufin[3];

    if(CAN_MSGAVAIL == CAN.checkReceive()){
        CAN.readMsgBuf(&len, bufin);
        unsigned long canId = CAN.getCanId();
        Serial.println("-----------------------------");
        Serial.print("Data from ID: 0x");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++){
            Serial.print(bufin[i]);
            Serial.print("\t");
            // Update LED state from 1st data item 
            if(i==0)
              {digitalWrite(ledPin, bufin[0]);} 
        }
        Serial.println();
    }
}
