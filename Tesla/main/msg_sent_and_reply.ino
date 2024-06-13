String reply(String input,String work){
  
  if(work=="DH_steps"){
    String* ptr = work_flow[0]; // point to DH_steps
    bool* btr = work_flow_check[0]; // point to DH_steps_bool
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){ // Ready to start
      String msg = "Ready to start";
      return msg;

    }else if(check_bool_forward(btr,1)&&check_work(input,ptr,1)){ // Get prime and generator
      server.set_pg();
      String PGpair = "P" + (String)server.get_prime()  + ",G" + (String)server.get_gen();
      Serial.println(PGpair);
      return PGpair;

    }else if(check_bool_forward(btr,2)&&check_work(input,ptr,2)){ // Get public key
      server.set_pub();
      String public_key = (String)server.get_pub();
      return public_key;

    }else if(check_bool_forward(btr,3)&&check_work(input.substring(0,DH_steps[3].length()),ptr,3)){ // Get client public key
      String client_public_str = input.substring(DH_steps[3].length(),input.length());
      int client_public_int = 0;
      for(int i=0;i<client_public_str.length();i++){
        client_public_int = client_public_int*10 + ((int)client_public_str[i]-48);
      }
      server.set_cli_pub(client_public_int);
      String msg = "Pub get";
      server.set_sym_key();
      return msg;

    }else if(check_bool_forward(btr,4)&&check_work(input,ptr,4)){ //  verify finish
      if(server.verify_finish()){
        return "Success";
      }
      return "Unsuccess";

    }
  }
  

  if(work=="indicate_steps"){
    String* ptr = work_flow[1];  // point to indicate_steps
    bool* btr = work_flow_check[1]; // point to indicate_steps_bool
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){ // Server Hello
      String msg = "Server Hello";
      return msg;

    }else if(check_bool_forward(btr,1)&&check_work(input,ptr,1)){ // Get indicate
      String msg = "ID:"+server.get_indicate();
      return msg;

    }else if(check_bool_forward(btr,2)&&check_work(input,ptr,2)){ // check finish
      String msg = "Indicate finish";
      return msg;

    }
  }

  if(work=="attestation_steps"){
    String* ptr = work_flow[2]; // point to attestation_steps
    bool* btr = work_flow_check[2]; // point to attestation_steps_bool
    if(check_bool_forward(btr,0)&&check_work(input,ptr,0)){ // Ready to start
      String msg = "Att ready";
      return msg;
    }else if(check_bool_forward(btr,1)&&check_work(input.substring(0,attestation_steps[1].length()),ptr,1)){ // Get attestation 1
      if(server.verify_attestation(1,input.substring(ptr[1].length()))){
        Serial.println("IN ATT verification 1");
        String msg = "Success, count=" + (String)server.count;
        mySerial.write((const uint8_t*)msg.c_str(), msg.length());
        
        delay(3000);
        return server.respond_tokenG();
      }else{
        btr[0]=false,btr[1]=false;
        Serial.println("ATT fail");
        delay(3000);
        return "Failed, ATT reset";
      }
    }else if(check_bool_forward(btr,2)&&check_work(input.substring(0,attestation_steps[2].length()),ptr,2)){ // Get attestation 2
      if(server.verify_attestation(2,input.substring(ptr[2].length()))){ // attestation 2 verification
        return "Access Granted";
      }else{
        btr[0]=false,btr[1]=false,btr[2]=false;
        Serial.println("ATT fail");
        delay(3000);
        return "Failed, ATT reset";
      }
    }
  }
  return "No command found";
}

bool check_work(String input,String list[],int index){ // check if the input is the same as the list
  if(input==list[index]){
    return true;
  }
  return false;
}

bool check_bool_forward(bool list[],int index){ // check if the bool list is all true before the index
  for(int i=0;i<index;i++){
    if(list[i]==false){
      return false;
    }
  }
  return true;
}

void cmd_or_msg(String input){ // check if the input is a command or a message
  if(input[0]=='A'&&input[1]=='T'){
    mySerial.write((const uint8_t*)input.c_str(), input.length());
  }else{
    sendCommand(input);
  }
}


void sendCommand(String cmd) { // send command to BLE
  mySerial.write((const uint8_t*)cmd.c_str(), cmd.length());
  Serial.print("UTF-8 Message Sent: ");
  Serial.println(cmd);
}