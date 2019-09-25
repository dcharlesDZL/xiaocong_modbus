#include <SoftwareSerial.h>
SoftwareSerial rs485;
void setup()
{
RS485.begin(9600);
RS485.setPin(13,15);
//rs485.setTX(15);
//rs485.setRX(13);
Serial.begin(9600);

}
void loop()
{
    //向设备请求参数信息
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce}; 
    for(int i=0; i<8; i++)     RS485.write(message[i]);
     delay(1000);
//    Serial.read();
//    Serial.write(message);
//    rs485.read();
}