/*
    REMOTE DISPLAY FOR CROWDING ALERT SYSTEM
    Runs on M5STACK MATRIX
*/

#include "M5Atom.h"

#define PORT       7778

#include <WiFi.h>
#include <AsyncUDP.h>

// Replace these with your WiFi network settings
const char* ssid = "<your wifi SSID>";
const char* password = "<your wifi password>";

AsyncUDP udp;

float people = 0;
float light_target = 0.0;   // 0 to 3.0
float light_state = 3.0;    // 0 to 3.0

void setup()
{
  M5.begin(true, false, true);
  delay(50);

  Serial.begin(115200);

  Serial.println("Starting...");

  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP().toString().c_str());
  if(udp.listen(PORT)) {
        Serial.print("UDP Listening on IP: ");
        Serial.print(WiFi.localIP());
        Serial.print(":");
        Serial.println(PORT);
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: [");
            int length = packet.length();
            for (int i = 0; i < length; i++)
            {
              Serial.print(packet.data()[i]);
              Serial.print(" ");
            }
            Serial.print("]   ");

            people = packet.data()[1] / 10.0;
            Serial.println(people);

            light_target = people;
        });
    }
}

void set_level(int led, int color)
{
  for (int i = 0; i < 25; i++)
  {
     M5.dis.drawpix(i, color);
  }
  M5.update();
}


void head_to_target() {
  float diff = fabs(light_state - light_target);

  if (diff > 0.1f)
  {
    light_state += (light_target - light_state) * 0.01;

    float green_delta = light_state < 0 ? 0.0 : (light_state - 0.0);
    float blue_delta = light_state - 1.5;
    float red_delta = light_state > 3.0 ? 0.0 : (3.0 - light_state);

    int green = 255 - 256 * 0.5 * green_delta * green_delta;  // green centered on 0.0
    int blue = 255 - 256 * 0.5 * blue_delta * blue_delta;     // blue centered on 1.5
    int red = 255 - 256 * 0.5 * red_delta * red_delta;        // red centered on 3.0

    if (green < 0) green = 0;
    if (green > 255) green = 255;
    if (blue <0) blue = 0;
    if (blue > 255) blue = 255;
    if (red < 0) red = 0;
    if (red > 255) red = 255;

    int color = (green << 16) + (red << 8) + blue;
    //Serial.print(color);
    for (int i = 0; i < 25; i++)
    {
       M5.dis.drawpix(i, color);
    }
    M5.update();
    // TODO: Add flashing for extreme numbers
  }
}

// During startup paints a wave of colors on the screen

int demo_count = 4000;

void demo(){
  int i = demo_count--;
  light_target = 1.5 + 1.5 * sin(i * 6.28 / 2000);
}

void loop() {
  if (demo_count >= 0){
    demo();
  }
  head_to_target();
  delay(5);
}
