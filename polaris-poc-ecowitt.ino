#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

#define AP_SSID "Polaris-POC"
#define AP_PWD "20241116"

#define SERVER_PORT 2024
#define SERVER_PATH "/data/report/"

WebServer server(SERVER_PORT);

void handleEcoWitt();

void setup() {
    Serial.begin(115200);
    delay(1000);

    if (!WiFi.softAP(AP_SSID, AP_PWD)) {
        log_e("Soft AP creation failed.");
        while (1);
    }

    IPAddress myIP = WiFi.softAPIP();
    Serial.printf("ecowitt server address: http://%s:%d%s\n", myIP.toString().c_str(), SERVER_PORT, SERVER_PATH);

    server.on(SERVER_PATH, handleEcoWitt);
    server.begin();
}

void loop() {
    server.handleClient();
}

void handleEcoWitt() {
    for (int i = 0; i < server.args(); ++i) {
        Serial.printf("%s: %s\n", server.argName(i).c_str(), server.arg(i).c_str());
    }
    server.send(200, "OK");
}
