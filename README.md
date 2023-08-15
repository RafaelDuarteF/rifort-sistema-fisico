# SISTEMA FÍSICO RIFORT
Sistema físico da RIFORT (Sensores para contagem de lotação de ônibus públicos)

## Requisitos 

### Requisitos funcionais

  * O sistema deverá incrementar mais um passageiro a cada entrada;
  * O sistema deverá decrementar menos um passageiro a cada saída;
  * O sistema irá apenas levar em consideração, para contagem, movimentos que estejam a pelo menos 80m de distância (na vertical);
  * O sistema deverá possuir a informação de qual o número limite (lotação máxima) de passageiros no veículo;
  * O sistema deverá exibir a quantidade de passageiros presentes no ônibus na tela LCD;
  * O sistema deverá exibir um alerta na tela LCD quando o total de passageiros no ônibus bater ou ultrapassar o limite máximo;
  * O sistema deverá retirar a mensagem de alerta da tela quando o total de passageiros descer para baixo do limite máximo.

### Requisitos não funcionais

  * O protótipo físico será desenvolvido utilizando a plataforma de prototipagem eletrônica Arduíno;
  * O protótipo usará sensores ultrassônicos para identificar o movimento dos passageiros e realizar a contagem;
  * O sistema será desenvolvido utilizando a linguagem de programação C++;
  * O sistema utilizará a biblioteca LiquidCrystal_I2C para fazer a comunicação com o display na tela LCD;
  * O sistema utilizará a biblioteca Wire para fazer a comunicação com o LCD;

## Fluxograma de funcionamento da contagem

![_Fluxograma Sistema Físico](https://github.com/RafaelDuarteF/rifort-sistema-fisico/assets/103393497/f50e54e8-94ed-40d9-8b16-3c9938502778)

Esse fluxograma representa o funcionamento do processo da realização da contagem dos passageiros em um ônibus, baseado na entrada ou saída dos mesmos.
