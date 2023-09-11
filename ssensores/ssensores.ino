#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 

#define col 20 // Serve para definir o numero de colunas do display utilizado
#define lin  4 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd_1(ende,col,lin); // Chamada da função LiquidCrystal para ser usada com o I2C


// Configurações iniciais do sistema

int passageiro = 38; // Número de passageiros presentes no ônibus
int distanciaMaxima = 20; // Distância de detecção de movimento em cm (vertical)
bool movimentoSensor01Detectado = false;
bool movimento0 = false;
bool movimento1 = false;
int lotacaoMaxima = 40; // Número de Lotação Máxima específico do modelo do ônibus
#define echoPin0 6
#define trigPin0 5
#define echoPin1 2
#define trigPin1 3
unsigned int duracao0 = 0;
unsigned int distancia0 = 0;
unsigned int duracao1 = 0;
unsigned int distancia1 = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  lcd_1.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd_1.backlight(); // Serve para ligar a luz do display
  lcd_1.clear(); // Serve para limpar a tela do display
  lcd_1.setCursor(7, 0);
  lcd_1.print(passageiro);
  Serial.begin(9600);
}
// Função responsável por incrementar ou decrementar passageiros, e exibir tal na tela LCD
void contarPassageiro(int tipo)
{
  if(tipo == 1 && passageiro > 0)
  {
    passageiro = passageiro - 1;
  } else if(tipo == 2)
  {
    passageiro = passageiro + 1;
  }
  if(passageiro >= 40) 
  {
    handleLotacaoMaxima(1);
  } else 
  {
    Serial.print(passageiro);
    Serial.print(" - ");
    lcd_1.clear();
    lcd_1.setCursor(7, 0);
    lcd_1.print(passageiro);
  }
  movimentoSensor01Detectado = true;
  delay(200);
}

// Função responsável por, e exibir tal na tela LCD
void handleLotacaoMaxima(int tipoLM)
{
  if(tipoLM == 1)
  {
    Serial.print(passageiro);
    Serial.print(" - ");
    lcd_1.clear();
    lcd_1.setCursor(7, 0);
    lcd_1.print(passageiro);
    Serial.print("Lotação Máxima atingida!!");
    lcd_1.setCursor(6, 1);
    lcd_1.print("LM!!");
    lcd_1.setCursor(0, 0);
  }
}

// Funcão responsável por realizar a verificação dos movimentos nos sensores e trabalhar em cima disso
void verificarSensor(int numSensor) {
  if(numSensor == 0)
  {
    if(distancia1 < distanciaMaxima && !movimentoSensor01Detectado)
    {
        movimento1 = true;
        movimento0 ? contarPassageiro(2) : (void)0;
    } 
  } else if (numSensor == 1)
  {
    if (distancia0 < distanciaMaxima && !movimentoSensor01Detectado)
    {
        movimento0 = true;
        movimento1 ? contarPassageiro(1) : (void)0;
    }
  }
}

void loop()
{
  
 // Start no sensor 0

  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin0, LOW);

  duracao0 = pulseIn(echoPin0, HIGH);
  distancia0 = duracao0 * 0.01719445;

  // Start no sensor 1

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duracao1 = pulseIn(echoPin1, HIGH);
  distancia1 = duracao1 * 0.01719445;


  // Verifique qual sensor detectou primeiro
  
  verificarSensor(0);
  verificarSensor(1);
  
  
  if(distancia1 > distanciaMaxima && movimentoSensor01Detectado) {
    movimento1 = false;
  } 
  if(distancia0 > distanciaMaxima && movimentoSensor01Detectado) {
    movimento0 = false;
  }
  if(movimentoSensor01Detectado && !movimento1 && !movimento0) {
    movimentoSensor01Detectado = false;
  }
}
