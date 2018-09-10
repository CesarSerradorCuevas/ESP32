#include <WiFi.h>

const char* ssid     = "ONO_Z479";
const char* password = "D4BCA4A344D0GCD45AG0";
int status = WL_IDLE_STATUS;
int ledPin = 27;

WiFiServer server(4015);
WiFiClient client;

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);      

    delay(100);

    // We start by connecting to a WiFi network
    status = WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 client = server.available();  

  if (client) { // listen for incoming clients                            
    Serial.println("New Client.");           
                                            
    while (client.connected()) { // Is client connected?           
      if (client.available()) { // Are there bytes to read from the client?            
        char data = client.read();             
        Serial.write(data);                    
        switch(data){
          case '0':
            digitalWrite(ledPin, LOW);
            break;
          case '1':
            digitalWrite(ledPin, HIGH);
            break;
          
        }
      }
    }
    
    client.stop(); // Close the connection
    Serial.println("Client Disconnected.");
  }
}