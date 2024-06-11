// APP
#include <SoftwareSerial.h>
#include <math.h>
#include "profile.h"
#include <Vector.h>
SoftwareSerial mySerial(2, 3); // RX, TX


String DH_steps[] = {"Start DH","PG req","Pub req","Pub sent:","DH done"};
bool* DH_steps_bool = new bool[5](0);

String indicate_steps[] = {"Client Hello","Indicate req","Indicate get"};
bool* indicate_steps_bool = new bool[3](0);

String attestation_steps[] = {"Start att","Att1 sent:","TokenG get","Att2 sent"};
bool*  attestation_steps_bool = new bool[5](0);

String token_give[] = {"Token give"};
bool* token_give_bool = new bool[1](0);

String work_name[] = {"DH_steps","indicate_steps","attestation_steps","token_give"};
String* work_flow[] = {DH_steps,indicate_steps,attestation_steps,token_give};
bool* work_flow_check[] = {DH_steps_bool,indicate_steps_bool,attestation_steps_bool,token_give_bool};
int work_length [] = {5,3,4,1};
const int MAX_WORK_FLOW = 4;

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
    String msg;
    msg = work_flow_verify(client);
    Serial.print("From BLE: ");
    Serial.println(client);
    Serial.println("Message sent:"+msg);
    mySerial.write((const uint8_t*)msg.c_str(), msg.length());
  }
}

String work_flow_verify(String input){
  for(int i=0;i<MAX_WORK_FLOW;i++){
    if(step_verify(work_flow[i],work_flow_check[i],work_length[i],input)){
      if(input.substring(0,10)=="Att1 sent:"){
        Serial.println("ATT sent command recieve");
      }
      return reply(input,work_name[i]);
    }
  }
  return "Invalid request";
}

bool step_verify(String step[],bool check[],int size,String current){
  if(current==step[0]){
    check[0] = true;
    return true;
  }

  for(int i=1;i<size;i++){
    if(current.substring(0,step[i].length())==step[i] && check[i-1]==true){
      check[i] = true;
      return true;
    }
  }
  return false;
}