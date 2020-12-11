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
#define TEMPERATURE_SENSOR 2
#define POTENTIONMETER 4
#define JOYSTICK 5
#define DCMOTOR 6
#define MOTOR 10
#define SERVO 11
#define LINEFOLLOWER 17
#define GASSENSOR 25
#define ULTRASONIC_ARDUINO 36
#define TOUCH_SENSOR 51
#define AVOID_SENSOR 52 

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
void writeHead(){
  writeSerial(0xff);
  writeSerial(0x55);
}
void writeEnd(){
  Serial.println(); 
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
        //   writeHead();
        //   writeSerial(idx);
        // }
        readSensor(device);
        //writeEnd();
     }
     break;
     case RUN:{
       runModule(device);
      // callOK();
     }
      break;
      case RESET:{
        //reset
        dc.reset(M1);
        dc.run(0);
        dc.reset(M2);
        dc.run(0);
        // callOK();
      }
     break;
     case START:{
        //start
        // callOK();
      }
     break;
  }
}
void callOK(){
    writeSerial(0xff);
    writeSerial(0x55);
    writeEnd();
}
/*
inbyte
HumnityData: 3
TouchData:1
AvoidData:2
Buton:4
*/ 
void sendByte(char c, int intbyte){
  writeSerial(intbyte);
  writeSerial(c);
}
void sendString(String s){
  int l = s.length();
  writeSerial(4);
  writeSerial(l);
  for(int i=0;i<l;i++){
    writeSerial(s.charAt(i));
  }
}
void sendFloat(float value, int ten){ 
    writeSerial(0xff);
     writeSerial(ten);
     val.floatVal = value;
     writeSerial(val.byteVal[0]);
     writeSerial(val.byteVal[1]);
     writeSerial(val.byteVal[2]);
     writeSerial(val.byteVal[3]);
}
void sendShort(double value){
     writeSerial(3);
     valShort.shortVal = value;
     writeSerial(valShort.byteVal[0]);
     writeSerial(valShort.byteVal[1]);
}
void sendDouble(double value){
     writeSerial(2);
     valDouble.doubleVal = value;
     writeSerial(valDouble.byteVal[0]);
     writeSerial(valDouble.byteVal[1]);
     writeSerial(valDouble.byteVal[2]);
     writeSerial(valDouble.byteVal[3]);
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
    //  writeHead();
    //  writeSerial(command_index);     
     sendFloat(value,22);
     
   }
   break;
   case  TEMPERATURE_SENSOR:{
     slot = readBuffer(7);
     if(ts.getPort()!=port||ts.getSlot()!=slot){
       ts.reset(port,slot);
     }
     value = ts.temperature();
     sendFloat(value,11);
   }
   break;
    case TOUCH_SENSOR:
   {
     if(touchSensor.getPort() != port){
       touchSensor.reset(port);
     }
     sendByte(touchSensor.touched(),1);
   }
   break;
  case AVOID_SENSOR:
   {
     if(avoidSensor.getPort() != port){
       avoidSensor.reset(port);
     }
     sendByte(avoidSensor.Avoidtested(),2);
   }
   break;
  case GASSENSOR:{
     if(GasSensor.getPort()!=port){
       GasSensor.reset(port);
       GasSensor.setpin(GasSensor.pin2(),GasSensor.pin1());
     }
     int16_t GasData; 
     GasData = GasSensor.readAnalog();
     sendShort(GasData);
   }
  break;
  case  LINEFOLLOWER:{
     if(generalDevice.getPort()!=port){
       generalDevice.reset(port);
         pinMode(generalDevice.pin1(),INPUT);
         pinMode(generalDevice.pin2(),INPUT);
     }
     value = generalDevice.dRead1()*2+generalDevice.dRead2();
     Serial.println(value);
     sendFloat(value,17);
   }
   break;
   case  POTENTIONMETER:{
     if(generalDevice.getPort()!=port){
       generalDevice.reset(port);
       pinMode(generalDevice.pin2(),INPUT);
     }
     value = generalDevice.aRead2();
     sendFloat(value,12);
   }
   break;
  }
}