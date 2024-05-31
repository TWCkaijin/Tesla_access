String reply(String input,String work){
  
  if(work=="DH_steps"){
    String* ptr = work_flow[0];
    bool* btr = work_flow_check[0];
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){
      String msg = "Ready to start";
      return msg;

    }else if(check_bool_forward(btr,1)&&check_work(input,ptr,1)){
      server.set_pg();
      String PGpair = "P" + (String)server.get_prime()  + ",G" + (String)server.get_gen();
      Serial.println(PGpair);
      return PGpair;

    }else if(check_bool_forward(btr,2)&&check_work(input,ptr,2)){
      server.set_pub();
      Serial.println(server.get_pub());
      String public_key = (String)server.get_pub();
      return public_key;

    }else if(check_bool_forward(btr,3)&&check_work(input.substring(0,DH_steps[3].length()),ptr,3)){
      String client_public_str = input.substring(DH_steps[3].length()+1);
      int client_public_int = 0;
      for(int i=0;i<client_public_str.length();i++)client_public_int = client_public_int*10 + (int)client_public_str[i];
      server.set_cli_pub(client_public_int);
      String msg = "Pub get";
      Serial.println(msg);
      server.set_sym_key();
      return msg;

    }else if(check_bool_forward(btr,4)&&check_work(input,ptr,4)){
      if(server.verify_finish()){
        return "Success";
      }
      return "Unsuccess";

    }
  }
  

  if(work=="indicate_steps"){
    String* ptr = work_flow[1];
    bool* btr = work_flow_check[1];
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){
      String msg = "Server Hello";
      return msg;

    }else if(check_bool_forward(btr,1)&&check_work(input,ptr,1)){
      String msg = "ID:"+server.get_indicate();
      return msg;

    }else if(check_bool_forward(btr,2)&&check_work(input,ptr,2)){
      String msg = "Indicate finish";
      return msg;

    }
  }

  if(work=="attestation_steps"){
    String* ptr = work_flow[2];
    bool* btr = work_flow_check[2];
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){
      String msg = "Att ready";
      return msg;
    }else if(check_bool_forward(btr,1)&&check_work(input,ptr,1)){
      if(server.verify_attestation(1,input.substring(ptr[1].length()))){
        return "Success, count=" + (String)server.count;
      }else{
        btr[0]=false,btr[1]=false;
        return "Failed, stage reset";
      }
    }
  }
}

bool check_work(String input,String list[],int index){
  if(input==list[index]){
    return true;
  }
  return false;
}

bool check_bool_forward(bool list[],int index){
  for(int i=0;i<index;i++){
    if(list[i]==false){
      return false;
    }
  }
  return true;
}

void cmd_or_msg(String input){
  if(input[0]=='A'&&input[1]=='T'){
    mySerial.println(input);
    Serial.print("cmd sent: ");
    Serial.println(input);
  }else{
    sendCommand(input);
  }
}


void sendCommand(String cmd) {
  mySerial.write((const uint8_t*)cmd.c_str(), cmd.length());
  Serial.print("UTF-8 Message Sent: ");
  Serial.println(cmd);
}