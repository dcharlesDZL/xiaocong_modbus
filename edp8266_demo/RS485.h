void MasterReceProc(u8 devNum)
{
  #pragma pack()
  if ( RS4852.UN2.slaveBuf.node == 0x01)
  {
    if (RS4852.UN2.slaveBuf.id == 0xae)
    
      RS4852.bufLen = 65;
      if ( SlaveCheckSum() != RS4852.UN2.slaveBuf.checkSum)
      {
        RsReset();
        return;
      }

      MachinePara.machineType          = RS4852.UN2.slaveBuf.type;
      MachinePara.paraTemp             = HTONS(RS4852.UN2.slaveBuf.temp);
      MachinePara.paraHumidity         = HTONS(RS4852.UN2.slaveBuf.humidity);
      MachinePara.paraSpeed            = HTONS(RS4852.UN2.slaveBuf.speed);
      MachinePara.paraConcen           = HTONS(RS4852.UN2.slaveBuf.concentration);
      MachinePara.paraPressure         = HTONS(RS4852.UN2.slaveBuf.pressure);
      MachinePara.paraIllumination     = RS4852.UN2.slaveBuf.illumination;
      MachinePara.paraRunTime          = HTONS(RS4852.UN2.slaveBuf.runTime);
      MachinePara.paraUV               = HTONS(RS4852.UN2.slaveBuf.uvValue);
      MachinePara.paraBean             = HTONS(RS4852.UN2.slaveBuf.been);
     
      {
        MachinePara.setTime            = HTONS(RS4852.UN2.slaveBuf.setTime);
        MachinePara.setIllumination    = RS4852.UN2.slaveBuf.illumination;
        MachinePara.setPressure        = HTONS(RS4852.UN2.slaveBuf.setPressure);
        MachinePara.setConcentration   = HTONS(RS4852.UN2.slaveBuf.setConcentration);
        MachinePara.setSpeed           = HTONS(RS4852.UN2.slaveBuf.setSpeed);
        MachinePara.setHumidity        = HTONS(RS4852.UN2.slaveBuf.setHumidity);

        MachinePara.setTemp            = HTONS(RS4852.UN2.slaveBuf.setTemp);
        MachinePara.setCycle           = RS4852.UN2.slaveBuf.setCycle;
        MachinePara.setSec             = RS4852.UN2.slaveBuf.setSec;

        MachinePara.tempSetMin         = HTONS(RS4852.UN2.slaveBuf.tempMin);
        MachinePara.tempSetMax         = HTONS(RS4852.UN2.slaveBuf.tempMax);
        MachinePara.speedSetMax        = HTONS(RS4852.UN2.slaveBuf.speedMax);
        MachinePara.illuminationMax    = RS4852.UN2.slaveBuf.illuminationRange;

        MachinePara.concentrationMax   = HTONS(RS4852.UN2.slaveBuf.concentrationRange);
        MachinePara.setBean            = HTONS(RS4852.UN2.slaveBuf.been);
      }

      if (RS4852.sendState == 0) //防止在设置的时候数据改变
      {
        RS4852.UN1.masterBuf.setTime          = RS4852.UN2.slaveBuf.setTime;
        RS4852.UN1.masterBuf.setIllumination  = RS4852.UN2.slaveBuf.illumination;
        RS4852.UN1.masterBuf.setPressure      = RS4852.UN2.slaveBuf.setPressure;
        RS4852.UN1.masterBuf.setConcentration = RS4852.UN2.slaveBuf.setConcentration;
        RS4852.UN1.masterBuf.setSpeed         = RS4852.UN2.slaveBuf.setSpeed;
        RS4852.UN1.masterBuf.setHumidity      = RS4852.UN2.slaveBuf.setHumidity;
        RS4852.UN1.masterBuf.setTemp          = RS4852.UN2.slaveBuf.setTemp;
        RS4852.UN1.masterBuf.setCycle         = RS4852.UN2.slaveBuf.setCycle;
        RS4852.UN1.masterBuf.setSec           = RS4852.UN2.slaveBuf.setSec;
        RS4852.UN1.masterBuf.been           =   RS4852.UN2.slaveBuf.been;

        key.bits.heatKey = (RS4852.UN2.slaveBuf.statusReserve & 0x0001) ? 1 : 0;
        key.bits.coolKey = (RS4852.UN2.slaveBuf.statusReserve & 0x0002) ? 1 : 0;
        key.bits.loopKey = (RS4852.UN2.slaveBuf.statusReserve & 0x0010) ? 1 : 0;
        key.bits.stirKey = (RS4852.UN2.slaveBuf.statusReserve & 0x0020) ? 1 : 0;
        key.bits.powerKey  = (RS4852.UN2.slaveBuf.status & 0x1000) ? 1 : 0;
        key.bits.otherTrig = 0;
        RS4852.UN1.masterBuf.reserve1 = key.value;
      }

      alarm = MachinePara.alarm = HTONS(RS4852.UN2.slaveBuf.status) & 0x27ff;
      alarmReserve = MachinePara.alarmReserve = HTONS(RS4852.UN2.slaveBuf.statusReserve) & 0x7f00;
      AlarmTask();
      ready_485 = 1;
      RunningPara.rs485Triged = 1;
      comOK();
    } else if (RS4852.UN2.slaveBuf.id == 0xaf)
    {
      RS4852.bufLen = 4;
      if ( SlaveCheckSum() != RS4852.UN2.slavePtr[4])
      {
        RsReset(); return;
      }
      ackOk = 1;
      APPSendMessageAlarm(MessageSetReply());
      comOK();
    } else if (RS4852.UN2.slaveBuf.id == 0xB0)
    {
      RS4852.bufLen = 4;
      if ( SlaveCheckSum() != RS4852.UN2.slavePtr[4])
      {
        RsReset(); return;
      }
      comOK();
    }
  } else
  {
    RsReset();
  }
}