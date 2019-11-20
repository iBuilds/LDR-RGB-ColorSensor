#include <EEPROM.h>

#define Digit1 A3
#define Digit2 A2
#define Digit3 A1
#define Digit4 A0
#define LDR_PIN A4
#define Button_PIN A5
#define Calibrate_PIN 8
#define LED_PIN 13
#define LED_R 9
#define LED_G 10
#define LED_B 11

long Timer_Button = 0;
int num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int charector[] = {0x50, 0x3D, 0x7C, 0x40};  //RGB-
int Color_White[] = {0, 0, 0};
int Color_Black[] = {0, 0, 0};
int Color_Value[] = {0, 0, 0};
int Color_Set[] = {0, 0, 0};

void setup() {
  DDRD = 0xFF;
  pinMode(Digit1, OUTPUT);
  pinMode(Digit2, OUTPUT);
  pinMode(Digit3, OUTPUT);
  pinMode(Digit4, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(Button_PIN, INPUT_PULLUP);
  pinMode(Calibrate_PIN, INPUT_PULLUP);
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);

  Color_White[0] = EEPROM.read(0) * 2;
  Color_White[1] = EEPROM.read(1) * 2;
  Color_White[2] = EEPROM.read(2) * 2;
  Color_Black[0] = EEPROM.read(3) * 2;
  Color_Black[1] = EEPROM.read(4) * 2;
  Color_Black[2] = EEPROM.read(5) * 2;
  Color_Set[0] = EEPROM.read(6);
  Color_Set[1] = EEPROM.read(7);
  Color_Set[2] = EEPROM.read(8);

  for (int i = 255; i > 100; i --) {
    analogWrite(LED_R, i);
    delay(3);
  }
  for (int i = 100; i < 255; i ++) {
    analogWrite(LED_R, i);
    delay(3);
  }

  for (int i = 255; i > 100; i --) {
    analogWrite(LED_G, i);
    delay(3);
  }
  for (int i = 100; i < 255; i ++) {
    analogWrite(LED_G, i);
    delay(3);
  }

  for (int i = 255; i > 100; i --) {
    analogWrite(LED_B, i);
    delay(3);
  }
  for (int i = 100; i < 255; i ++) {
    analogWrite(LED_B, i);
    delay(3);
  }
}

void loop() {
  Check_Button();
  Read_Color();
  Check_Color_Set();
  Serial.begin(9600);
  Serial.print("R = ");
  Serial.println(int(Color_Value[0]));
  Serial.print("G = ");
  Serial.println(int(Color_Value[1]));
  Serial.print("B = ");
  Serial.println(int(Color_Value[2]));
  Serial.end();
  Show(0, Color_Value[0], 500);
  Show(1, Color_Value[1], 500);
  Show(2, Color_Value[2], 500);
}

void Calibrate() {
  PORTD = charector[3];
  digitalWrite(Digit1, 1);
  digitalWrite(Digit2, 1);
  digitalWrite(Digit3, 1);
  digitalWrite(Digit4, 1);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
  delay(5000);

  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
  delay(50);
  Color_White[0] = analogRead(LDR_PIN);
  EEPROM.write(0, Color_White[0] / 2);
  delay(50);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 0);
  digitalWrite(LED_B, 1);
  delay(50);
  Color_White[1] = analogRead(LDR_PIN);
  EEPROM.write(1, Color_White[1] / 2);
  delay(50);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 0);
  delay(50);
  Color_White[2] = analogRead(LDR_PIN);
  EEPROM.write(2, Color_White[2] / 2);
  delay(50);
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);

  delay(5000);

  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
  delay(50);
  Color_Black[0] = analogRead(LDR_PIN);
  EEPROM.write(3, Color_Black[0] / 2);
  delay(50);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 0);
  digitalWrite(LED_B, 1);
  delay(50);
  Color_Black[1] = analogRead(LDR_PIN);
  EEPROM.write(4, Color_Black[1] / 2);
  delay(50);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 0);
  delay(50);
  Color_Black[2] = analogRead(LDR_PIN);
  EEPROM.write(5, Color_Black[2] / 2);
  delay(50);
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);

  delay(2000);
}

void Read_Color() {
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
  delay(20);
  Color_Value[0] = map(analogRead(LDR_PIN), Color_Black[0], Color_White[0], 0, 255);
  if (Color_Value[0] < 0) {
    Color_Value[0] = 0;
  }
  else if (Color_Value[0] > 255) {
    Color_Value[0] = 255;
  }
  delay(10);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 0);
  digitalWrite(LED_B, 1);
  delay(20);
  Color_Value[1] = map(analogRead(LDR_PIN), Color_Black[1], Color_White[1], 0, 255);
  if (Color_Value[1] < 0) {
    Color_Value[1] = 0;
  }
  else if (Color_Value[1] > 255) {
    Color_Value[1] = 255;
  }
  delay(10);

  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 0);
  delay(20);
  Color_Value[2] = map(analogRead(LDR_PIN), Color_Black[2], Color_White[2], 0, 255);
  if (Color_Value[2] < 0) {
    Color_Value[2] = 0;
  }
  else if (Color_Value[2] > 255) {
    Color_Value[2] = 255;
  }
  delay(10);
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);
  digitalWrite(LED_B, 1);
}

void Show(int CHAR, int NUM, long TIMER) {
  long Timer = millis();
  int Before_Last_Number = NUM;
  int Last_Number = NUM;
  while (millis() - Timer < TIMER) {
    Check_Button();
    if (NUM < 10) {
      PORTD = charector[CHAR];
      digitalWrite(Digit1, 1);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 0);
      delay(10);
      PORTD = num[NUM];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 1);
      delay(10);
    }
    else if (NUM >= 10 && NUM < 100) {
      PORTD = charector[CHAR];
      digitalWrite(Digit1, 1);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 0);
      delay(7);
      PORTD = num[NUM / 10];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 1);
      digitalWrite(Digit4, 0);
      delay(7);
      for (Last_Number; Last_Number > 9; Last_Number -= 10) {}
      PORTD = num[Last_Number];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 1);
      delay(7);
    }
    else if (NUM >= 100 && NUM < 1000) {
      PORTD = charector[CHAR];
      digitalWrite(Digit1, 1);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 0);
      delay(5);
      PORTD = num[NUM / 100];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 1);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 0);
      delay(5);
      for (Before_Last_Number; Before_Last_Number > 99; Before_Last_Number -= 100) {}
      PORTD = num[Before_Last_Number / 10];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 1);
      digitalWrite(Digit4, 0);
      delay(5);
      for (Last_Number; Last_Number > 9; Last_Number -= 10) {}
      PORTD = num[Last_Number];
      digitalWrite(Digit1, 0);
      digitalWrite(Digit2, 0);
      digitalWrite(Digit3, 0);
      digitalWrite(Digit4, 1);
      delay(5);
    }
  }
  digitalWrite(Digit1, 0);
  digitalWrite(Digit2, 0);
  digitalWrite(Digit3, 0);
  digitalWrite(Digit4, 0);
}

void Check_Button() {
  bool Button_Value = !digitalRead(Button_PIN);
  bool Calibrate_Value = !digitalRead(Calibrate_PIN);

  if (Calibrate_Value == 1) {
    Calibrate();
  }
  if (Button_Value == 0) {
    Timer_Button = millis();
  }
  else if (Button_Value == 1 && millis() - Timer_Button > 5000) {
    while (1) {
      PORTD = charector[3];
      digitalWrite(Digit1, 1);
      digitalWrite(Digit2, 1);
      digitalWrite(Digit3, 1);
      digitalWrite(Digit4, 1);
      Read_Color();
      Color_Set[0] = Color_Value[0];
      EEPROM.write(6, Color_Value[0]);
      Color_Set[1] = Color_Value[1];
      EEPROM.write(7, Color_Value[1]);
      Color_Set[2] = Color_Value[2];
      EEPROM.write(8, Color_Value[2]);
      delay(1000);
      break;
    }
  }
}

void Check_Color_Set() {
  if ((Color_Value[0] - Color_Set[0] >= -20 && Color_Value[0] - Color_Set[0] <= 20) && (Color_Value[1] - Color_Set[1] >= -20 && Color_Value[1] - Color_Set[1] <= 20)  && (Color_Value[2] - Color_Set[2] >= -20 && Color_Value[2] - Color_Set[2] <= 20)) {
    digitalWrite(LED_PIN, 1);
  }
  else {
    digitalWrite(LED_PIN, 0);
  }
}
