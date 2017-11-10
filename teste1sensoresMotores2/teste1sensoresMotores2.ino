





/************************************\
  |   Código Elaborado por RoboCore    |
  | Sinta-se livre para usar ou editar |
  |    SEMPRE cite a fonte do código   |
  |          www.RoboCore.net          |
  \************************************/
/*
  CS      = pino  4
  MOSI    = pino 11
  MISO    = pino 12
  CLK/SCK = pino 13
*/
const int chipSelect = 10;
#include <SPI.h>
#include "SdFat.h"
#include <SLacoes.h>
#include <math.h>
SdFat sd;
SdFile myFile;


//variaveis globais utiliz
long tempoanterior = 0;
unsigned long tempoatual = 0;   //Tempo atual em ms
int i = 0;// teste
int estado = 0; // variavel para verificar estado anterior
int e2 = 0; // verificar estado antes de entrar no estado frente
int v = 255; // velocidade aplicada

//int vec[MAX];// limite de posiçoes nesse programa.


int lim = 95;// define o limite entre o branco e o preto
// abaixo desse valor definimos de branco, acima dele e considerado
// preto.

// definicao das portas para controle do motor

SLacoes motores(5,3,9,6); // inclucao das portas para uso dos motores 
//SLcartaoSD cartao(sd,myFile,10);

//definicao de portas para os leds
int ledCE = 2;
int ledCD = 7;
//const int ledP = A5;
//int ledrd = 11;
//int ledre = 12;
// definicao de portas para SD
/*
  CS      = pino  4
  MOSI    = pino 11
  MISO    = pino 12
  CLK/SCK = pino 13
******* = pino 10 (necessario).
*/
//definicao de portas para os sensores
//quanto menor o valor, mais luz infravermelha chega ao sensor

int sensorLinhaDir = A2;
int sensorLinhaEsq = A1;
//int sensorCantoEsq = A0;
//int sensorCantoDir = A3;

//int ledPin = 13;      // select the pin for the LED
int valorLinhaEsq, valorLinhaDir, valorCantoEsq, valorCantoDir = 0;  // variable to store the value coming from the sensor




// funcoes SD
void Escreve(int interacao, int estado) {
  // open the file for write at end like the Native SD library
  if (!myFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END)) {
    digitalWrite(ledCD,HIGH);//1
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //2
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    sd.errorHalt("opening test.txt for write failed");
  }

  // if the file opened okay, write to it:
  Serial.print("Writing to test.txt...");
  myFile.print("-");
  myFile.print(interacao);
  myFile.print(",");
  myFile.println(estado);

  // close the file:
  myFile.close();
  Serial.println("done.");
}

void Ler() {
  // re-open the file for reading:
  if (!myFile.open("test.txt", O_READ)) {
    
    digitalWrite(ledCD,HIGH);//1
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //2
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH);//3
    delay(150);
    digitalWrite(ledCD,LOW);  
    
    sd.errorHalt("opening test.txt for read failed");
   
  }
  Serial.println("test.txt:");

  // read from the file until there's nothing else in it:

  int data, expo, cont = 0; //
  int c[10], n = 0, interacao, estado;


  while ((data = myFile.read()) >= 0) {

    if (data == 45) { //encontrou '-' // 45 em ASCII = '-'

      while ((data = myFile.read()) != 44) { // funcao pra construir String// 44 em ASCII = ','
        c[cont] = data;
        cont++;
      }
      expo = cont - 1; // aux para ajudar no calculo para converte String em int

      for (int j = 0; j < cont; j++) { ///funcao para converter String em int

        n = n + ((c[j] - 48) * pow(10, expo)); //ex: int 10 = c[0]*10^1+c[1]*10^0 sendo c[0]= 49
        // que corresponde ao Zero na tebela ASCII
        expo--;

      }
      interacao = n;
      Serial.print(interacao);
      Serial.print("-");
      cont = 0; // zera onte para obter novos numeros
      n = 0; // zera n para obter novos numero

    }
    if (data == 44) { //encotrou ','// funcao pra construir String
      while ((data = myFile.read()) != 13) { // 13 em ASCII = '\r'

        c[cont] = data;
        cont++;
      }


      expo = cont - 1; // aux para ajudar no calculo para converte String em int

      for (int j = 0; j < cont; j++) { ///funcao para converter String em int

        n = n + ((c[j] - 48) * pow(10, expo)); //ex: int 10 = c[0]*10^1+c[1]*10^0 sendo c[0]= 49
        // que corresponde ao Zero na tebela ASCII
        expo--;

      }
      estado = n;
      Serial.print(estado);
      Serial.print("\n");
      cont = 0; // zera onte para obter novos numeros
      n = 0; // zera n para obter novos numeros
    }




  }
  // close the file:
  myFile.close();

}


void Del() {
  if (!myFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END)) {
    digitalWrite(ledCD,HIGH); //1
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //2
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //3
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //4
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    sd.errorHalt("opening test.txt for write failed");
  }
  sd.remove("test.txt");

  myFile.close();
  digitalWrite(ledCD,HIGH);//1
    delay(2000);
    digitalWrite(ledCD,LOW); 
  Serial.println("Excuido");
}


//fim SD


void setup() {
  Serial.begin(9600);
  pinMode(ledCE, INPUT);
  pinMode(ledCD, OUTPUT);
  //    pinMode(ledP,OUTPUT);
  //    pinMode(ledrd,OUTPUT);
  //    pinMode(ledre,OUTPUT);
  //    pinMode(6,OUTPUT);
  //}
  //funcoes SD.

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  // change to SPI_FULL_SPEED for more performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    
    digitalWrite(ledCD,HIGH);//1
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH); //2
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH);//3
    delay(150);
    digitalWrite(ledCD,LOW);  
    delay(150);
    digitalWrite(ledCD,HIGH); //4
    delay(150);
    digitalWrite(ledCD,LOW); 
    delay(150);
    digitalWrite(ledCD,HIGH);//5
    delay(150);
    digitalWrite(ledCD,LOW);  
    
    sd.initErrorHalt();
        
  }
  
  Serial.println("initialization done.");
  digitalWrite(ledCD,HIGH);//1
    delay(2000);
    digitalWrite(ledCD,LOW); 
  
  Serial.println("OK");


}



void loop() {

  // montar a matriz dos estados que ja passou nas suas respectivas
  // interaçoes e zera o arquivo.
  //motores.Frente50(v);
  valorLinhaEsq = analogRead(sensorLinhaEsq);
  valorLinhaDir = analogRead(sensorLinhaDir);

  // Serial.println(i);
  //  valorCantoEsq = analogRead(sensorCantoEsq);
  //  valorCantoDir = analogRead(sensorCantoDir);

//
    Serial.print("Linha Esq: ");
    Serial.print(valorLinhaEsq);
    Serial.print("\t ");
    Serial.print("   Linha Dir: ");
    Serial.print(valorLinhaDir);
    Serial.print("\n ");
    Serial.print("   Estado: ");
    Serial.println(estado);
  //*
  //esquerda branco, direita preto
  if (valorLinhaEsq < lim  &&  valorLinhaDir > lim && estado < 5  ) {

    motores.Direita38(v);
    e2 = estado;
    estado = 3;
    
    //Escreve(i, estado);
    i++;


  }
  //esquerda preto, direita branco
  else if (valorLinhaEsq > lim  && valorLinhaDir < lim && estado < 5 ) {
    
    motores.Esquerda38(v);
    e2 = estado;
    estado = 1;
   //Escreve(i, estado);
    i++;

  }
  //esquerda branco, direita branco
  else if (valorLinhaEsq < lim  &&  valorLinhaDir < lim && estado < 5 ) {
    

    motores.Frente50(v);
    e2 = estado;
    estado = 2;
    //Escreve(i, estado);
    i++;
  }
  //esquerda preto, direita preto
  else if (valorLinhaEsq > lim  &&  valorLinhaDir > lim && estado < 5 ) {
    //  digitalWrite(ledCE,LOW);
    //  digitalWrite(ledCD,LOW);
    //  digitalWrite(ledP,HIGH);

    // para();
    estado = 4;
    tempoatual = millis();


  }
   if (estado == 4 && tempoatual - tempoanterior < 10000) {
    
    tempoanterior = tempoatual;
    if (e2 == 1){
      estado = 0;
      motores.Direita38(v);
      
    }else 
    if (e2==3){
      estado = 0;
      motores.Esquerda38(v);
      
    }
   }
  //*/
  if (estado == 4 && tempoatual - tempoanterior > 10000) {
    motores.Para();
    
    tempoanterior = tempoatual;

    //  Ler();
    int j = 0 ;
    //  for(j =0; j<i;j++){
    //    Escreve(j,vec[j]);
    //    Serial.println(j);
    //    Serial.println(vec[j]);
    //  }
    estado = 5;
    i = 0;
    // salvar no arquivo e zera as insteracoes
  }
  if (estado == 5) {
    //Ler();
    Serial.println();
    estado = 6;
    Serial.println("FIM");
  }
if (estado == 6){
    if (digitalRead(ledCE) == HIGH) {

    //    digitalWrite(ledCD,HIGH);
    //    delay(150);
    //    digitalWrite(ledCD,LOW);

    Del();
    estado = 0;
    tempoatual = millis();
  }
}
  //  Serial.println("Atual: ");
  //  Serial.println(estado);
  //  Serial.println("anterior: ");
  //  Serial.println(e2);

  //Serial.println("   Canto Esq: " );
  //Serial.print(valorCantoEsq);
  //Serial.print("   Canto Dir: ");
  //Serial.println(valorCantoDir);
  // delay(250);
  //delay(100);
  //*/
}
