/*
The firmware of TK-BOT use in the education and fresers in the discpvery IOT.
*/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <TKOrion.h>

// Decaled libary of TkBot 
Servo servos[8];
TKDCMotor dc;
TKTemperature ts;
TKJoystick joystick;
TKAvoidSensor avoidSensor;
TKUltrasonicSensorB usB;
TKGasSensor GasSensor;
TKTouchSensor touchSensor;
TKPort generalDevice;
TKBuzzer buTK;
TKButton btTK;
 
typedef struct TKModule
{
    int device;
    int port;
    int slot;
    int pin;
    int index;
    float value[3];
} TKModule;

union {
    byte byteVal[4];
    float floatVal;
    long longVal;
} val;
union{
  byte byteVal[8];
  double doubleVal;
}valDouble;

union{
  byte byteVal[2];
  short shortVal;
}valShort;
String mVersion = "TK.01.001";
boolean isAvailable = false;
boolean isBluetooth = false;

int len = 53;
char buffer[53];
char bufferBt[53];
byte index = 0;
byte dataLen;
byte modulesLen=0;
boolean isStart = false;
unsigned char irRead;
char serialRead;  

// Vairiable of the module and sensor.
#define VERSION 0
#define MOTOR 1
#define JOYSTICK 2
#define SERVO 3
#define BUZZER 4


#define ULTRASONIC_ARDUINO 10
#define POTENTIONMETER 11
#define AVOID_SENSOR 12 
#define TOUCH_SENSOR 13
#define TEMPERATURE_SENSOR 14
#define GASSENSOR 15
#define LINEFOLLOWER 16
#define BUTTON_MODULE 17
#define DCMOTOR 6


// Created to variable.
#define GET 1
#define RUN 2
#define RESET 4
#define START 5

float angleServo = 90.0;
int servo_pins[8]={0,0,0,0,0,0,0,0};
unsigned char prevc=0;
double lastTime = 0.0;
double currentTime = 0.0;
uint8_t command_index = 0;

//Beginning for system
void setup(){
  Serial.begin(115200);
  Serial.print("Version: ");
  Serial.println(mVersion);
}
// while true:

void loop(){
  currentTime = millis()/1000.0-lastTime;
  readSerial();
  if(isAvailable){
    unsigned char c = serialRead&0xff;
    if(c==0x55&&isStart==false){
     if(prevc==0xff){
      index=1;
      isStart = true;
     }
    }else{
      prevc = c;
      if(isStart){
        if(index==2){
         dataLen = c; 
        }else if(index>2){
          dataLen--;
        }
        writeBuffer(index,c);
      }
    }
     index++;
     if(index>52){
      index=0; 
      isStart=false;
     }
     if(isStart&&dataLen==0&&index>3){ 
        isStart = false;
        parseData(); 
        index=0;
     }
  }
}
unsigned char readBuffer(int index){
  return isBluetooth?buffer[index]:bufferBt[index]; 
}
void readSerial(){
  isAvailable = false;
  if(Serial.available()>0){
    isAvailable = true;
    isBluetooth = false;
    serialRead = Serial.read();
  } 
}
void writeBuffer(int index,unsigned char c){
  if(isBluetooth){
    buffer[index]=c;
  }else{
    bufferBt[index]=c;
  } 
}
void writeSerial(unsigned char c){
  Serial.write(c);
}
/*
ff 55 len idx action device port  slot  data a
0  1  2   3   4      5      6     7     8
*/
//ff 55 08 00 02 06 4c 00 4c ff
void parseData(){
  isStart = false;
  int idx = readBuffer(3);
  command_index = (uint8_t)idx;
  int action = readBuffer(4);
  int device = readBuffer(5);  
  switch(action){
    case GET:{
        // if(device != ULTRASONIC_ARDUINO){
        //   writeSerial(idx);
        // }
        readSensor(device);
     }
     break;
     case RUN:{
       runModule(device);
     }
      break;
      case RESET:{
        //reset
        dc.reset(M1);
        dc.run(0);
        dc.reset(M2);
        dc.run(0);
      }
     break;
     case START:{
      }
     break;
  }
}
/*
inbyte
HumnityData: 3
TouchData:1
AvoidData:2
Buton:4
*/ 
void sendByte(char c, char name, char name1, int port){
  writeSerial(name);
  writeSerial(name1);
  writeSerial(port);
  writeSerial(c);
}
void sendFloat(float value, char name, char name1, int port){ 
    val.floatVal = value;
    writeSerial(name);
    writeSerial(name1);
    writeSerial(port);
    writeSerial(val.byteVal[0]);
    writeSerial(val.byteVal[1]);
    writeSerial(val.byteVal[2]);
    writeSerial(val.byteVal[3]);
}
void sendShort(double value, char name, char name1, int port){
    valShort.shortVal = value;
    writeSerial(name);
    writeSerial(name1);
    writeSerial(port);
    writeSerial(valShort.byteVal[0]);
    writeSerial(valShort.byteVal[1]);
}

short readShort(int idx){
  valShort.byteVal[0] = readBuffer(idx);
  valShort.byteVal[1] = readBuffer(idx+1);
  return valShort.shortVal; 
}
float readFloat(int idx){
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.floatVal;
}
long readLong(int idx){
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.longVal;
}

// Functions of module write.
void runModule(int device){
  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
  int port = readBuffer(6);
  int pin = port;
  switch(device){
   case MOTOR:{
     int speed = readShort(7);
     dc.reset(port);
     dc.run(speed);
    }
    break;
    case JOYSTICK:{
     int leftSpeed = readShort(6);
     dc.reset(M1);
     dc.run(leftSpeed);
     int rightSpeed = readShort(8);
     dc.reset(M2);
     dc.run(rightSpeed);
    }
    break;
   case SERVO:{
     int slot = readBuffer(7);
     if(slot == 1){
      pin = mePort[port].s1;
      }
     int angle = readBuffer(8);
     int duration = readBuffer(9);
     int timer = readBuffer(10);
     Servo sv = servos[searchServoPin(pin)];
     if(angle >= 0 && angle <= 180)
     {
       if(!sv.attached())
       {
         sv.attach(pin);
       }
       sv.write(angle);
      //  delay(duration*pow(10, timer));
     }
   }
   break;
   case BUZZER:{
      int slot = readBuffer(7);
     if(slot == 1){
      pin = mePort[port].s1;
      }
     int frequence = readShort(8);
     int durations = readShort(10);
     if (durations == 0){
       buTK.noTone();
     }else{
      buTK.tone(pin , frequence, durations);
     }
   }
   break;
  }
}
int searchServoPin(int pin){
    for(int i=0;i<8;i++){
      if(servo_pins[i] == pin){
        return i;
      }
      if(servo_pins[i]==0){
        servo_pins[i] = pin;
        return i;
      }
    }
    return 0;
}
void readSensor(int device){
  /**************************************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value=0.0;
  int port,slot,pin;
  port = readBuffer(6);
  pin = port;
  switch(device){
    case  ULTRASONIC_ARDUINO:{
      if(usB.getPort()!=port){
        usB.reset(port);
      }
      value = usB.distanceCm(); 
      if (port  == 2){
        sendFloat(value,'a','a', 2);
      } 
      if (port  == 3){
        sendFloat(value,'a','a', 3);
      } 
      if (port  == 5){
        sendFloat(value,'a','a', 5);
      } 
      if (port  == 6){
        sendFloat(value,'a','a', 6);
      } 
      if (port  == 7){
        sendFloat(value,'a','a', 7);
      } 
      if (port  == 8){
        sendFloat(value,'a','a', 8);
      }
   }
   break;
   case  TEMPERATURE_SENSOR:{
     slot = readBuffer(7);
     if(ts.getPort()!=port||ts.getSlot()!=slot){
       ts.reset(port,slot);
     }
     value = ts.temperature();
     sendFloat(value,'t','e', port);
   }
   break;
    case TOUCH_SENSOR:
   {
     if(touchSensor.getPort() != port){
       touchSensor.reset(port);
     }
     sendByte(touchSensor.touched(),'a','t', port);
   }
   break;
  case AVOID_SENSOR:
   {
     if(avoidSensor.getPort() != port){
       avoidSensor.reset(port);
     }
     sendByte(avoidSensor.Avoidtested(),'a','v', port);
   }
   break;
   case BUTTON_MODULE:
   {
     if(btTK.getPort() != port){
       btTK.reset(port);
     }
     sendByte(btTK.tkpressed(),'b','t', port);
   }
   break;
  case GASSENSOR:{
     if(GasSensor.getPort()!=port){
       GasSensor.reset(port);
       GasSensor.setpin(GasSensor.pin2(),GasSensor.pin1());
     }
     int16_t GasData; 
     GasData = GasSensor.readAnalog();
     sendShort(GasData, 'g', 's', port );
   }
  break;
  case  LINEFOLLOWER:{
     if(generalDevice.getPort()!=port){
       generalDevice.reset(port);
         pinMode(generalDevice.pin1(),INPUT);
         pinMode(generalDevice.pin2(),INPUT);
     }
    value = generalDevice.dRead1()*2+generalDevice.dRead2();
     sendFloat(value,'f', 'w', port);
   }
   break;
   case  POTENTIONMETER:{
     if(generalDevice.getPort()!=port){
       generalDevice.reset(port);
       pinMode(generalDevice.pin2(),INPUT);
     }
     value = generalDevice.aRead1();
     sendFloat(value,'p', 'p', port);
   }
   break;
  }
}