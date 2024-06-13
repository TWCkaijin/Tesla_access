## 使用方法:
  1. 安裝Arduino IDE 或 VScode 的 Arduino 套件
  2. 安裝使用的套件: SoftwareSerial
  3. 分為組程式，Tesla 是真特斯拉，請將他上傳到真特斯拉模擬裝置上，Fake_as_tesla 是攻擊者連線真用戶的裝置，請將他上傳到假特斯拉裝置上
  4. 在兩支手機上安裝 nRF connect，並且分別連線上裝置即可開始。
  5. 搭配DH_outer生成及記憶att、DH公鑰私鑰。(該程式為一個偽用戶端)
  DH 指令順序: "Start DH","PG req","Pub req","Pub sent:","DH done"
  

  Indicate 指令順序: "Client Hello","Indicate req","Indicate get"


  Attestation 指令順序: "Start att","Att1 sent:","Att2 sent:"

  上述指令若各自沒有按照順序輸入或錯誤輸入，會使系統回傳"Invalid request"
