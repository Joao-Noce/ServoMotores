#include <Servo.h>

// João Pedro Mori Noce - 21/04/2023
// Gravador e reprodutor de movimento com quatro servomotores

#define CHAVE 13

#define POTEN1 A4
#define POTEN2 A3
#define POTEN3 A2
#define POTEN4 A1

#define BOTAO1 12
#define BOTAO2 11
//nomeia todas as portas

Servo A;
Servo B;
Servo C;
Servo D;
//nomeia os servoMotores

int posicao1[50];
int posicao2[50];
int posicao3[50];
int posicao4[50];
//limita até 50 posições cada servoMotor

int x = 0;
//cria a variável que indicará a quantidade de gravações

void setup()
{
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  
  pinMode(CHAVE,INPUT);
  pinMode(BOTAO1,INPUT_PULLUP);
  pinMode(BOTAO2,INPUT_PULLUP);
  
  pinMode(POTEN1,INPUT);
  pinMode(POTEN2,INPUT);
  pinMode(POTEN3,INPUT);
  pinMode(POTEN4,INPUT);
 //indica a função de entrada ou saída de cada pino
  
  A.attach(7);
  B.attach(6);
  C.attach(5);
  D.attach(4);
 //prende o nome do servoMotor a cada pino
  
  Serial.begin(9600);
 //abre a porta serial com taxa de transferência para 9600 bps
}

void loop()
{  
  int valor1;
  int valor2;
  int valor3;
  int valor4;
 
  valor1 = map(analogRead(POTEN1), 0, 1023, 0, 180); 
  valor2 = map(analogRead(POTEN2), 0, 1023, 0, 180);
  valor3 = map(analogRead(POTEN3), 0, 1023, 0, 180);
  valor4 = map(analogRead(POTEN4), 0, 1023, 0, 180);
 //limita o giro do potenciometro de 1023 para 180
  
  A.write(valor1);
  B.write(valor2);
  C.write(valor3);
  D.write(valor4);
 //prende cada potenciometro ao seu respectivo servoMotor
  
            
  if(digitalRead(BOTAO1) == 0){
    
    
    posicao1[x] = valor1;
    posicao2[x] = valor2;
    posicao3[x] = valor3;
    posicao4[x] = valor4;
    
    x++;
    digitalWrite(8,1);
    delay(100);
 //a cada toque no botão, x passa para a próxima gravação
    
    Serial.print("Gravou = ");
    Serial.println(x);
    
    while(digitalRead(BOTAO1) == 0){
      
      Serial.println("Solte o Botao");
 //se o botão estiver pressionado, nada acontece
    }
  }
  
  if(digitalRead(CHAVE) == 0){
   Serial.println("Gravar");
    digitalWrite(10,1);
    digitalWrite(9,0);
    delay(100);
  }
  
  else{
    digitalWrite(9,1);
    digitalWrite(10,0);
    delay(100);
    Serial.println("Reproduzindo");
    
    for(int a = 0; a < x; a = a + 1){
 //cria a variável que limitará as posições para o número de x
      
      A.write(posicao1[a]);
      B.write(posicao2[a]);
      C.write(posicao3[a]);
      D.write(posicao4[a]);
      delay(1000);
    }
  }
  
  if(digitalRead(BOTAO2) == 0){
    x = 0;
    digitalWrite(8,1);
 //x volta a ser 0, excluindo todas as gravações feitas
    Serial.print("Gravou = ");
    Serial.println(x);
    
    while(digitalRead(BOTAO2) == 0){
      
     Serial.println("Solte o Botao");
    }
  }
  else{
    digitalWrite(8,0);
  }
}