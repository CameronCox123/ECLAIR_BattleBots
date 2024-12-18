#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "utexas-iot";
const char* password = "153260095736g35923140";

// Set web server port number
WiFiServer server(80);

const int controlPin = 2;

void setup() {
  Serial.begin(115200);

  // Set pin 2 as output
  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW); // Initially LOW

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop(){
  // Check if a client has connected
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client connected.");
    String currentLine = "";

    // Read client request
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          // Handle keypress events
          if (currentLine.indexOf("GET /W_ON") >= 0) {
            digitalWrite(controlPin, HIGH);
            Serial.println("Pin 2 set to HIGH");
          }
          else if (currentLine.indexOf("GET /W_OFF") >= 0) {
            digitalWrite(controlPin, LOW);
            Serial.println("Pin 2 set to LOW");
          }

          // Send a simple HTTP response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html><body><h1>ESP32 Web Server</h1>");
          client.println("<script>");
          client.println("document.addEventListener('keydown', function(event) {");
          client.println("  if (event.key === 'w' || event.key === 'W') {");
          client.println("    fetch('/W_ON');");
          client.println("  }");
          client.println("});");
          client.println("document.addEventListener('keyup', function(event) {");
          client.println("  if (event.key === 'w' || event.key === 'W') {");
          client.println("    fetch('/W_OFF');");
          client.println("  }");
          client.println("});");
          client.println("</script>");
          client.println("</body></html>");
          client.println();
          break;
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}
