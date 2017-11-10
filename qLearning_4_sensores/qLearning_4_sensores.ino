#include <SLacoes.h>
#include <math.h>

typedef struct
{
  float valor;
  int posicao;
} ac;

void mergeSort( ac *vetor, int posicaoInicio, int posicaoFim);
void ExeAcao(int acao);
int QualEstado(int Esquerda, int Direita);
int melhorAcao(int estado);
int recompensa(int estado);

//variaveis globais utiliz

int vel = 255; // velocidade aplicada
int lim = 230;// define o limite entre o branco e o preto
// abaixo desse valor definimos de branco, acima dele e considerado
// preto.

// definicao das portas para controle do motor

SLacoes motores(5,3,9,6); // inclucao das portas para uso dos motores 
//SLcartaoSD cartao(sd,myFile,10);

//definicao de portas para os leds
//int ledCE = 2;
//int ledCD = 7;


//definicao de portas para os sensores
//quanto menor o valor, mais luz infravermelha chega ao sensor
int sensorLinhaDir = A2;
int sensorLinhaEsq = A1;
int sensorCantoEsq = A0;
int sensorCantoDir = A3;
int valorLinhaEsq, valorLinhaDir, valorCantoEsq, valorCantoDir = 0;  // variable to store the value coming from the sensor

//************************************************************************************************************************************

//********************************************************************************************************************************************
 int states = 4;
 int action = 13;
 float q [4][13];
 //******
void setup() {
  Serial.begin(9600);
  //pinMode(ledCE, INPUT);//botao
//  pinMode(ledCD, OUTPUT);//led 
  randomSeed(analogRead(7));
  for(int i = 0; i < states; i++){
    for(int j = 0; j < action; j++){
      q[i][j]= 0.0;
    }
  }

}
//*******************************************************************************************************************
void imprimeQ(float q[4][13]){
    for(int i = 0; i < 4; i++){
      Serial.println();
    for(int j = 0; j < 13; j++){
      Serial.print(q[i][j]);
      Serial.print(" ");
    }
  }

}
//********************************************************************************************
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
    motores.Frente100(vel);
//    motores.Para();
  }
  if(acao == 2 ){
    motores.Frente75(vel);
//    motores.Para();
  }
  if(acao == 3 ){
    motores.Frente65(vel);
//    motores.Para();
  }
  //*
  if(acao == 4 ){
    motores.Frente50(vel);
//    motores.Para();
  }
  if(acao == 5 ){
    motores.Direita100(vel);
//    motores.Para();
  }
  if(acao == 6 ){
    motores.Direita75(vel);
//    motores.Para();
  }
  if(acao == 7 ){
    motores.Direita65(vel);
//    motores.Para();
  }
  if(acao == 8 ){
    motores.Direita50(vel);
//    motores.Para();
  }
  if(acao == 9 ){
    motores.Esquerda100(vel);
//    motores.Para();
  }
  if(acao == 10 ){
    motores.Esquerda75(vel);
//    motores.Para();
  }
  if(acao == 11 ){
    motores.Esquerda65(vel);
//    motores.Para();
  }
  if(acao == 12 ){
    motores.Esquerda50(vel);
//    motores.Para();
  }
  //*/
  if(acao == 0){
    motores.Para();
  } 
}
//*******************************************************
int melhorAcao(int estado){
  float maior = 0.0;
  int pos;
  if(estado == 0){// buscar melhor ação para esse estado 
    maior = q[0][1];
    pos = 1;
    for(int i = 2; i <= 4; i++){//
      if(maior < q[0][i]){
        maior = q[0][i];
        pos = i;
      }
    }//fim do for
    return pos;
  }//fim do if estado
  else if(estado == 1){// buscar melhor ação para esse estado 
    /*maior = q[1][1];
    pos = 1;
    for(int i = 2; i <= 12; i++){//
      if(maior < q[1][i]){
        maior = q[1][i];
        pos = i;
      }
    }//fim do for*/
    return 0 ;
  }//fim do if estado
  else if(estado == 2){// buscar melhor ação para esse estado 
    maior = q[2][5];
    pos = 5;
    for(int i = 5; i <=8; i++){//
      if(maior < q[2][i]){
        maior = q[2][i];
        pos = i;
      }
    }//fim do for
    return pos;
  }//fim do if estado
  else if(estado == 3){// buscar melhor ação para esse estado 
    maior = q[3][9];
    pos = 9;
    for(int i = 9; i <= 12; i++){//
      if(maior < q[3][i]){
        maior = q[3][i];
        pos = i;
      }
    }//fim do for
    return pos;
  }//fim do if estado
}
//*******************************************************
int recompensa(int estado){
  if(estado == 0){
    return 1000;
  }
  else{
    return -1000;
  }
}
//********************************************************
int statess = 0, actionn = 0,statess2 = 0, actionn2 = 0;
float alpha = 0.5, gamma = 0.7;

int t1=0,t2=0;//tempo
//***********************************************************
void loop() {



//      t1=millis();
    valorLinhaEsq = analogRead(sensorLinhaEsq);
    valorLinhaDir = analogRead(sensorLinhaDir);

//    Serial.print("t1= ");
//    Serial.println(t1);
    
    valorCantoEsq = analogRead(sensorCantoEsq);
    valorCantoDir = analogRead(sensorCantoDir);
      Serial.print("Linha Esq: ");
      Serial.print(valorCantoEsq);
      Serial.print("\t ");
      Serial.print("   Linha Dir: ");
      Serial.print(valorCantoDir);
      Serial.print("\n ");
//    Serial.print("   Estado: ");
//    Serial.println(estado);
/*
      statess = QualEstado(valorLinhaEsq,valorLinhaDir);
      if(statess !=1){
      actionn = melhorAcao(statess);
      }
//      Serial.println(actionn);
//      ExeAcao(actionn);
//      delay(1);
//      motores.Para();//teste
//      delay(1);

      ExeAcao(actionn);
      
      delay(5);
      motores.Para();
      *//*
      
do{
      valorLinhaEsq = analogRead(sensorLinhaEsq);
      valorLinhaDir = analogRead(sensorLinhaDir);
      statess2 = QualEstado(valorLinhaEsq,valorLinhaDir);
      if(statess2 !=1){
      actionn2 = melhorAcao(statess2);
      }
      int r = recompensa(statess2);
      q[statess][actionn] = q[statess][actionn] + alpha * ( r + (gamma*q[statess2][actionn2]) - q[statess][actionn]);
      statess=statess2;
      actionn = actionn2;
      
      ExeAcao(actionn);
      
      delay(5);
      motores.Para();
      
      /*if(statess2 == 0 )
      {
        delay(1);
        motores.Para();//teste
        delay(2000);
      }*/

    
/*
      
}while(statess != 0);
  
//  delay(1);
//  motores.Para();
//  delay(1000);

//      imprimeQ(q);
//        t2 = millis();
//        Serial.println(t2-t1);

    
    /* 
      if (statess == 0 ){// EB DB
//      ExeAcao(1);  /
    
      }

      
      else if (statess == 1){// EP DP 
        //ExeAcao();
        //delay(2000);
      }

      
      else if (statess == 2){//EP DB
//        ExeAcao(2);/
      }
      
      else if (statess == 3){ //EB DP
//        ExeAcao(3);
      }

// */

      
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







