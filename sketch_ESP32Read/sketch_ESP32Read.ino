#define RXD2 16
#define TXD2 17
#include <WiFi.h>
#include <WebSocketsServer.h>

void serialEvent();

int clientCount = 0;

// Replace with your network credentials
const char* ssid = "***********";
const char* password = "***********";
std::vector<int> clients;



WebSocketsServer webSocket = WebSocketsServer(443);


String splitString(String string, char deliniator, int index);

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
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
   auto serialValue = Serial2.readStringUntil('\n');
   auto waterValue = splitString(serialValue, ',', 1);
   auto soundValue = splitString(serialValue, ',', 0);

   
    for (int n : clients) {
        webSocket.sendTXT(n, "Water: " + waterValue + "\n Sound: " + soundValue);
    }
  
}

void onWebSocketEvent(uint8_t clientNum,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", clientNum);
      clients.erase(std::remove(clients.begin(), clients.end(), 8), clients.end());
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(clientNum);
        Serial.printf("[%u] Connection from ", clientNum);
        Serial.println(ip.toString());
        clients.push_back(clientNum);
      }
      break;

    //Text Message
    case WStype_TEXT:

      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", clientNum, payload);

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
