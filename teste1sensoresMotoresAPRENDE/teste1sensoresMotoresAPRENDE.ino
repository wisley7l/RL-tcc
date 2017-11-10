




typedef struct
{
  float valor;
  int posicao;
} ac;

void mergeSort( ac *vetor, int posicaoInicio, int posicaoFim);


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
//const int ledP = A5;
// definicao de portas para SD

/*
  CS      = pino  10
  MOSI    = pino 11
  MISO    = pino 12
  CLK/SCK = pino 13
*/

//definicao de portas para os sensores
//quanto menor o valor, mais luz infravermelha chega ao sensor
int sensorLinhaDir = A2;
int sensorLinhaEsq = A1;
//int sensorCantoEsq = A0;
//int sensorCantoDir = A3;
int valorLinhaEsq, valorLinhaDir, valorCantoEsq, valorCantoDir = 0;  // variable to store the value coming from the sensor

//************************************************************************************************************************************
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
//***************************************
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
//***********************************************

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
//********************************************************************************************************************************************
 int states = 4;
 int action = 4;
 float q[4][4];
//******

void setup() {
  Serial.begin(9600);
  //pinMode(ledCE, INPUT);//botao
  pinMode(ledCD, OUTPUT);//led 
  //matriz Q(S,A);
 
  for (int i = 0; i < states;i++ ){
    for (int j = 0; j < action; j++){
      q[i][j] = 0.0;
    }
  }
      Serial.println("Matriz Q(S,A) inicialiada");

  //}
  //funcoes SD.
/*
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
// */
  randomSeed(analogRead(7));
}
//*******************************************************************************************************************
//funçoes para manipulação do aprendizado
//**********
int recompensa(int estado){
  if (estado == 0){
    return 100;
  }
  else 
    return 0;
}
//***************
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
  /*
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
    motores.Frente50(vel);
//    motores.Para();
  }
  if(acao == 8 ){
    motores.Direita50(vel);
//    motores.Para();
  }
  if(acao == 9 ){
    motores.Esquerda50(vel);
//    motores.Para();
  }
  if(acao == 10 ){
    motores.Frente38(vel);
//    motores.Para();
  }
  if(acao == 11 ){
    motores.Direita38(vel);
//    motores.Para();
  }
  if(acao == 12 ){
    motores.Esquerda38(vel);
//    motores.Para();
  }
  //*/
  if(acao == 0){
    motores.Para();
  }
  
  
}
//****************
void ExeAcaoInversa(int acao){
//  Serial.print("Acao: ");
//  Serial.println(acao);


  
  if(acao == 1 ){
    motores.Frente50Inv(vel);
//    motores.Para();
  }
  if(acao == 2 ){
    motores.Direita50Inv(vel);
//    motores.Para();
  }
  if(acao == 3 ){
    motores.Esquerda50Inv(vel);
//    motores.Para();
  }
  /*
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
    motores.Frente50(vel);
//    motores.Para();
  }
  if(acao == 8 ){
    motores.Direita50(vel);
//    motores.Para();
  }
  if(acao == 9 ){
    motores.Esquerda50(vel);
//    motores.Para();
  }
  if(acao == 10 ){
    motores.Frente38(vel);
//    motores.Para();
  }
  if(acao == 11 ){
    motores.Direita38(vel);
//    motores.Para();
  }
  if(acao == 12 ){
    motores.Esquerda38(vel);
//    motores.Para();
  }
  //*/
  if(acao == 0){
    motores.Para();
  }
  
  
}
//****************
void imprimeM(float m[4][4]){
  Serial.println("Matriz Q(S,A)");
  for(int i = 0;i < 4;i++){
    Serial.println();
    for(int j = 0; j < 4;j++){
      Serial.print(m[i][j]);
      Serial.print(" ");
      
    }
  }
}
//************
void mergeSort( ac *vetor, int posicaoInicio, int posicaoFim) {
    int i, j, k, metadeTamanho;
    ac *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (ac *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));
  

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k].valor = vetor[j].valor;
            vetorTemp[k].posicao = vetor[j].posicao;
            j++;
            k++;
        } 
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k].valor = vetor[i].valor;
                vetorTemp[k].posicao = vetor[i].posicao;
                i++;
                k++;
            } 
            else {
                if (vetor[i].valor < vetor[j].valor) { 
                    vetorTemp[k].valor = vetor[i].valor;
                    vetorTemp[k].posicao = vetor[i].posicao;
                    i++;
                    k++;
                } 
                else { 
                    vetorTemp[k].valor = vetor[j].valor;
                    vetorTemp[k].posicao = vetor[j].posicao;
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        vetor[i].valor = vetorTemp[i - posicaoInicio].valor;
        vetor[i].posicao = vetorTemp[i - posicaoInicio].posicao;
    }
    free(vetorTemp);
}
//************************************
int buscaAcao(float q[4][4],int estado){
  //acao 0 é ficar parado.
  ac acoes[4]; // desconsiderando as acoes com 38% de velocidade 
  
  for(int i = 0; i < 4;i++){
  acoes[i].valor = q[estado][i];
  acoes[i].posicao = i;
//  Serial.print("Verifica acoes");
//  Serial.println(acoes[i].posicao);
  }
 //mergeSort(acoes,0, 13);
 int randNumber = random(1,4);// sortei um numero de 1 a 3, 
 //para selecionar um das 3 melhores ações.
 
  return acoes[randNumber].posicao; // retorna o valor da ação sorteada
}


//********************************************************
int statess = 0, actionn = 0,statess2 = 0, actionn2 = 0;
//posicao da matriz Q(S,A)
float alpha = 0.5, gamma = 0.7;

int t1=0,t2=0;//tempo
int r = 0; // recompensa 
//*********************************************************
void loop() {

  // montar a matriz dos estados que ja passou nas suas respectivas
  
    digitalWrite(ledCD,LOW);
    valorLinhaEsq = analogRead(sensorLinhaEsq);
    valorLinhaDir = analogRead(sensorLinhaDir);
//    t1=millis();
//    Serial.print("t1= ");
//    Serial.println(t1);
    
//    valorCantoEsq = analogRead(sensorCantoEsq);
//    valorCantoDir = analogRead(sensorCantoDir);
    Serial.print("Linha Esq: ");
    Serial.print(valorLinhaEsq);
    Serial.print("\t ");
    Serial.print("   Linha Dir: ");
    Serial.print(valorLinhaDir);
    Serial.print("\n ");
//    Serial.print("   Estado: ");
//    Serial.println(estado);

      statess = QualEstado(valorLinhaEsq,valorLinhaDir);
//       Serial.println();
//       Serial.print("e = ");
//       Serial.println(statess);

      actionn = buscaAcao(q,statess);
//         Serial.println();
//       Serial.print("A = ");
//       Serial.println(actionn);
//       t2=millis();
//       Serial.print("t2 = ");
//       Serial.println(t2);
//       imprimeM(q);


      ExeAcao(actionn);
//
      valorLinhaEsq = analogRead(sensorLinhaEsq);
      valorLinhaDir = analogRead(sensorLinhaDir);
//    

//      Serial.print("Linha Esq: ");
//      Serial.print(valorLinhaEsq);
////    
//      Serial.print("   Linha Dir: ");
//      Serial.println(valorLinhaDir);
      
  
      statess2 = QualEstado(valorLinhaEsq,valorLinhaDir);
      actionn2 = buscaAcao(q,statess2);
     
      r = recompensa(statess2);
      
//      Serial.print("recompensa=  ");
//      Serial.println(r);      

      
      Serial.print("estado = ");
      Serial.println(statess);
      
      Serial.print("estado2 = ");
      Serial.println(statess2);
      
///*      
      q[statess][actionn] = q[statess][actionn] + alpha*(r+(gamma*q[statess2][actionn2])-q[statess][actionn]);
      Serial.print("q[");Serial.print(statess); Serial.print("]");
      Serial.print("["); Serial.print(actionn); Serial.print("] = ");
      Serial.println(q[statess][actionn]); 
//*/       
        int statess3 = statess2;
        while(statess3 == 1){
          digitalWrite(ledCD,HIGH);
        ExeAcao(actionn);  // ou acao inversa
        valorLinhaEsq = analogRead(sensorLinhaEsq);
        valorLinhaDir = analogRead(sensorLinhaDir);
        statess3 = QualEstado(valorLinhaEsq,valorLinhaDir);  
        
//          motores.Para();
//          delay(10000);
        }
        
       Serial.println();
       imprimeM(q);
       Serial.println();
//
//    motores.Frente100(vel);
//    Serial.print("OK");
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







