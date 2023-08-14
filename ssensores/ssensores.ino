#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 

#define col 20 // Serve para definir o numero de colunas do display utilizado
#define lin  4 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd_1(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

int passageiro = 20;
bool movimentoDetectado = false;
bool movimentoDetectado2 = false;
int lotacaoMaxima = 40;
#define echoPin 6
#define trigPin 5
#define echoPin2 2
#define trigPin2 3
unsigned int duracao = 0;
unsigned int distancia = 0;
unsigned int duracao2 = 0;
unsigned int distancia2 = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  lcd_1.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd_1.backlight(); // Serve para ligar a luz do display
  lcd_1.clear(); // Serve para limpar a tela do display
  lcd_1.setCursor(7, 0);
  lcd_1.print(passageiro);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.01719445;

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duracao2 = pulseIn(echoPin2, HIGH);
  distancia2 = duracao2 * 0.01719445;

  if (distancia < 20 && movimentoDetectado == false) {
    if (passageiro > 0) {
      passageiro = passageiro - 1;
      Serial.print(passageiro);
      Serial.print(" - ");
      lcd_1.clear();
      lcd_1.setCursor(7, 0);
      lcd_1.print(passageiro);
      movimentoDetectado = true;
      delay(500);
    }
    else {
      Serial.print(passageiro);
      Serial.print(" - ");
      lcd_1.clear();
      lcd_1.setCursor(7, 0);
      lcd_1.print(passageiro);
      movimentoDetectado = true;
    }
    if (passageiro >= lotacaoMaxima) {
      Serial.print(passageiro);
      Serial.print(" - ");
      lcd_1.clear();
      lcd_1.setCursor(7, 0);
      lcd_1.print(passageiro);
      lcd_1.setCursor(6, 1);
      Serial.print("Lotação Máxima atingida!!");
      lcd_1.print("LM!!");
      lcd_1.setCursor(7, 0);
    }
  }
  if (distancia > 20) {
    movimentoDetectado = false;
  }

  if (distancia2 < 20 && movimentoDetectado2 == false) {
    passageiro = passageiro + 1;
    Serial.print(passageiro);
    Serial.print(" - ");
    lcd_1.clear();
    lcd_1.setCursor(7, 0);
    lcd_1.print(passageiro);
    movimentoDetectado2 = true;
    delay(500);
    if (passageiro >= lotacaoMaxima) {
      if (passageiro == lotacaoMaxima) {
        Serial.print("Alerta, lotacao maxima atingida! Não ultrapasse! ");
        lcd_1.setCursor(6, 1);
        lcd_1.print("LM!!");
        lcd_1.setCursor(7, 0);
      }
      else {
        Serial.print("Alerta, lotacao maxima atingida!, libere ");
        Serial.print(passageiro - (lotacaoMaxima - 1));
        Serial.print(" passageiros! ");
        lcd_1.setCursor(6, 1);
        lcd_1.print("LM!!");
        lcd_1.setCursor(7, 0);
      }
    }
  }
  if (distancia2 > 20) {
    movimentoDetectado2 = false;
  }
}
