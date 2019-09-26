#include <SoftwareSerial.h>
#include "main.h"
SoftwareSerial RS485;

void setup()
{
  RS485.begin(9600);
  RS485.setPin(13,15);
  Serial.begin(9600);
}
void loop()
{
    //向设备请求参数信息
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce}; 
    for(int i=0; i<8; i++)     
    RS485.write(message[i]);          //通过串口按字节向从机发送获取数据指令
    delay(1000);

    if (RS485.available()>0)          //判断串口缓冲区是否接受到数据
    {
      int len = RS485.available();    //读取串口缓冲区数据的字节数
      if (len = 35)                   //如果从机返回的数据长度等于35字节，则存储该数据
      {
        for (int i=0; i<len; i++)
        {
          RS485A.UN2.slavePtr[70] = RS485.read();     //将串口缓冲区的数据按字节存储到slavePtr[]数组中
        }
        if (RS485A.UN2.slavePtr[0] == 0x01 && RS485A.UN2.slavePtr[1] == 0x03)     //判断从机返回的数据前两个字节
        MasterReceProc(0x01);
      }
      else                            //如果返回数据长度不等于35字节，则情况串口缓冲区
      {
        while(RS485.available())
        RS485.read();
      }
      
      
    }
}
