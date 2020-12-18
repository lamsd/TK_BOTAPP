/*
The firmware of TK-BOT use in the education and fresers in the discpvery IOT.
*/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <TKOrion.h>

// Decaled libary of TkBot 
String mVersion = "TK.01.001";
boolean isAvailable = false;
boolean isBluetooth = false;

Servo servos[8];
int servo_pins[8]={0,0,0,0,0,0,0,0};
int len = 15;
char buffer[15];
int index = 0;
byte dataLen;
byte modulesLen=0;
boolean isStart = false;
char serialRead;

unsigned char prevc=0;
double lastTime = 0.0;
double currentTime = 0.0;
uint8_t command_index = 0;
// import library of TK-BOT;
TKDCMotor dc;
TKUltrasonicSensorB usB;
TKPort generalDevice;
TKGasSensor GasSensor;
TKAvoidSensor avoidSensor;
TKTouchSensor touchSensor;
TKTemperature ts;
// Defination  the Module:
#define VERSION 0
#define MOTOR 1
#define JOYSTICK 2
#define SERVO 3
#define ULTRASONICARDUINO 10
#define POTENTIONMETER 11
#define AVOIDSENSOR 12
#define TOUCHSENSOR 13
#define TEMPERATURESENSOR 14
#define GASSENSOR 15 
#define LINEFOLLOWER 16

// Created to variable.
#define GET 1// Read the Sensor
#define RUN 2 // Run the motion DC such as: motor, servo, ...
#define RESET 4 // Reset system when you press button.
#define START 5 // Start
void setup(){    
    Serial.begin(115200);
    Serial.print("Version: ");
    Serial.println(mVersion);
}
// ff 55 04 00 01 24 32
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
        if(index>20){
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
void readSerial(){
    isAvailable = false;
    if(Serial.available()>0){
        isAvailable = true;
        serialRead = Serial.read();
    } 
}
void writeBuffer(int index, unsigned char c) {
    buffer[index] = c;
}
unsigned char readBuffer(int index){
    return buffer[index];
}
// Get value to the system.
// Show to value of the byte;
union{
    byte byteVal[4];
    float floatVal;
    long longVal;
}val;
// Show to value of the Double;
union{
    byte byteVal[8];
    double doubleVal;
}valDouble;
// Show to value of the Short;
union{
    byte byteVal[2];
    short shortVal;
}valShort;
// Using the read function;
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
// Functions to write module.
void writeSerial(unsigned char c){
    //Serial.write(c);
}
void sendFloat(float value, int ten){ 
  String s = String(value);
  Serial.write("aa");
//    writeSerial('a');
//    writeSerial('a');
    for(int i =0; i < 5; i++){
         Serial.write(s.charAt(i));
      }
    Serial.write(';');
}

/*
ff 55 len idx action device port  slot  data a
0  1  2   3   4      5      6     7     8
*/
void parseData(){
    isStart = false;
    int idx  = readBuffer(3);
    int action = readBuffer(4);
    int device = readBuffer(5);
    switch (action){
    case GET: {
        readSensor(device);
        }
        break;
    case RUN: {
        runModule(device);
        }
        break;
    case RESET :{
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
// Functions of the write module;

void runModule(int device){
    int port = readBuffer(6);
    int pin = port;
    switch(device){
        case MOTOR: {            
        }
        break;
        /*
            ff 55 len idx action device speedM1  speedM2
            0  1  2   3   4      5      6          8
            ff  55  07  00  02  01  0x ff 0x 00
        */
        case JOYSTICK:{
            int leftSpeed = readShort(6);
            int rightSpeed = readShort(8);
            dc.reset(M1);
            dc.run(leftSpeed);
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
            Servo sv = servos[searchServoPin(pin)];
            if(angle >= 0 && angle <= 180){
                if(!sv.attached()){
                    sv.attach(pin);
                    }
                sv.write(angle);
                }         
            }
        break;
    }    
}
int  searchServoPin(int pin){
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
// Function of the sensors.
/**************************************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
      ff 55 04 00 01 0a 01  
***************************************************/
/*
    Ultrasonic:10
*/
void readSensor(int device){
    float value=0.0;
    int  port, pin;
    port  = readBuffer(6);
    pin = port; 
    switch (device){
    case ULTRASONICARDUINO:{
        if(usB.getPort() !=port){
            usB.reset(port);
            }
        String value =  String(usB.distanceCm());
        if(port == 2){
            Serial.write("aa2");
        } else if (port == 3){
            Serial.write("aa3");
        } else if (port == 5){
            Serial.write("aa5");
        } else if (port == 6){
            Serial.write("aa6");
        } else if (port == 7){
            Serial.write("aa7");
        } else if (port == 8){
            Serial.write("aa8");
            }
        for (int i = 0; i < 5; i++){
            Serial.write(value.charAt(i));
            } 
        }        
        break;
    case POTENTIONMETER:{
        if(generalDevice.getPort()!=port){
            generalDevice.reset(port);
            pinMode(generalDevice.pin2(),INPUT);
            }
        String value = String(generalDevice.aRead2());
        if(port == 2){
            Serial.write("pp2");
        } else if (port == 3){
            Serial.write("pp3");
        } else if (port == 5){
            Serial.write("pp5");
        } else if (port == 6){
            Serial.write("pp6");
        } else if (port == 7){
            Serial.write("pp7");
        } else if (port == 8){
            Serial.write("pp8");
            }
        for (int i = 0; i < 3; i++){
            Serial.write(value.charAt(i));
            } 
        }
        break;
    case AVOIDSENSOR:{
        if(avoidSensor.getPort() != port){
            avoidSensor.reset(port);
            }
        if(port == 2){
            Serial.write("av2");
        } else if (port == 3){
            Serial.write("av3");
        } else if (port == 5){
            Serial.write("av5");
        } else if (port == 6){
            Serial.write("av6");
        } else if (port == 7){
            Serial.write("av7");
        } else if (port == 8){
            Serial.write("av8");
            }          
        if (avoidSensor.Avoidtested() == 0){
            Serial.write('1');
        } else {
            Serial.write('0');
            } 
        }
        break;
    case TOUCHSENSOR:{
        if(touchSensor.getPort() != port){
            touchSensor.reset(port);
            }
        if(port == 2){
            Serial.write("at2");
        } else if (port == 3){
            Serial.write("at3");
        } else if (port == 5){
            Serial.write("at5");
        } else if (port == 6){
            Serial.write("at6");
        } else if (port == 7){
            Serial.write("at7");
        } else if (port == 8){
            Serial.write("at8");
            }
        if (touchSensor.touched() == 0){
            Serial.write('1');
        } else {
            Serial.write('0');
            }         
        }
        break;
    case TEMPERATURESENSOR:{
        int slot = readBuffer(7);
        if(ts.getPort()!=port||ts.getSlot()!=slot){
            ts.reset(port,slot);
            }
        String value = String(ts.temperature());
        if(port == 2){
            Serial.write("te2");
        } else if (port == 3){
            Serial.write("te3");
        } else if (port == 5){
            Serial.write("te5");
        } else if (port == 6){
            Serial.write("te6");
        } else if (port == 7){
            Serial.write("te7");
        } else if (port == 8){
            Serial.write("te8");
            }
        for (int i = 0; i < 5; i++){
            Serial.write(value.charAt(i));
            } 
        }
        break;
    case GASSENSOR:{
        if(GasSensor.getPort()!=port){
        GasSensor.reset(port);
        GasSensor.setpin(GasSensor.pin2(),GasSensor.pin1());
            }
        int16_t GasData; 
        GasData = GasSensor.readAnalog();
        //sendShort(GasData);
        }
        break;
    case LINEFOLLOWER:{
        if(generalDevice.getPort()!=port){
            generalDevice.reset(port);
            pinMode(generalDevice.pin1(),INPUT);
            pinMode(generalDevice.pin2(),INPUT);
            }
        String value = String(generalDevice.dRead1()*2+generalDevice.dRead2());
        if(port == 2){
            Serial.write("fw2");
        } else if (port == 3){
            Serial.write("fw3");
        } else if (port == 5){
            Serial.write("fw5");
        } else if (port == 6){
            Serial.write("fw6");
        } else if (port == 7){
            Serial.write("fw7");
        } else if (port == 8){
            Serial.write("fw8");
            }
        Serial.write(value.charAt(0));
        }
        break;
    }    
}
