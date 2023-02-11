/*
Instrumentação Eletronica UNB - FGA
Criado por João Vitor em fevereiro de 2023

Objetivos: 
-Leitura dos valores digitais do MPU6050
-Conversão dos dados digitais do acelerometro para gravidade 
-Calibração dos Eixos do acelerometro
-Leitura dos angulos de inclinação em Graus usando a gravidade.
*/


/*
 *  Mandatory includes
 */
#include <Arduino.h>
#include <TinyMPU6050.h>

/* CONSTANTES */
const int medidas = 100; //quantidade de coletas para calibracao
const int qt = 36; //quantidade de coletas para calcular erro
const int lin = 15; //quantidade de linhas printadas na serial
const int line = 255-lin;






/* Variaveis*/
byte qtline = 0;
float AcelXoffset, AcelYoffset, AcelZoffset, GanhoX, GanhoY, GanhoZ;
float Xp= 108.04;
float Xn = -92.43;
float Yp = 99.13;
float Yn = -99.71;
float Zp = 102.80;
float Zn = -99.17;



  
/*   Constructing MPU-6050   */
MPU6050 mpu (Wire);




/*     Setup    */
void setup() {

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("iniciando Calibração...");
  calibrar(); 
  Serial.println("Calibracao efetuada com sucesso!");
}

void loop() {
  
  // mpu.Execute(); // atualiza e trata todos os dados do MPU6050 para futuramente poderem serem chamados os valores.
  acelerometro(); // Funcao que printa valores constantemente
  lerCMD(); // funcão que verifica comandos na Serial
}


void acelerometro(){// Printa os dados lidos na serial
  mpu.Execute(); // atualiza e trata todos os dados do MPU6050 para futuramente poderem serem chamados os valores.
  
  if (qtline == 0){ // printa a qt de linhas definida no escopo
    Serial.println("\n|     Raw X     |     Raw Y     |     Raw Z     |       X       |       Y       |       Z       |     ang YZ    |     ang XZ    |     ang XY    |");
    qtline = line;    
  }

  if ((millis()%250)==0){
    // Serial.println("| %d | %d | %d | %f m/s² | %f m/s² | %f m/s² |",mpu.GetRawAccX(),mpu.GetRawAccY(), mpu.GetRawAccZ(), mpu.GetAccX(), mpu.GetAccY(), mpu.GetAccZ());
    Serial.print("| ");
    PrintAcelBefore();
    PrintAcelAfter();
    PrintAng();
    qtline ++;
  }
}

void lerCMD(){// ler comandos na Serial
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n'); //salva o comando digitado em uma variavel
    if (comando == "calibrar"){  
      calibrar(); 
    }    
    else if (comando == "erro"){  
      Erro();
    }  
  }  
}

void calibrar(){// calibra os eixos do acelerometro
  Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
  while(true){
    if (Serial.available()){
      String comando = Serial.readStringUntil('\n');
      if (comando == "Xp"){  
        Xp = 0;  //reseta somatorio
        Serial.print("Xp = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute(); //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccX());
          Serial.print(", ");
          Xp += mpu.GetAccX();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Xp COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      } 
      else if (comando == "Xn"){  
        Xn = 0;   //reseta somatorio
        Serial.print("Xn = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute();  //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccX());
          Serial.print(", ");
          Xn += mpu.GetAccX();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Xn COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
      else if (comando == "Yp"){  
        Yp = 0;   //reseta somatorio
        Serial.print("Yp = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute();  //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccY());
          Serial.print(", ");
          Yp += mpu.GetAccY();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Yp COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
      else if (comando == "Yn"){  
        Yn = 0;   //reseta somatorio
        Serial.print("Yn = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute();  //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccY());
          Serial.print(", ");
          Yn += mpu.GetAccY();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Yn COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
      else if (comando == "Zp"){  
        Zp = 0;   //reseta somatorio
        Serial.print("Zp = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute();  //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccZ());
          Serial.print(", ");
          Zp += mpu.GetAccZ();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Zp COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
      else if (comando == "Zn"){  
        Zn = 0;   //reseta somatorio
        Serial.print("Zn = [");
        for (int i = 0; i< medidas; i++){
          mpu.Execute();  //atualilza os valores dos eixos.
          Serial.print(mpu.GetAccZ());
          Serial.print(", ");
          Zn += mpu.GetAccZ();
          delay(2);
        }
        Serial.println("]");
        Serial.println("##### DADOS Zn COLETADOS #######");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
      else if (comando == "EXIT"){ 
        Serial.println("##### CALIBRACAO ENCERRADA #######");
        break;
      }
      else{
        Serial.println("##### COMANDO INVALIDO #####");
        Serial.println("Digite o eixo que será calibrado. Ex: Xp, Xn, Yp, Yn, Zp, Zn ou EXIT");
      }
    }
  }

  //***** CALCULO DOS OFSSET's E GANHOS ******//
  AcelXoffset = (Xp+Xn)/(2*medidas);
  AcelYoffset = (Yp+Yn)/(2*medidas);
  AcelZoffset = (Zp+Zn)/(2*medidas);
  GanhoX = Xp/medidas - AcelXoffset;
  GanhoY = Yp/medidas - AcelYoffset;
  GanhoZ = Zp/medidas - AcelZoffset;

  Serial.println(Xp);
  Serial.println(Xn);
  Serial.println(Yp);
  Serial.println(Yn);
  Serial.println(Zp);
  Serial.println(Zn);

  // Printa os parametros de calibração na serial
  Serial.println("Ganho X = "+(String)GanhoX +"\t Offset X = "+(String)AcelXoffset);
  Serial.println("Ganho Y = "+(String)GanhoY +"\t Offset Y = "+(String)AcelYoffset);
  Serial.println("Ganho Z = "+(String)GanhoZ +"\t Offset Z = "+(String)AcelZoffset);
}


// FUNCOES COM EIXOS CALIBRADOS
float getX(){
  float X = mpu.GetAccX()/GanhoX - AcelXoffset;
  return(X);
}

float getY(){
  float Y = mpu.GetAccY()/GanhoY - AcelYoffset;
  return(Y);
}

float getZ(){
  float Z = mpu.GetAccZ()/GanhoZ - AcelZoffset;
  return(Z);
}


// Calculo do angulo em graus 
float ang(float Y, float Z){
  float ZY = atan(Y/Z)*57.2958;
  if (Y < 0 ){ // Y negativo
    if (Z < 0){ // Y- Z-
      return (180 - ZY);
    }
    else if(Z == 0){ // Y- Z0
      return (90);
    }
    else { // Y- Z+
      return (-ZY); 
    }
  }
  else if(Y > 0){ // Y positivo
    if (Z < 0){ // Y+ Z-
      return (-ZY +180);
    }
    else if(Z == 0){ // Y+ Z0
      return (270);
    }
    else { // Y+ Z+
      return (360-ZY); 
    }
  }
  else{ // Y zerado
    return (180);
  }
}

void Erro(){ //Função para calcular o Erro.
  int passo = 0;
  //define vetores para armazenar valores medidos e de referencia
  float ref[qt-1], erro[qt-1]={0}; 
  Serial.println("Posicione em 0 graus e pressione Enter");
  while (passo < qt){ //loop para medir erro dos angulos solicitados
    if(Serial.available()){
      //executa coleta de dados quando pressiona ENTER na Serial
      if (Serial.readStringUntil('\n')){  
        mpu.Execute(); //Atualiza os dados
        ref[passo] = 10*passo; //define o angulo de referencia dessa interacao

        //condiçao para evitar angulo proximo 360 quando referencia é 0
        if(passo == 0){ 
          if(ang(getY(),getZ())< 180){
            erro[passo] = ang(getY(),getZ()) - ref[passo];
          } 
          else{
            erro[passo] = ang(getY(),getZ()) - 360;            
          }      
        }
        //calcula o diferença entre medido e referencia.
        else erro[passo] = ang(getY(),getZ()) - ref[passo]; 
        
        //apresenta o Erro na serial
        Serial.println("angulo ref = "+ (String)ref[passo]+"\t angulo lido = "+ (String)(erro[passo]+ref[passo])+"\t erro = "+(String)erro[passo]);
        passo ++; //incrementa o loop

        if (passo < qt) Serial.println("Posicione em "+(String)(ref[passo-1]+10)+" graus e pressione Enter");

        //fim da coleta, apresenta os valores como vetores na serial.
        else {
          Serial.println("######## Fim de coleta dos Erros");
          Serial.print("erro = [");
          for(int i=0;i<qt;i++){
            Serial.print(erro[i]);
            if(i<(qt-1)) Serial.print(" ");
          }
          Serial.println("]");
          Serial.print("ref = [");
          for(int i=0;i<qt;i++){
            Serial.print(ref[i]);
            if(i<(qt-1)) Serial.print(" ");
          }
          Serial.println("]");
        }
      }
    }
  }
}

//funcoes de print
void PrintAcelBefore(){// printa eixos nao calibrados
  Serial.print(mpu.GetAccX()); 
  Serial.print(" g \t| ");
  Serial.print(mpu.GetAccY());
  Serial.print(" g \t| ");  
  Serial.print(mpu.GetAccZ());
  Serial.print(" g \t| ");  
}

void PrintAcelAfter(){ //printa eixos calibrados
  Serial.print(getX());
  Serial.print(" g \t| ");  
  Serial.print(getY());
  Serial.print(" g \t| ");
  Serial.print(getZ());
  Serial.print(" g \t| ");
}

void PrintAng(){ //printa angulos
  Serial.print(ang(getY(), getZ()));
  Serial.print("◦ YZ \t| ");
  Serial.print(ang(getX(), getZ()));
  Serial.print("◦ XZ \t| ");
  Serial.print(ang(getX(), getY()));
  Serial.println("◦ XY \t| ");
}