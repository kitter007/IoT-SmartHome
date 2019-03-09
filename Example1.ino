#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "";
const char* password = "";

#define APPID   ""
#define KEY     ""
#define SECRET  ""
#define ALIAS   ""

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    char strState[msglen];
    for (int i = 0; i < msglen; i++){
        strState[i] = (char)msg[i];
        Serial.print((char)msg[i]);
    }
    Serial.println((char *)msg);
    String stateStr = String(strState).substring(0,msglen);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup() {
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
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
}

void loop() {
    if (microgear.connected()) {
        Serial.println("connected");
        microgear.loop();
    } else {
        Serial.println("connection lost, reconnect...");
    }
    delay(100);
}
