
typedef struct
{
  float valor;
  int posicao;
} ac;

void mergeSort( ac *vetor, int posicaoInicio, int posicaoFim);

#include <SLacoes.h>
#include <math.h>

//variaveis globais utiliz

int vel = 255; // velocidade aplicada
int lim = 225;// define o limite entre o branco e o preto
// abaixo desse valor definimos de branco, acima dele e considerado
// preto.

// definicao das portas para controle do motor

SLacoes motores(5,3,9,6); // inclucao das portas para uso dos motores 
//SLcartaoSD cartao(sd,myFile,10);

//definicao de portas para os leds
int ledCE = 2;
int ledCD = 7;


//definicao de portas para os sensores
//quanto menor o valor, mais luz infravermelha chega ao sensor
int sensorLinhaDir = A2;
int sensorLinhaEsq = A1;
//int sensorCantoEsq = A0;
//int sensorCantoDir = A3;
int valorLinhaEsq, valorLinhaDir, valorCantoEsq, valorCantoDir = 0;  // variable to store the value coming from the sensor

//************************************************************************************************************************************

//********************************************************************************************************************************************
 int states = 4;
 int action = 4;
 //******
void setup() {
  Serial.begin(9600);
  //pinMode(ledCE, INPUT);//botao
  pinMode(ledCD, OUTPUT);//led 
randomSeed(analogRead(7));
}
//*******************************************************************************************************************
int QualEstado(int Esquerda, int Direita){ // recebe os valores de linha retorna o valor do estado da leitura 
      // E = esquerda D = direita B= branco P= preto
    
    if( Esquerda > lim && Direita <= lim ){ // EP e DB --Estado 2 --
      return 2;
    }
    else if( Esquerda > lim && Direita > lim ){ // EP e DP --Estado 1--
      return 1;
    }
    else if( Esquerda <= lim && Direita > lim ){ // EB e DP --Estado  3 --
      return 3;
    }
    else if( Esquerda <= lim && Direita <= lim ){ // EB e DB --Estado 0 --
        return 0;
    }
}
//******************
void ExeAcao(int acao){
//  Serial.print("Acao: ");
//  Serial.println(acao);


  
  if(acao == 1 ){
    motores.Frente50(vel);
//    motores.Para();
  }
  if(acao == 2 ){
    motores.Direita50(vel);
//    motores.Para();
  }
  if(acao == 3 ){
    motores.Esquerda50(vel);
//    motores.Para();
  }
  //*
  if(acao == 4 ){
    motores.Frente75(vel);
//    motores.Para();
  }
  if(acao == 5 ){
    motores.Direita75(vel);
//    motores.Para();
  }
  if(acao == 6 ){
    motores.Esquerda75(vel);
//    motores.Para();
  }
  if(acao == 7 ){
    motores.Frente65(vel);
//    motores.Para();
  }
  if(acao == 8 ){
    motores.Direita65(vel);
//    motores.Para();
  }
  if(acao == 9 ){
    motores.Esquerda65(vel);
//    motores.Para();
  }
  if(acao == 10 ){
    motores.Frente100(vel);
//    motores.Para();
  }
  if(acao == 11 ){
    motores.Direita100(vel);
//    motores.Para();
  }
  if(acao == 12 ){
    motores.Esquerda100(vel);
//    motores.Para();
  }
  //*/
  if(acao == 0){
    motores.Para();
  } 
}

//********************************************************
int statess = 0, actionn = 0,statess2 = 0, actionn2 = 0;

int t1=0,t2=0;//tempo
//***********************************************************
void loop() {
  
    valorLinhaEsq = analogRead(sensorLinhaEsq);
    valorLinhaDir = analogRead(sensorLinhaDir);
//    t1=millis();
//    Serial.print("t1= ");
//    Serial.println(t1);
    
//    valorCantoEsq = analogRead(sensorCantoEsq);
//    valorCantoDir = analogRead(sensorCantoDir);
//    Serial.print("Linha Esq: ");
//    Serial.print(valorLinhaEsq);
//    Serial.print("\t ");
//    Serial.print("   Linha Dir: ");
//    Serial.print(valorLinhaDir);
//    Serial.print("\n ");
//    Serial.print("   Estado: ");
//    Serial.println(estado);

      statess = QualEstado(valorLinhaEsq,valorLinhaDir);
      if (statess == 0 ){//
      ExeAcao(10);  
      actionn = 10;
      }
      else if (statess == 1){//
        ExeAcao(actionn);
        //delay(2000);
      }
      else if (statess == 2){
        ExeAcao(11);
        actionn = 11;
      }else if (statess == 3){
        ExeAcao(12);
        actionn = 12;
      }
      delay(5);
      motores.Para();

      
//*********************************
// escolher uma acaoem relacao a estado atual seguindo a politica de Q
    //repita até que seja estado final. {obs: nesse caso o tempo} 
    //escolher uma ACAO2 em relação a estado2 derivada da politica de Q
    // atualiza q = q + alpha[recompensa + gamma q(a2,e2) - q ] 
    // atualiza s para s2 e a para acao2
//*************************



// randNumber = random(300);
// Serial.println(randNumber);
// delay(50); 

}
//***************************************************************







