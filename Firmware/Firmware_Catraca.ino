/* ============================================================
Versão 1.0 
Projeto de Acionamento de Catraca em 2 Modos
Compilador: Arduino IDE 1.8.14
Autor: Eng. Luiz Bertucci
Data:  Janeiro de 2022
============================================================ */


// ============================================================
// --- Mapeamento de Hardware ---
//define name ports
#define sole1 2            //Define porta da solenoide 1
#define sole2 3            //Define porta da solenoide 2
#define rotacaoDireita 4   //Define porta do sensor de rotação 1 
#define rotacaoEsquerda 5  //Define porta do sensor de rotação 2
#define liberaDireita 6    //Define porta que libera entrada.
#define liberaEsquerda 7   //Define porta que libera saída.
#define modo  8            // Se Modo true= 1 Solenoide, se Modo false = 2 solenoides. 
#define espera 1200        //Tempo de espera no programa após libeção de entrada ou saída. 
#define trava 1200         // Tempo da solenoide ligada para bloquear/travar passagem indevida.
// ============================================================

// ============================================================
// --- Variáveis ---
bool flagMode = false;
// ============================================================

// ============================================================
// --- Funções---
void solenoide_1(); //Função que opera em modo 1 solenóide.
void solenoide_2(); //Função que opera em modo 2 solenóides.
// ============================================================

void setup() {
  Serial.begin(9600);
  //Define se as portas são entradas ou saídas.
  pinMode(sole1, OUTPUT);
  pinMode(sole2, OUTPUT);
  pinMode(rotacaoDireita, INPUT);
  pinMode(rotacaoEsquerda, INPUT);
  pinMode(liberaDireita, INPUT);
  pinMode(liberaEsquerda, INPUT);
  pinMode(modo, INPUT);  
 //Inicia as solenoides deligadas. 
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void loop() {
  // Condição que define modo de operação
  //1 solenoide
  if (digitalRead(modo)) {
    solenoide_1();
    if(flagMode){
      Serial.println("Modo 1");
      flagMode = !flagMode;
      }
  }
  //2 solenoides
  if (!digitalRead(modo)) {
    solenoide_2();
    if(!flagMode){
      Serial.println("Modo 2");
      flagMode = !flagMode;
      }
  }
}

void solenoide_1() {
  if ((digitalRead(rotacaoDireita) || digitalRead(rotacaoEsquerda)) && (!digitalRead(liberaDireita) || !digitalRead(liberaEsquerda))) {
    digitalWrite(sole1, HIGH);
    delay(trava);
    digitalWrite(sole1, LOW);
    Serial.println("Acesso Negado x");
  }
  if (digitalRead(liberaDireita)) {
    Serial.println("Direita -->");
    digitalWrite(sole1, LOW);    
    delay(espera);
  }
  if (digitalRead(liberaEsquerda)) {
    Serial.println("Esquerda <--");
    digitalWrite(sole1, LOW);
    delay(espera);
  }
} // Fim da função 1

void solenoide_2() {
  if (digitalRead(rotacaoDireita) && (!digitalRead(liberaDireita) || !digitalRead(liberaEsquerda))) {
    digitalWrite(sole1, HIGH);
    Serial.println("Acesso Negado x");
    delay(trava);
    digitalWrite(sole1, LOW);  
  }
  if (digitalRead(rotacaoEsquerda) && (!digitalRead(liberaDireita) || !digitalRead(liberaEsquerda))) {
    digitalWrite(sole2, HIGH);
    Serial.println("Acesso Negado x");    
    delay(trava);
    digitalWrite(sole2, LOW);
  }
  if (digitalRead(liberaDireita)) {
    digitalWrite(sole1, LOW);
    digitalWrite(sole2, HIGH);
    Serial.println("Direita -->");
    delay(espera);
    digitalWrite(sole2, LOW);
  }
  if (digitalRead(liberaEsquerda)) {
    digitalWrite(sole1, HIGH);
    digitalWrite(sole2, LOW);
    Serial.println("Esquerda <--");
    delay(espera);
    digitalWrite(sole1, LOW);
  }
} //Fim da função 2



// ============================================================
// --- FINAL DO PROGRAMA ---
