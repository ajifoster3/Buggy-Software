#define RXD2 16
#define TXD2 17
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>

bool stringComplete = false;
void serialEvent();
String serialValue;
String waterValue;
String soundValue;
std::vector<int> clients;
int clientCount = 0;

// Replace with your network credentials
const char* ssid = "BTWholeHome-8H6";
const char* password = "HqwUCtPTG4x7";



// Set web server port number to 80
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(443);


String splitString(String string, char deliniator, int index);


void onWebSocketEvent(uint8_t client_num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_num);
      clients.erase(std::remove(clients.begin(), clients.end(), 8), clients.end());
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("[%u] Connection from ", client_num);
        Serial.println(ip.toString());
        clients.push_back(client_num);
      }
      break;

    // Handle text messages from client
    case WStype_TEXT:

      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", client_num, payload);

      if ( strcmp((char *)payload, "forward") == 0 ) {
        Serial2.println("forward");
      }else if ( strcmp((char *)payload, "backward") == 0 ) {
        Serial2.println("backward");
      } else if ( strcmp((char *)payload, "left") == 0 ) {
        Serial2.println("left");
      } else if ( strcmp((char *)payload, "right") == 0 ) {
        Serial2.println("right");
      } else if ( strcmp((char *)payload, "stop") == 0 ) {
        Serial2.println("stop");
      } else if ( strcmp((char *)payload, "toggleWaterSensor") == 0 ) {
        Serial2.println("toggle");
      }else {
        Serial.println("[%u] Message not recognized");
      }
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}



void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
 if (Serial2.available())
        serialEvent();
   
  webSocket.loop();
  
}



String splitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void serialEvent() {
   serialValue = Serial2.readStringUntil('\n');
   waterValue = splitString(serialValue, ',', 1);
   soundValue = splitString(serialValue, ',', 0);

   
    for (int n : clients) {
        webSocket.sendTXT(n, "Water: " + waterValue + "\n Sound: " + soundValue);
    }
  
}
