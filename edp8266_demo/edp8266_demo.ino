#include <SoftwareSerial.h>
#include "main.h"
#include "RS485.h"
SoftwareSerial RS485;

void setup()
{
  RS485.setPin(13,15);
  RS485.begin(9600);
  
  Serial.begin(9600);
}
void loop()
{
    /*主机向从机发送获取数据指令*/
    MasterGetData(0x01);              //向设备请求参数信息
    if (RS485.available()>0)          //判断串口缓冲区是否接受到数据
    {
      int len = RS485.available();    //读取串口缓冲区数据的字节数
      if (len = 39)                   //如果从机返回的数据长度等于39字节，则存储该数据
      {
        for (int i=0; i<len; i++)
        {
          RS485A.UN2.slavePtr[i] = RS485.read();     //将串口缓冲区的数据按字节存储到slavePtr[]数组中
        }
        MasterReceProc(0x01);
      }
      else                            //如果返回数据长度不等于35字节，则清空串口缓冲区
      {
        while(RS485.available())
        RS485.read();
      }
    }


    /*
      主机向从发送修改参数指令
      实参依次填写设备码、寄存器地址高八位、寄存器地址低八位、设置参数高八位、设置参数低八位
      可修改对应寄存器中参数的值
    */
    MasterSetData(0x01, 0x00, 0x0e, 0xff, 0xff);    //启动全部
    MasterSetData(0x01, 0x00, 0x04, 0x00, 0xc8);    //设定速度为200


}


//调用MasterGetData(u8 devnum)时，实参填写设备码，可获取对应设备的各项参数
void MasterGetData(u8 devnum)
{
  int message[8] = {devnum,0x03,0x00,0x00,0x00,0x11}; 
  int crc = CRC16(message, 6);   //调用函数计算校验值
  int crclow = crc & 0x00ff;     //取crc校验值低八位
	int crchigh = crc >>8;         //取crc校验值高八位
	message[6] = crclow;           //先存crc校验值低八位
	message[7] = crchigh;          //再存crc校验值高八位
  for(int i=0; i<8; i++)     
  RS485.write(message[i]);      //通过串口按字节向从机发送获取数据指令
  delay(5000);
}


/*
  调用MasterSetData()时，实参依次填写设备码、寄存器地址高八位、寄存器地址低八位、设置参数高八位、设置参数低八位
  可修改对应寄存器中参数的值
*/
void MasterSetData(u8 devnum, u8 idhigh, u8 idlow, u8 setdatahigh, u8 setdatalow)
{
  int message[8] = {devnum, 0x06, idhigh, idlow, setdatahigh, setdatalow};
  int crc = CRC16(message, 6);   //调用函数计算校验值
  int crclow = crc & 0x00ff;     //取crc校验值低八位
	int crchigh = crc >>8;         //取crc校验值高八位
	message[6] = crclow;           //先存crc校验值低八位
	message[7] = crchigh;          //再存crc校验值高八位
  for(int i=0; i<8; i++)     
  RS485.write(message[i]);      //通过串口按字节向从机发送获取数据指令
  delay(5000);
}


//modbus协议16位CRC校验算法,返回unsigned short(两字节)类型的CRC校验值
//int * puchMsg, 要进行CRC校验的消息
//unsigned short usDataLen,消息中的字节数
unsigned short CRC16(int * puchMsg, unsigned short usDataLen)
{
  int i, j;                             
  unsigned short usRegCRC = 0xFFFF;     //用于保存crc值

  for(i=0; i<usDataLen; i++)            //循环处理传输的数据
  {
    usRegCRC ^= * puchMsg++;            //异或算法得到crc值
    for (j=0; j<8; j++)                 //循环处理每个bit位
    {
      if(usRegCRC & 0x0001)
      usRegCRC = usRegCRC >> 1 ^ 0xA001;
      else
        usRegCRC >>= 1;
    }
  }
  return usRegCRC;
}    
