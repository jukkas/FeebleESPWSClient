/* 
    Minimal example of using FeebleESPWSClient.
    Connects to a demo Websocket server, sends a message.
    Prints out messages from server.
*/

#include "fwsc.h"

Fwsc ws;

void setup() {
    Serial.begin(115200);

    // WiFi-startup
    char ssid[] = "YourWiFiName";
    char pass[] = "YourWiFiPasword";
    Serial.println("Starting up!");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    Serial.println("WiFi connected");

    auto cb = [&](WSEvent type, uint8_t * payload) {
        switch (type)
        {
        case WSEvent::error:
            Serial.printf_P(PSTR("WS Got error\n"));
            break;
        case WSEvent::disconnected:
            Serial.printf_P(PSTR("WS Got disconnected%s\n"), ws.isConnected ? " library bug!!!":"");
            break;
        case WSEvent::connected:
            Serial.printf_P(PSTR("WS Got connected%s\n"), ws.isConnected ? "": " library bug!!!");
            ws.sendtxt("Hello Websocket server, ESP here!");
            break;
        case WSEvent::text:
            Serial.printf_P(PSTR("WS Got text '%s'\n"), (char *)payload);
            break;
        
        default:
            Serial.printf_P(PSTR("WS Got unimplemented\n"));
            break;
        }
    };
    ws.setCallback(cb);
    ws.connect("echo.websocket.org", 443, "/");
}

void loop() {
    ws.loop();
}
