String reply(String input){
  if(input.substring(0,DH_steps[0].length())==DH_steps[0]){
    String sh = "Ready to start";
    mySerial.write((const uint8_t*)sh.c_str(), sh.length());
    return sh;

  }else if(input.substring(0,DH_steps[1].length())==DH_steps[1]){
    server.set_pg();
    String PGpair = "P" + (String)server.get_prime()  + ",G" + (String)server.get_gen();
    Serial.println(PGpair);
    mySerial.write((const uint8_t*)PGpair.c_str(), PGpair.length());
    return PGpair;

  }else if(input.substring(0,DH_steps[2].length())==DH_steps[2]){
    server.set_pub();
    Serial.println(server.get_pub());
    String public_key = (String)server.get_pub();
    mySerial.write((const uint8_t*)public_key.c_str(), public_key.length());
    return public_key;

  }else if(input.substring(0,DH_steps[3].length())==DH_steps[3]){
    String client_public_str = input.substring(DH_steps[3].length()+1);
    int client_public_int = 0;
    for(int i=0;i<client_public_str.length();i++){
      client_public_int = client_public_int*10 + (int)client_public_str[i];
    }
    server.set_cli_pub(client_public_int);
    String msg = "Pub get";
    Serial.println(msg);
    mySerial.write((const uint8_t*)msg.c_str(), 7);
    server.set_sym_key();
    return msg;

  }else if(input.substring(0,DH_steps[4].length())==DH_steps[4]){
    if(server.verify_finish()){
      Serial.println("DH key exchange fininsh");
      return "Success";
    }
    return "Unsuccess";
    
  }else if(input.substring(0,indicate_steps[0].length())==indicate_steps[0]){
    String msg = "Server Hello";
    mySerial.write((const uint8_t*)msg.c_str(), msg.length());
    return msg;
  }
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