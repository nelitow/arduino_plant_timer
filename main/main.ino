#include <Arduino.h>
#include <TM1637Display.h>

//Porta ligada ao pino IN1 do modulo rele
int porta_rele1 = 7;
int porta_rele2 = 8;

#define CLK 4
#define DIO 5

TM1637Display display(CLK, DIO);

void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT);
  pinMode(porta_rele2, OUTPUT);
  pinMode(A1, INPUT);

  pinMode(2, INPUT_PULLUP);//botao de skip
}

void loop() {
  digitalWrite(porta_rele2, HIGH);
  digitalWrite(porta_rele1, LOW);

  display.setBrightness(0x0a);
  display.showNumberDec(420, false);
  delay(1000);
  digitalWrite(porta_rele1, HIGH);
  delay(1000);

  for (long i = 21600; i > 0; i--) {
    if (digitalRead(2)) {
      delay(1000);
    } else {
      i = i - 100;
      display.showNumberDec((i / 3600) * 100 + ((i - (3600 * (i / 3600))) / 60), false);
    }
  }
  digitalWrite(porta_rele1, LOW);
  for (long i = 64800; i > 0; i--) {
    if (digitalRead(2)) {
      delay(1000);
      if ( (i % 2) == 0)
        display.setBrightness(0x00);
      else
        display.setBrightness(0x0a);
    } else i = i - 100;
    display.showNumberDec((i / 3600) * 100 + ((i - (3600 * (i / 3600))) / 60), false);
  }
  digitalWrite(porta_rele1, HIGH);
  delay(100);
  digitalWrite(porta_rele1, LOW);
  delay(100);
  digitalWrite(porta_rele1, HIGH);
}
