//TESLA

#include <SoftwareSerial.h>

// 定义AT-09连接的引脚
#define RX_PIN 2
#define TX_PIN 3

// 初始化SoftwareSerial对象
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // 初始化AT-09串口
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }

  if (Serial.available()) {
    char c = Serial.read();
    mySerial.write(c);
  }
}
