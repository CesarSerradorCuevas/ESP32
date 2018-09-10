#include <WiFi.h>

const char* ssid     = "ONO_Z479";
const char* password = "D4BCA4A344D0GCD45AG0";
int status = WL_IDLE_STATUS;
int ledPin = 27;
String inData;
int inDataToInt;

WiFiServer server(4015);
WiFiClient client;

int freq = 5000;
int ledChannel = 0; //0 to 15
int resolution = 8; //1 to 16 bits. 8 = 255

void setup()
{
    Serial.begin(115200);
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin, ledChannel);      // set the LED pin mode
    
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
 client = server.available();   // listen for incoming clients
 
  if (client) { // Is there a client?
    Serial.println("New Client.");           
                                            
    while (client.connected()) { // Is client connected?           
      if (client.available()) { // Are there bytes to read from the client?
        String data = client.readStringUntil('\n');          
        inDataToInt = data.toInt();
        Serial.println(inDataToInt);
        ledcWrite(ledChannel, inDataToInt);           
      }
    }
    
    client.stop(); // Close the connection
    Serial.println("Client Disconnected.");
  }
}