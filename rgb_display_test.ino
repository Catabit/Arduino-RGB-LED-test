#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

unsigned char r, g, b, current, buttonstate;


int state = 0;


void setup() {

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.write("Starting up!");
  display.display();
  
  pinMode(3, OUTPUT); //R
  pinMode(5, OUTPUT); //G
  pinMode(6, OUTPUT); //B

  pinMode(12, OUTPUT); //RED LED
  pinMode(11, OUTPUT); //GREEN LED
  pinMode(10, OUTPUT); //BLUE LED

  pinMode(A3, INPUT); // Potentiometer control
  pinMode(A1, INPUT_PULLUP); //Change current Color (White Button)

  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);


  current = 0;

  display.clearDisplay();
}

void loop()
{
  int reading = digitalRead(A1);


  if (reading == LOW)
  {
    state = analogRead(A3) / 4;
    current++;
    if (current == 3)
      current = 0;
  }

  if (analogRead(A3) / 4 < state - 3 || analogRead(A3) / 4 > state + 3)
  {

    if (current == 0) // change red
      if (analogRead(A3) / 4 < r - 3 || analogRead(A3) / 4 > r + 3)
        r = analogRead(A3) / 4;


    if (current == 1) // change green
      if (analogRead(A3) / 4 < g - 3 || analogRead(A3) / 4 > g + 3)
        g = analogRead(A3) / 4;

    if (current == 2) // change blue
      if (analogRead(A3) / 4 < b - 3 || analogRead(A3) / 4 > b + 3)
        b = analogRead(A3) / 4;
  }

  if (r < 20)
    r = 0;
  if (g < 20)
    g = 0;
  if (b < 20)
    b = 0;

  analogWrite(3, r);
  analogWrite(5, g);
  analogWrite(6, b);

  if (current == 0)
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  if (current == 1)
  {
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
  }

  if (current == 2)
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,18);
  display.print("R=");
  display.println(r);
  display.print("G=");
  display.println(g);
  display.print("B=");
  display.println(b);
  display.println();
  display.display();


  Serial.print("RGB(");
  Serial.print(r);
  Serial.print(',');
  Serial.print(g);
  Serial.print(',');
  Serial.print(b);
  Serial.println(")");

  delay(100);
}

