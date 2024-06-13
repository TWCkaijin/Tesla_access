// APP
#include <SoftwareSerial.h>
#include <math.h>
#include "profile.h"
SoftwareSerial mySerial(2, 3); // RX, TX


String DH_steps[] = {"Start DH","PG req","Pub req","Pub sent:","DH done"}; //steps for DH
bool* DH_steps_bool = new bool[5](0); //bool array for DH

String indicate_steps[] = {"Client Hello","Indicate req","Indicate get"}; //steps for indicate
bool* indicate_steps_bool = new bool[3](0); //bool array for indicate

String attestation_steps[] = {"Start att","Att1 sent:","Att2 sent:"}; //steps for attestation
bool*  attestation_steps_bool = new bool[5](0); //bool array for attestation

String token_give[] = {"Token give"};
bool* token_give_bool = new bool[1](0);

String work_name[] = {"DH_steps","indicate_steps","attestation_steps","token_give"}; //name of work flow
String* work_flow[] = {DH_steps,indicate_steps,attestation_steps,token_give};//work flow pointer
bool* work_flow_check[] = {DH_steps_bool,indicate_steps_bool,attestation_steps_bool,token_give_bool};//work flow check
int work_length [] = {5,3,4,1}; //]length of each work flow
const int MAX_WORK_FLOW = 4;

profile server;
void setup() {
  int seed = analogRead(A0);
  randomSeed(seed);
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("mySerial Module Setup Complete");
}

void loop() {
  if (Serial.available()) {
    cmd_or_msg(Serial.readString());

  }
  
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

String work_flow_verify(String input){ //find if ant he message matches the work flow steps
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

bool step_verify(String step[],bool check[],int size,String current){ //check if any the message matches the step
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