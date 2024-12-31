#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ut-iot";   // Your Wi-Fi SSID
const char* password = "<Put_Wi-Fi-Here>"; // Your Wi-Fi password
const bool FORWARD = true;
const bool BACKWARD = false;

WebServer server(80);

const int GPIO1 = 32;
const int GPIO2 = 33;
const int GPIO3 = 25;
const int GPIO4 = 26;

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Control the Motors</h1>";
  html += "<p>Use the W, A, S, D keys to control the motors.</p>";
  html += "<script>";
  html += "var pressed = false;";
  html += "document.addEventListener('keydown', function(event) { "
          "if (!pressed && event.key === 'w') { pressed=true;fetch('/forward'); } "
          "if (!pressed && event.key === 's') { pressed=true;fetch('/backward'); } "
          "if (!pressed && event.key === 'a') { pressed=true;fetch('/left'); } "
          "if (!pressed && event.key === 'd') { pressed=true;fetch('/right'); } });";
  html += "document.addEventListener('keyup', function(event) { "
          "pressed = false;"
          "if (['w', 's', 'a', 'd'].includes(event.key)) { fetch('/stop'); } });";
  html += "</script>";
  html += "</body></html>";
 
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(GPIO1, OUTPUT);
  pinMode(GPIO2, OUTPUT);
  pinMode(GPIO3, OUTPUT);
  pinMode(GPIO4, OUTPUT);
 
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO3, LOW);
  digitalWrite(GPIO4, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
 
  // Serve the web page
  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, forward);
  server.on("/backward", HTTP_GET, backward);
  server.on("/left", HTTP_GET, left);
  server.on("/right", HTTP_GET, right);
  server.on("/stop", HTTP_GET, stopMotors);
  server.begin();
  Serial.println("HTTP server started");
  // Print the IP address
  Serial.print("ESP32 Web Server IP Address: ");
  Serial.println(WiFi.localIP());
}

void forward() {
  digitalWrite(GPIO1, HIGH);
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO3, HIGH);
  digitalWrite(GPIO4, LOW);
}

void backward() {
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, HIGH);
  digitalWrite(GPIO3, LOW);
  digitalWrite(GPIO4, HIGH);
}

void left() {
  digitalWrite(GPIO1, HIGH);
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO3, LOW);
  digitalWrite(GPIO4, HIGH);
}

void right() {
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, HIGH);
  digitalWrite(GPIO3, HIGH);
  digitalWrite(GPIO4, LOW);
}

void stopMotors() {
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO3, LOW);
  digitalWrite(GPIO4, LOW);
}
