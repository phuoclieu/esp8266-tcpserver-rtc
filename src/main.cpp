#include <Arduino.h>

#include <ESP8266WiFi.h>

int port = 8888; //Port number
WiFiServer server(port);
int count = 0;
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
String _ssid = "Compass211"; 
String _password = "123456089";
void setup()
{
  Serial.begin(115200);

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(_ssid, _password) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.softAPIP());
  Serial.print(" on port ");
  Serial.println(port);
  Serial.printf("Stations connected to soft-AP = %d \n", WiFi.softAPgetStationNum());
}
void loop()
{
  WiFiClient client = server.available();

  if (WiFi.softAPgetStationNum() != count)
  {
    Serial.printf("Stations connected to soft-AP = %d \n", WiFi.softAPgetStationNum());
    count = WiFi.softAPgetStationNum();
  }
  if (client)
  {
    if (client.connected())
    {
      Serial.println("Client Connected");
    }

    while (client.connected())
    {
      /*
      while (client.available() > 0)
      {
        // read data from the connected client
        Serial.write(client.read());
      }
      //Send Data to connected client
      while (Serial.available() > 0)
      {
        client.write(Serial.read());
      }
      */
      String request = client.readStringUntil('\r');

      Serial.println(request);

      client.flush();
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}