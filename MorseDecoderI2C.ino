#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;
const int threshold = 500;
const int sampleInterval = 10;

const int dotDuration = 200;
const int dashDuration = 600;
const int symbolGap = 200;
const int letterGap = 600;
const int wordGap = 1400;

String currentSymbol = "";
String currentMorse = "";
unsigned long lastChangeTime = 0;
bool lastState = false;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27. Change if yours is different.

struct MorseMap {
  const char* code;
  char letter;
};

MorseMap morseTable[] = {
  {"01", 'A'}, {"1000", 'B'}, {"1010", 'C'}, {"100", 'D'}, {"0", 'E'}, {"0010", 'F'},
  {"110", 'G'}, {"0000", 'H'}, {"00", 'I'}, {"0111", 'J'}, {"101", 'K'}, {"0100", 'L'},
  {"11", 'M'}, {"10", 'N'}, {"111", 'O'}, {"0110", 'P'}, {"1101", 'Q'}, {"010", 'R'},
  {"000", 'S'}, {"1", 'T'}, {"001", 'U'}, {"0001", 'V'}, {"011", 'W'}, {"1001", 'X'},
  {"1011", 'Y'}, {"1100", 'Z'}, {"11111", '0'}, {"01111", '1'}, {"00111", '2'}, {"00011", '3'},
  {"00001", '4'}, {"00000", '5'}, {"10000", '6'}, {"11000", '7'}, {"11100", '8'}, {"11110", '9'}
};

char decodeMorse(String code) {
  for (MorseMap m : morseTable) {
    if (code == m.code) return m.letter;
  }
  return '?';
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Morse Decoder");

  delay(1000);
  lcd.clear();
  Serial.println("Ready to receive Morse...");
}

void loop() {
  static bool isLight = false;
  static unsigned long lastTransitionTime = millis();
  static unsigned long lastActivityTime = millis();

  int lightLevel = analogRead(sensorPin);
  bool lightDetected = lightLevel > threshold;

  if (lightDetected != isLight) {
    unsigned long now = millis();
    unsigned long duration = now - lastTransitionTime;
    lastTransitionTime = now;
    lastActivityTime = now;

    if (isLight) {
      if (duration < dotDuration + 100) {
        currentSymbol += '0';
      } else if (duration < dashDuration + 200) {
        currentSymbol += '1';
      }
    } else {
      if (duration >= wordGap - 200) {
        if (currentSymbol.length() > 0) {
          char decoded = decodeMorse(currentSymbol);
          appendChar(decoded);
          currentSymbol = "";
        }
        appendChar(' ');
      } else if (duration >= letterGap - 200) {
        if (currentSymbol.length() > 0) {
          char decoded = decodeMorse(currentSymbol);
          appendChar(decoded);
          currentSymbol = "";
        }
      }
    }

    isLight = lightDetected;
  }

  if (currentSymbol.length() > 0 && millis() - lastActivityTime > letterGap + 200) {
    char decoded = decodeMorse(currentSymbol);
    appendChar(decoded);
    currentSymbol = "";
    lastActivityTime = millis();
  }

  delay(sampleInterval);
}

void appendChar(char c) {
  Serial.print(c);
  currentMorse += c;

  static int lcdPos = 0;
  static int row = 0;

  lcd.setCursor(lcdPos, row);
  lcd.print(c);

  lcdPos++;
  if (lcdPos >= 16) {
    lcdPos = 0;
    row = (row + 1) % 2;
    lcd.setCursor(0, row);
    lcd.print("                "); // Clear next row
  }
}


