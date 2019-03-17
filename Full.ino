#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "";
const char* password = "";

#define APPID   "SmartHomeKMUTNB"
#define KEY     "939z1vxSIM8ua6A"
#define SECRET  "FiT52qpRHVb9VpemQIbjOdCyK"
#define ALIAS   "smartplug"
#define CH1 5
#define CH2 4
#define CH3 0
#define CH4 2

WiFiClient client;
MicroGear microgear(client);

void MsgCallback(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    char strState[msglen];
    for (int i = 0; i < msglen; i++){
        strState[i] = (char)msg[i];
    }
    Serial.println((char *)msg);
    String stateStr = String(strState).substring(0,msglen);
    if(stateStr=="CH1_ON"){
      digitalWrite(CH1,HIGH);
      microgear.publish("/led/state1","1");
    }
    if(stateStr=="CH1_OFF"){
      digitalWrite(CH1,LOW);
      microgear.publish("/led/state1","0");
    }
    
    if(stateStr=="CH2_ON"){
      digitalWrite(CH2,HIGH);
      microgear.publish("/led/state2","1");
    }
    if(stateStr=="CH2_OFF"){
      digitalWrite(CH2,LOW);
      microgear.publish("/led/state2","0");
    }

    if(stateStr=="CH3_ON"){
      digitalWrite(CH3,HIGH);
      microgear.publish("/led/state3","1");
    }
    if(stateStr=="CH3_OFF"){
      digitalWrite(CH3,LOW);
      microgear.publish("/led/state3","0");
    }

    if(stateStr=="CH4_ON"){
      digitalWrite(CH4,HIGH);
      microgear.publish("/led/state4","1");
    }
    if(stateStr=="CH4_OFF"){
      digitalWrite(CH4,LOW);
      microgear.publish("/led/state4","0");
    }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup() {
    microgear.on(MESSAGE,MsgCallback);
    microgear.on(CONNECTED,onConnected);
    pinMode(CH1,OUTPUT);
    pinMode(CH2,OUTPUT);
    pinMode(CH3,OUTPUT);
    pinMode(CH4,OUTPUT);
    Serial.begin(9600);
    Serial.println("Starting...");
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); 
        
    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
    digitalWrite(CH1,LOW);
    digitalWrite(CH2,LOW);
    digitalWrite(CH3,LOW);
    digitalWrite(CH4,LOW);
    microgear.publish("/led/state1","0");
    microgear.publish("/led/state2","0");
    microgear.publish("/led/state3","0");
    microgear.publish("/led/state4","0");
}

void loop() {
    if (microgear.connected()) {
        Serial.println("connected");
        microgear.loop();
    } else {
        Serial.println("connection lost");
        setup();
    }
    delay(100);
}
