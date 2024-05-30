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
        generator = random(20);
        bool flag = true;
        while(flag){
          prime = random(1000);
          flag = !is_prime(prime);
          Serial.println(prime);
        } 

      }
    }

    void set_pub(){
      if(pub==-1&&prime!=-1&&generator!=-1){
        private_key = random(10);
        pub = ((long long)pow(generator,private_key))%prime;
        Serial.println("Pub set");
      }else {
        return;
      }
    }

    void set_sym_key(){
      if(sym_key==-1&&pub!=-1&&cli_pub!=-1){
        sym_key = ((long long)pow(cli_pub,private_key)) % prime;
      }

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



  private :
    int generator;
    int prime;
    int private_key;
    int pub;
    int sym_key;
    int cli_pub;
    char car_id[10];
};


#endif