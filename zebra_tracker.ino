Adafruit_GPS GPS;
PulseOximeter pox;


void setup() {
    // temperature
    pinMode(A1, INPUT);
    // Vitals
    pinMode(2, INPUT);
    // Air Quality
    pinMode(A2, INPUT);
    pinMode(8, INPUT);
    Serial.begin(9600);


    // Networking
    pinMode(0, OUTPUT);
}




void loop() {
    // Temp
    float temp = analogRead(A1) / 1023.0 * 5.0 * 100.0;


    // GPS
    string gpsResult = GPS.read();


    string spO2_res = "";
    string hb_res = "";
    // Vitals
    if (pox.begin()) {
        spO2_res = pox.getSpO2();
        hb_res = pox.getHeartRate();
    }


    // Air Quality
    int analogResult = analogRead(A2);


    string message = "{\"temp\":" + to_string(temp)
                 + ",\"gps\":" + gpsResult 
                 + ",\"o2_pct:\":" + spO2_res 
                 + ",\"hb_res\":" + hb_res
                 + ",\"ppma\":" + to_string(analogResult) 
                 + "}";


    Serial.println(
        message
    );
    // Networking
    // Send
    Serial.sendMessage(0, message);


    // Print anything recieved
    if (Serial.availableMessage() != 0) {
        string mystr = Serial.readMessage();
        Serial.println("GOSSIP:" + mystr);
    }


    delay(20000);
}
