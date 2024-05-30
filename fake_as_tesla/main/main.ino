#include <SoftwareSerial.h>
#include <math.h>
#include "profile.h"
SoftwareSerial mySerial(2, 3); // RX, TX
String DH_steps[] = {"Start DH","PG req","Pub req","Pub sent:","DH done"};
String indicate_steps[] = {"Client Hello","indicate req",""};
profile server;
void setup() {
  // 开启硬件串口和软件串口
  int seed = analogRead(A0);
  randomSeed(seed);
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("mySerial Module Setup Complete");
}

void loop() {
  // 检查是否有来自串口监视器的输入
  if (Serial.available()) {
    cmd_or_msg(Serial.readString());

  }

  // 检查是否有来自BLE模块的输入
  if (mySerial.available()) {
    String client = mySerial.readString();
    String msg = reply(client);
    Serial.print("From BLE: ");
    Serial.println(client);
    Serial.println("Message sent:"+msg);
  }
}


