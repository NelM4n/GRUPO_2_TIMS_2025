#include<Arduino.h>
#define AIN1 13
#define BIN1 12
#define AIN2 14
#define BIN2 27
#define PWMA 26
#define PWMB 25
#define STBY 33

void frente() {
    Serial.print("Indo pra frente");
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);  
  }
  void parado() {
    Serial.print("Parado");
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);  
  }
  void esquerda(){
    Serial.print("Virando pra esquerda");
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW); 
  }

  void direita(){
    Serial.print("Virando pra direita");
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); 
  }

  void re(){
    Serial.print("Indo pra trás");
    analogWrite(PWMA, 255);
    analogWrite(PWMB, 255);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); 
  }