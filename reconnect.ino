void reconnect(){
    microgear.on(MESSAGE,MsgCallback);
    microgear.on(CONNECTED,onConnected);
    Serial.println("connection lost, reconnect..."); 
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
