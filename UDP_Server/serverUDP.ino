#include <WiFi.h>

const char* ssid     = "ONO_Z479";
const char* password = "D4BCA4A344D0GCD45AG0";
int status = WL_IDLE_STATUS;

char packetBuffer[255];

WiFiUDP server;

void setup()
{
    Serial.begin(115200);
    
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
    Serial.println("Signal strength: ");
    Serial.println(WiFi.RSSI());
    
    server.begin(4015);

}

void loop(){  
 int packetSize = server.parsePacket();
 
  if(packetSize)
  {
    int len = server.read(packetBuffer, 255);
    if(len > 0)
    {
        packetBuffer[len] = 0;
    }
    Serial.println(packetBuffer);
  }
}
