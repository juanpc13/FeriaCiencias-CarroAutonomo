#include <Servo.h>

//Servo
Servo myservo;
#define maximoServo   160
#define centroServo   80
#define minimoServo   0
#define minimoTiempo  1000

//Ultrasonic
#define echoPin       12
#define trigPin       13
#define stopDistancia 15
#define readTimes     4

//Motor
#define motorA1       5   //Izquierda
#define motorA2       6   //Derecha
#define motorB1       10  //Izquierda
#define motorB2       11  //Derecha
#define motorAPower   200 //Izquierda
#define motorBPower   200 //Derecha

void setup() {
  //Serial
  Serial.begin(9600);
  //Servo
  myservo.attach(A5);  // attaches the servo on pin 9 to the servo object
  //Ultasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  //Motor
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  //TEST
  //Serial.println(getDistanciaFrente());
  //Serial.println(getDistanciaIzquierda());
  //Serial.println(getDistanciaDerecha());
}

void loop() {
  //CARRO LOOP
  int distanciaActual = getDistanciaFrente(false);
  if(distanciaActual <= stopDistancia){
    //DETENER CARRO
    motorA(0);
    motorB(0);
    //EVALUAR
    int distanciaIzquierda = getDistanciaIzquierda();
    int distanciaDerecha = getDistanciaDerecha();
    //VALIDAR TOPE Y ESPERAR 4 segundos
    if(distanciaIzquierda <= stopDistancia || distanciaDerecha <= stopDistancia){
      //DETENER CARRO
      motorA(0);
      motorB(0);
      delay(4000);
      return;
    }
    //DAR DIRECCION DERECHA O IZQUIERDA
    if(distanciaIzquierda >= distanciaDerecha){
      //GIRAR
      motorA(0);
      motorB(motorBPower);
      delay(200);
    }else{
      //GIRAR
      motorA(motorAPower);
      motorB(0);
      delay(200);
    }
    //CAMINAR
    motorA(motorAPower);
    motorB(motorBPower);
  }else{
    //CAMINAR
    motorA(motorAPower);
    motorB(motorBPower);
  }
  //DEBUG
  Serial.println(distanciaActual);
  
}

int getDistancia(){
  long duration; // variable for the duration of sound wave travel
  int distance; 
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}
int getDistanciaFrente(bool needDelay){
  myservo.write(centroServo);
  if(needDelay){
    delay(minimoTiempo);
  }
  int dis = getDistancia();
  return dis;
}
int getDistanciaIzquierda(){
  myservo.write(maximoServo);
  delay(minimoTiempo);
  int dis = getDistancia();
  myservo.write(centroServo);
  delay(minimoTiempo);
  return dis;
}
int getDistanciaDerecha(){
  myservo.write(minimoServo);
  delay(minimoTiempo);
  int dis = getDistancia();
  myservo.write(centroServo);
  delay(minimoTiempo);
  return dis;
}
void motorA(int power){
  if(power >= 0){
    analogWrite(motorA1, 0);
    analogWrite(motorA2, power);
  }else{
    analogWrite(motorA1, power);
    analogWrite(motorA2, 0);
  }
}
void motorB(int power){
  if(power >= 0){
    analogWrite(motorB1, 0);
    analogWrite(motorB2, power);
  }else{
    analogWrite(motorB1, power);
    analogWrite(motorB2, 0);
  }
}
