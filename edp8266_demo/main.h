//modbus数据结构
#pragma pack(1)  //让编译器将结构体数据强制连续排列，数据输出更紧凑
typedef struct
{
  union     //UN1  主机向从机写数据
  {
    struct
    {
      u8 node;              //设备号
      u8 funcode;           //功能码(0x10写)
      u8 idhigh;            //起始地址高八位
      u8 idlow;             //起始地址低八位
      u8 numhigh;           //寄存器数高八位
      u8 numlow;            //寄存器数低八位
      u8 datalen;           //数据字节长度
      s16 setTemp;          //设定温度
      s16 setSpeed;         //设定速度
      s16 setTimeHour;      //设定时间（小时）
      s16 setTimeMinute;    //设定时间（分钟）
      u16 tempMin;          //设定温度量程最小值
      u16 tempMax;          //设定温度量程最大值
      u16 speedMin;         //设定温度最小值
      u16 speedMax;         //设定温度最大值
      u16 setStatus;        //设置运行状态
      s16 setCurrentMode;   //设置当前模式（1/2/3）
      u8  setPwrOffMem;     //设置掉电记忆(0/1)
    } __attribute__ ((aligned (1))) masterBuf; 
    u8 masterPtr[40];
  } UN1;
  
  union       //UN2  当主机发送读取指令后从机向主机返回的参数
  {
    struct {
      u8 node;             //地址码
      u8 funcode;          //功能码
      u8 datalen;          //返回的数据长度

      u16 type;            //机器类型（全部两字节）
      u16 temp;            //当前温度
      u16 setTemp;         //温度设定值
      u16 speed;           //当前速度
      u16 setSpeed;        //速度设定值
      u16 setTimeHour;     //小时设定值
      u16 setTimeMinute;   //分钟设定值
      u16 timeHour;        //当前小时值
      u16 timeMinute;      //当前分钟值
      u16 tempRangeMin;    //温度量程最小值
      u16 tempRangeMax;    //温度量程最大值
      u16 speedMin;        //速度最小值
      u16 speedMax;        //速度最大值
      u8 innerSensorErr;              //内部传感器故障
      u8 innerTempAlarm;              //内部传感器温度报警
      u8 externalSensorErr;           //外部传感器故障
      u8 externalSensorOverrange;     //外部传感器超温
      u8 mechineTempOverrange;        //机械限温超温
      u8 mechineSensorErr;            //机械限温传感器故障
      u8 motorStalling;               //电机堵转
      u8 externalSensorDrop;          //外部传感器跌落
      u8 Timeout;                     //定时结束
      u8 externalSensorUnplugged;     //外部传感器未插入
      u16 status;                     //运行状态（到此处一共15个数据，共30字节）
      u16 checkcode;                  //校验码

      // s16 currentMode;                //当前模式（协议2.2添加的）
      // u8 powerOffMem;                 //掉电记忆（协议2.2添加的）
    }slaveBuf;                            //从机缓冲 modbus
    u8 slavePtr[70];                      //从机返回的数据
  } UN2;
} RS485_TYPE;
#pragma pack()
RS485_TYPE RS485A;


struct _MachinePara       //机器参数
{                   
  s16 machineType = 0;
  s16 paraTemp = 0;
  s16 setTemp = 50.0;     //缺省值为50
  s16 paraSpeed = 0;
  s16 setSpeed = 100;     //速度设定缺省值为100
  s16 setTimeHour = 0;
  s16 setTimeMinute = 0;
  s16 paraTimeHour = 0;
  s16 paraTimeMinute = 0;
  s16 paraTempRangeMin = 0;
  s16 paraTempRangeMax = 0;
  s16 setTempRangeMin = 0.0;
  s16 setTempRangeMax = 320.0;    //最大设定温度为320
  s16 paraSpeedMin = 0; 
  s16 paraSpeedMax = 0;
  s16 setSpeedMin = 100; //最小设定速度缺省值为100
  s16 setSpeedMax = 1500; //最大设定速度缺省值为1500
  u16 alarm,alarmReserve; //报警值，位操作
  u16 paraRunStatus = 0;
  u8 paraCurrentMode = 0;
  u8 paraPwrOffMem = 0;
  u8 setCurrentMode = 0;
  u8 setPwrOffMem = 0;
}MachinePara;
