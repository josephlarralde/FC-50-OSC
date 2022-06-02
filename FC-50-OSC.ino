#include <SPI.h>
#include <Ethernet.h>

#include <ArdOSC.h>

byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte myIp[]  = { 192, 168, 0, 123 };
int serverPort = 10000;

byte targetIp[] = {192, 168, 0, 124};
int destPort = 12000;

int led1Pin = 14;
int led2Pin = 15;
int led3Pin = 16;
int led4Pin = 17;
int led5Pin = 19;
int led6Pin = 18;
int led7Pin = 20;

int switch1Pin = 31;
int switch2Pin = 32;
int switch3Pin = 33;
int switch4Pin = 34;
int switch5Pin = 35;
int switchAPin = 30;
int switches[6];

int footSensorPin = A7;

OSCServer server;
OSCClient client;

void setup(){ 
 int i;
 
 //Serial.begin(19200);
 
 for(i=0;i<6;i++) {
   switches[i] = 0;
 }
 
 Ethernet.begin(myMac ,myIp); 
 server.begin(serverPort);
 
 //set callback function & oscaddress
 server.addCallback("/fc50/led/1",&led1func);
 server.addCallback("/fc50/led/2",&led2func);
 server.addCallback("/fc50/led/3",&led3func);
 server.addCallback("/fc50/led/4",&led4func);
 server.addCallback("/fc50/led/5",&led5func);
 server.addCallback("/fc50/led/6",&led6func);
 server.addCallback("/fc50/led/7",&led7func);
 
 pinMode(led1Pin, OUTPUT);  
 pinMode(led2Pin, OUTPUT);  
 pinMode(led3Pin, OUTPUT);  
 pinMode(led4Pin, OUTPUT);  
 pinMode(led5Pin, OUTPUT);  
 pinMode(led6Pin, OUTPUT);  
 pinMode(led7Pin, OUTPUT);  
 
 pinMode(switch1Pin, INPUT);
 pinMode(switch2Pin, INPUT);
 pinMode(switch3Pin, INPUT);
 pinMode(switch4Pin, INPUT);
 pinMode(switch5Pin, INPUT);
 pinMode(switchAPin, INPUT);
 
 digitalWrite(led6Pin, HIGH);
}
  
void loop() {
  
  int i;
  int value, flag;
  OSCMessage newMes;
  
  if(server.aviableCheck()>0){
    // Serial.println("alive! ");
    delay(5);
  }
  
  //for(i=0; i<2; i++) {

    flag = 0;
    value = digitalRead(switch1Pin);
    if (value == HIGH && switches[0] == 0) {
      switches[0] = 1;
      flag = 1;
    }
    if (value == LOW && switches[0] == 1) {
      switches[0] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/1");
      newMes.addArgInt32(1-switches[0]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    flag = 0;
    value = digitalRead(switch2Pin);
    if (value == HIGH && switches[1] == 0) {
      switches[1] = 1;
      flag = 1;
    }
    if (value == LOW && switches[1] == 1) {
      switches[1] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/2");
      newMes.addArgInt32(1-switches[1]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    flag = 0;
    value = digitalRead(switch3Pin);
    if (value == HIGH && switches[2] == 0) {
      switches[2] = 1;
      flag = 1;
    }
    if (value == LOW && switches[2] == 1) {
      switches[2] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/3");
      newMes.addArgInt32(1-switches[2]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    flag = 0;
    value = digitalRead(switch4Pin);
    if (value == HIGH && switches[3] == 0) {
      switches[3] = 1;
      flag = 1;
    }
    if (value == LOW && switches[3] == 1) {
      switches[3] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/4");
      newMes.addArgInt32(1-switches[3]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    flag = 0;
    value = digitalRead(switch5Pin);
    if (value == HIGH && switches[4] == 0) {
      switches[4] = 1;
      flag = 1;
    }
    if (value == LOW && switches[4] == 1) {
      switches[4] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/5");
      newMes.addArgInt32(1-switches[4]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    flag = 0;
    value = digitalRead(switchAPin);
    if (value == HIGH && switches[5] == 0) {
      switches[5] = 1;
      flag = 1;
    }
    if (value == LOW && switches[5] == 1) {
      switches[5] = 0;
      flag = 1;
    }
    if (flag == 1) {
      newMes.setAddress(targetIp,destPort);
      newMes.beginMessage("/fc50/switch/6");
      newMes.addArgInt32(1-switches[5]);
      //send osc message
      //for(int i=0; i<3; i++) {
        client.send(&newMes);
      //}
    }
    delay(3);

    //*
    value = analogRead(footSensorPin);
    newMes.setAddress(targetIp,destPort);
    newMes.beginMessage("/fc50/footsensor");
    newMes.addArgInt32(value);
    //send osc message
    client.send(&newMes);
    //Serial.println(value);  
    //*/
  //}
}

// ________________ LEDS ___________________

void led1func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led1Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led1Pin, LOW);
  }
}

void led2func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led2Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led2Pin, LOW);
  }
}

void led3func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led3Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led3Pin, LOW);
  }
}

void led4func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led4Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led4Pin, LOW);
  }
}

void led5func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led5Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led5Pin, LOW);
  }
}

void led6func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led6Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led6Pin, LOW);
  }
}

void led7func(OSCMessage *_mes){
  int value = _mes->getArgInt32(0);
  if (value==1) {
    digitalWrite(led7Pin, HIGH);
  } else if (value==0) {
    digitalWrite(led7Pin, LOW);
  }
}
