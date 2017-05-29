// Begin fifozeug

#define FIFOSIZE 33
uint8_t fifoBuffer[FIFOSIZE];
uint8_t* fifoWrPtr;
uint8_t* fifoRdPtr;
unsigned int fifoFill;

void fillElementFifo( uint8_t input );
int getElementFifo( uint8_t* outputPtr );
void initFifo();

// End fifozeug


//
// Stellt 1 Byte in den Ringbuffer
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist voll. Es kann kein weiteres Byte gespeichert werden
//     BUFFER_SUCCESS    das Byte wurde gespeichert
//
uint8_t BufferNext(uint8_t *pByte)
{
  
}

uint8_t BufferLength()
{
  if (buffer.write > buffer.read )
  {
    return (buffer.write -buffer.read);
    }
    else
  {
    return (buffer.write -buffer.read+BUFFER_SIZE);
  }
}

uint8_t BufferIn(uint8_t byte)
{
  //if (buffer.write >= BUFFER_SIZE)
  //  buffer.write = 0; // erhöht sicherheit

  if ( ( buffer.write + 1 == buffer.read ) ||
       ( buffer.read == 0 && buffer.write + 1 == BUFFER_SIZE ) )
    return BUFFER_FAIL; // voll

  buffer.data[buffer.write] = byte;

  buffer.write++;
  if (buffer.write >= BUFFER_SIZE)
    buffer.write = 0;

  return BUFFER_SUCCESS;
}

//
// Holt 1 Byte aus dem Ringbuffer, sofern mindestens eines abholbereit ist
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
//     BUFFER_SUCCESS    1 Byte wurde geliefert
//    
uint8_t BufferOut(uint8_t *pByte)
{
  if (buffer.read == buffer.write)
    return BUFFER_FAIL;

  *pByte = buffer.data[buffer.read];

  buffer.read++;
  if (buffer.read >= BUFFER_SIZE)
    buffer.read = 0;

  return BUFFER_SUCCESS;
}


void readSerial()
{
   while (Serial.available() > 0)
  {
    // 32Byte
    //BufferIn(Serial.read());
    fillElementFifo(Serial.read());
  }
  
}



void printP()
{
  update_volt_amp();
  resetTeleChecksum();
  writeTeleData('P');
  int16_t tmp = (int16_t) flightcontrol_sensors.amp * 1000;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  tmp = (int16_t) flightcontrol_sensors.volt * 1000;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  writeTeleChecksum();

}
void printM()
{
  update_mag();
  resetTeleChecksum();
  writeTeleData('M');
  writeTeleData(flightcontrol_sensors.mag[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.mag[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.mag[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.mag[2]&B11111111); //LSB
  writeTeleChecksum();
}

void printTP()
{
  update_mag();
  resetTeleChecksum();
  writeTeleData('T');
  writeTeleData(flightcontrol_sensors.pres >> 8); //MSB
  writeTeleData(flightcontrol_sensors.pres & B11111111); //LSB
  int16_t tmp = (int16_t) flightcontrol_sensors.temp * 10.0;
  writeTeleData(tmp >> 8); //MSB
  writeTeleData(tmp & B11111111); //LSB
  writeTeleChecksum();

}

void printF()
{
  update_gyr_acc();
  //Gyro xyz
  //Acc xyz
  resetTeleChecksum();
  writeTeleData('F');
  writeTeleData(flightcontrol_sensors.gyr[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.gyr[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.gyr[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.gyr[2]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[0] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[0]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[1] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[1]&B11111111); //LSB
  writeTeleData(flightcontrol_sensors.acc[2] >> 8); //MSB
  writeTeleData(flightcontrol_sensors.acc[2]&B11111111); //LSB
  writeTeleChecksum();
}

uint8_t checksumdata = 0;
void resetTeleChecksum()
{
  checksumdata = 0;
}
void writeTeleData(uint8_t data)
{
  checksumdata = checksumdata ^ data;
  Serial.write(data);
}

void writeTeleChecksum()
{
  Serial.write(checksumdata);
  checksumdata = 0;
}

void sendTelemetry()
{
  printF();

  if (tele_cnt == 4 || tele_cnt == 8)
  {
    printM();
  }
  if (tele_cnt >= 9)
  {
    printP();
    
    tele_cnt = 0;
  }

  tele_cnt++;
}


void fillElementFifo( uint8_t input )
{
  if( fifoFill < FIFOSIZE ){
    *fifoWrPtr = input;
    fifoFill++;
    if( fifoWrPtr != &fifoBuffer[FIFOSIZE-1] ){
      fifoWrPtr++;
    }else{
      fifoWrPtr = &fifoBuffer[0];
    }
  }
}

int getElementFifo( uint8_t* outputPtr )
{
  if( fifoFill > 0 ){
    *outputPtr = *fifoRdPtr;
    fifoFill--;
    if( fifoRdPtr != &fifoBuffer[FIFOSIZE-1] ){
      fifoRdPtr++;
    }else{
      fifoRdPtr = &fifoBuffer[0];
    }
  }else{
    return -1;
  }
  return 0;
}

int getElementIndexFifo( unsigned int index, uint8_t outputPtr )
{
  if( index < fifoFill ){
    
  }else{
    return -1;
  }
  return 0;
}

int checkData()
{
  if( fifoFill > 0 ){
    int i = 0;
    int deleteVar = 0;
    while( i < datatypes.noTypes ){
      ++i;
      if( *fifoRdPtr == datatypes.types[i].type ){
        // forward
        if( fifoFill >= datatypes.types[i].length+2 ){
          uint8_t checksum = 0;
          for( int ii = 0; ii < datatypes.types[i].length; ++i ){
            //TBD gibts no a class
          }
          //paaaasst
        }else
        {
          break;
        }
      }else{
        deleteVar++;
      }
    }
    if( deleteVar == datatypes.noTypes ){
      uint8_t dummy;
      getElementFifo(&dummy);
    }
  }
  return 0;
}

void initFifo()
{
  fifoWrPtr = &fifoBuffer[0];
  fifoRdPtr = &fifoBuffer[0];
  fifoFill = 0; 
}







