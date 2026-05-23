#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <Wire.h>  //For I2C communication
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();
//Set webserver port number to 80
//AsyncWebSever server(80);
AsyncWebServer server(80);

const char* ssid = "ESP32_Hand";
const char* password = "12345678";

#define SERVOMIN 280
#define SERVOMAX 320
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}
String fingerNames[6] = {
  "Kleiner Finger",
  "Ringfinger",
  "Mittelfinger",
  "Zeigefinger",
  "Daumen",
  "Daumen_gelenk"
};
/**
 * Wait for WiFi connection, and, if not connected, reboot
 */
void waitForWiFiConnectOrReboot(bool printOnSerial = true) {
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    if (printOnSerial) {
      Serial.println("Wifi connecting...");
    }
    notConnectedCounter++;
    if (notConnectedCounter > 50) {  // Reset board if not connected after 5s
      if (printOnSerial) {
        Serial.println("Resetting due to Wifi not connecting...");
      }
      ESP.restart();
    }
  }
  if (printOnSerial) {
    // Print wifi IP addess
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
  
//wird aufgerufen sobald es im browser geöffnet wird
void handleRoot(AsyncWebServerRequest *request) {
  //HTML-Seite erstellen
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style> 
      body { font-family: Arial; text-align: center; }
      .slider { width: 80%; }
      button {
        padding: 10px;
        margin: 5px;
        font-size: 16px;
      }
    </style>
  </head>
  <body>
    <h2>ESP32 Handsteuerung</h2>
  )rawliteral";

  for (int i = 0; i < 6; i++) {
    html += "<p>" + fingerNames[i] + "</p>";
//Schiebe-Regler
    html += "<input type='range' min='180' max='360' value='270' class='slider' ";
    html += "oninput='send(" + String(i) + ", this.value)'><br>";
//Buttons
   // html += "<button onclick='slowUp(" + String(i) + ")'> 180° (2s)</button>";
   // html += "<button onclick='slowDown(" + String(i) + ")'> 0° (2s)</button>";
  }
//send-func sendet HTTP_Request an ESP32
  html += R"rawliteral(
    <script>
      function send(id, val) {
        fetch(`/set?servo=${id}&value=${val}`);
      }

      function slowUp(id) {
        fetch(`/slow?servo=${id}&dir=up`);
      }

      function slowDown(id) {
        fetch(`/slow?servo=${id}&dir=down`);
      }
    </script>
  </body>
  </html>
  )rawliteral";
//ESP32 schickt fertige HTML-Seite an den Browser
  request->send(200, "text/html", html);
}

void handleSet(AsyncWebServerRequest *request) {

  if (request->hasParam("servo") && request->hasParam("value")) {

    int servo = request->getParam("servo")->value().toInt();
    int value = request->getParam("value")->value().toInt();

    int pulse = angleToPulse(value);

    pca.setPWM(servo, 0, pulse);

    Serial.printf("Servo %d -> %d°\n", servo, value);
  }

  request->send(200, "text/plain", "OK");
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Wire.begin();
  pca.begin();
  pca.setPWMFreq(50);

  WiFi.softAP(ssid, password);

    Serial.println("Access Point gestartet!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

 /* server.on("/", handleRoot);
  server.on("/set", handleSet);*/
  server.on("/", HTTP_GET, handleRoot);
server.on("/set", HTTP_GET, handleSet);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //server.handleClient();
}
