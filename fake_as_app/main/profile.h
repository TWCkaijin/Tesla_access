#ifndef PROFILE_H
#define PROFILE_H

class profile{
  public:
    profile(){
      pub=-1;
      private_key=-1;
      prime=-1;
      generator=-1;
      cli_pub = -1;
      sym_key = -1;
      car_id = "1234567890";
      access_token = -1;
      count = 0;
      att=-1;
      access_token = random(9)+1;
    }

    int count;



    String respond_tokenG(){
      String temp = (String)(access_token*sym_key);
      Serial.println("Token G gened:"+temp);
      return temp;
    }

    bool verify_attestation(int stage,String input){
      long msg=0;
      for(int i=0;i<input.length();i++){
        msg = msg*10+(int)input[i]-48;
      }
      Serial.println("1");
      count = stage;
      if(stage==2){
        long temp = msg/sym_key/cli_pub;
        if(access_token==temp/sym_key){
          return true;
        }else{
          Serial.println("Pair check:");
          Serial.println(temp);
          Serial.println(access_token);
        }
        
      }else if(stage==1){
        att = msg/sym_key;
        Serial.print("att:");
        Serial.println(att);
        return true;
      }
      return false;
      //msg = AES_GCM(a,S,count,null)
      //msg = AES_GCM(b,S,count,G)
    }

    bool is_prime(int num){
      for(int i=2;i<=sqrt(num);i++){
        if(num%i==0){
          return false;
        }
      }
      return true;
    }

    bool verify_finish(){
      if(prime!=-1&&generator!=-1&&private_key!=-1&&pub!=-1&&sym_key!=-1&&cli_pub!=-1){
        return true;
      }
      return false;
    }

    void set_pg(){
      if(prime==-1&&generator==-1){
        generator = random(8)+2;
        bool flag = true;
        while(flag){
          prime = random(93)+7;
          flag = !is_prime(prime);
        } 
      }
    }

    void set_pub(){
      if(pub==-1&&prime!=-1&&generator!=-1){
        private_key = random(3)+2;
        long temp = generator;
        for(int i=0;i<private_key;i++){
          temp *= generator;
        }
        pub = (temp%prime);

        Serial.print("Private");
        Serial.println(private_key);
        Serial.print("Pub set");
        Serial.println(pub);
      }else {
        Serial.println("Pub set error");
      }
    }

    void set_sym_key(){
      if(sym_key==-1&&pub!=-1&&cli_pub!=-1){

        long  temp = cli_pub;
        for(int i=0;i<private_key;i++){
          temp*= cli_pub;
        }
        sym_key = (long)(temp%prime);
      }else{
        Serial.print(sym_key);
        Serial.print(pub);
        Serial.print(cli_pub);

        Serial.println("sym key set error");
      }
      Serial.print("Private: ");
      Serial.println(private_key);
      Serial.print("Sym_key: ");
      Serial.println(sym_key);
    }

    void set_cli_pub(int a){
      cli_pub = a;
    }

    int get_private_key(){
      return private_key;
    }

    int get_pub(){
      return pub;
    }

    int get_gen(){
      return generator;
    }

    int get_prime(){
      return prime;
    }

    int get_sym_key(){
      return sym_key;
    }

    String get_indicate(){
      return car_id;
    }

  private :
    long generator;
    long prime;
    long private_key;
    long pub;
    long sym_key;
    long cli_pub;
    long access_token;
    long att;
    String car_id;
};


#endif