#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "KFEKursova";
const char* password ="Kursova123";

// Web server
WiFiServer server(80);
String header;

// Store received text
String storedText = "";

// Morse code mapping
const char* morseTable[36] = {
  "01",      // A
  "1000",    // B
  "1010",    // C
  "100",     // D
  "0",       // E
  "0010",    // F
  "110",     // G
  "0000",    // H
  "00",      // I
  "0111",    // J
  "101",     // K
  "0100",    // L
  "11",      // M
  "10",      // N
  "111",     // O
  "0110",    // P
  "1101",    // Q
  "010",     // R
  "000",     // S
  "1",       // T
  "001",     // U
  "0001",    // V
  "011",     // W
  "1001",    // X
  "1011",    // Y
  "1100",    // Z
  "11111",   // 0
  "01111",   // 1
  "00111",   // 2
  "00011",   // 3
  "00001",   // 4
  "00000",   // 5
  "10000",   // 6
  "11000",   // 7
  "11100",   // 8
  "11110"    // 9
};

// Get Morse code for character
String charToMorse(char c) {
  if (c >= 'A' && c <= 'Z') {
    return morseTable[c - 'A'];
  } else if (c >= 'a' && c <= 'z') {
    return morseTable[c - 'a'];
  } else if (c >= '0' && c <= '9') {
    return morseTable[c - '0' + 26];
  } else {
    return "";  // skip unknown characters
  }
}

// void printMorse(String text) {
//   String morseOutput = "";
//   for (int i = 0; i < text.length(); i++) {
//     if (text[i] == ' ') {
//       morseOutput += "   "; // space between words
//     } else {
//       String code = charToMorse(text[i]);
//       if (code != "") {
//         morseOutput += code + " "; // space between letters
//       }
//     }
//   }
//   Serial.println("Morse Code:");
//   Serial.println(morseOutput);
// }
const int laserPin = 13;  // Change to your actual GPIO pin

void blinkDot() {
  digitalWrite(laserPin, HIGH);
  delay(200); // dot duration
  digitalWrite(laserPin, LOW);
  delay(200); // gap between symbols
}

void blinkDash() {
  digitalWrite(laserPin, HIGH);
  delay(600); // dash duration
  digitalWrite(laserPin, LOW);
  delay(200); // gap between symbols
}

void printMorse(String text) {
  Serial.println("Morse Code:");
  for (int i = 0; i < text.length(); i++) {
    if (text[i] == ' ') {
      delay(1400);  // word space
      continue;
    }

    String code = charToMorse(text[i]);
    Serial.print(code);
    Serial.print(" ");

    for (int j = 0; j < code.length(); j++) {
      if (code[j] == '0') {
        blinkDot();
      } else if (code[j] == '1') {
        blinkDash();
      }
    }
    delay(600); // space between letters
  }
  Serial.println();
}

void setup() {
  pinMode(laserPin, OUTPUT);
digitalWrite(laserPin, LOW); // Make sure laser is off initially

  Serial.begin(115200);
  WiFi.softAP(ssid,password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    unsigned long timeout = millis();
    String currentLine = "";
    header = "";
    Serial.println("New Client");

    while (client.connected() && millis() - timeout < 2000) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Handle request
            if (header.indexOf("GET /text?value=") >= 0) {
              int start = header.indexOf("GET /text?value=") + 16;
              int end = header.indexOf(" ", start);
              String rawText = header.substring(start, end);
              rawText.replace("+", " ");
              rawText.replace("%20", " ");
              storedText = rawText;
              Serial.println("Text received: " + storedText);
              printMorse(storedText);
            }

            // Send response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html><head><title>ESP32 Morse</title></head>");
            client.println("<body style='font-family:monospace; text-align:center;'>");
            client.println("<h2>Enter Text to Convert to Morse</h2>");
            client.println("<form action=\"/text\" method=\"get\">");
            client.println("<input type=\"text\" name=\"value\" style='font-size:20px;'>");
            client.println("<input type=\"submit\" value=\"Send\" style='font-size:20px;'>");
            client.println("</form>");
            client.println("<p><strong>Stored Text:</strong> " + storedText + "</p>");
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();
  }
}