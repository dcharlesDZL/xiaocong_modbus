#include <SoftwareSerial.h>
SoftwareSerial rs485;
void setup()
{
rs485.begin(9600);
rs485.setPin(13,15);
//rs485.setTX(15);
//rs485.setRX(13);
Serial.begin(9600);

}
void loop()
{
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce};
    for(int i=0; i<8; i++)     rs485.write(message[i]);
     delay(1000);
//    Serial.read();
//    Serial.write(message);
//    rs485.read();
}