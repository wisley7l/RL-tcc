/************************************\
|   Código Elaborado por RoboCore    |
| Sinta-se livre para usar ou editar |
|    SEMPRE cite a fonte do código   |
|          www.RoboCore.net          |
\************************************/
int lim = 250;// define o limite entre o branco e o preto
// abaixo desse valor definimos de branco, acima dele e considerado
// preto.

//quanto menor o valor, mais luz infravermelha chega ao sensor

int sensorLinhaDir = A2;
int sensorLinhaEsq = A1;
//int sensorCantoEsq = A;
//int sensorCantoDir = A;

int ledPin = 13;      // select the pin for the LED
int valorLinhaEsq, valorLinhaDir, valorCantoEsq, valorCantoDir = 0;  // variable to store the value coming from the sensor

void setup() {
    Serial.begin(9600);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
}

void loop() {
  
  valorLinhaEsq = analogRead(sensorLinhaEsq);    
  valorLinhaDir = analogRead(sensorLinhaDir);
  //valorCantoEsq = analogRead(sensorCantoEsq);
  //valorCantoDir = analogRead(sensorCantoDir);
  
  Serial.print("Linha Esq: ");
  Serial.print(valorLinhaEsq);
  Serial.print("\n ");
  Serial.print("   Linha Dir: ");
  Serial.print(valorLinhaDir);
  Serial.print("\n ");
if(valorLinhaEsq<lim  &&  valorLinhaDir>lim){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);  
}
else if(valorLinhaEsq>lim  && valorLinhaDir<lim){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);  
}
else if(valorLinhaEsq<lim  &&  valorLinhaDir<lim){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);  
}
else if(valorLinhaEsq>lim  &&  valorLinhaDir>lim){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);  
}


  //Serial.print("   Canto Esq: ");
  //Serial.print(valorCantoEsq);
  //Serial.print("   Canto Dir: ");
  //Serial.println(valorCantoDir);
  
  delay(250);
}
