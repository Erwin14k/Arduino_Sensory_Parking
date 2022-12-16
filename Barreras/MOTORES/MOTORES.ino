
//PINES PARA LA BARRERA DE ENTRADA
#define BARR1_1 8
#define BARR1_2 9
#define BARR1_3 10
#define BARR1_4 11
//PINES PARA LA BARRERA DE SALIDA
#define BARR2_1 4
#define BARR2_2 5
#define BARR2_3 6
#define BARR2_4 7
void setup()
{

  Serial1.begin(9600); //Comunicacion bluetooth
  pinMode(BARR1_1,OUTPUT);
  pinMode(BARR1_2,OUTPUT);
  pinMode(BARR1_3,OUTPUT);
  pinMode(BARR1_4,OUTPUT);

  pinMode(BARR2_1,OUTPUT);
  pinMode(BARR2_2,OUTPUT);
  pinMode(BARR2_3,OUTPUT);
  pinMode(BARR2_4,OUTPUT);


  //AL INICIO COLOCAR LOS MOTORES EN SU ESTADO INICIAL
  estadoInicial_1();
  estadoInicial_2();
  
}



void loop() 
{

  //Cuando se active alguna de las barreras, llamar a la función de activar
  //activarBarrera_1();
  //activarBarrera_2();
}

void activarBarrera_1(){
  //Primero giro 90 grados en sentido antihorario
  digitalWrite(BARR1_4,LOW);
  digitalWrite(BARR1_2, LOW);
  
  digitalWrite(BARR1_1,HIGH);
  delay(3000);
  desactivarBarrera_1();
}

void activarBarrera_2(){
  //Primero giro 90 grados en sentido antihorario
  digitalWrite(BARR2_4,LOW);
  digitalWrite(BARR2_2, LOW);
  
  digitalWrite(BARR2_1,HIGH);
  delay(3000);
  desactivarBarrera_2();
}

void desactivarBarrera_1(){
  digitalWrite(BARR1_2, HIGH);
  digitalWrite(BARR1_4,HIGH);
  delay(5000); //Tiempo que podemos cambiar, representa lo que tarda el carro en pasar la barrera
  estadoInicial_1();

  }

  void desactivarBarrera_2(){
  digitalWrite(BARR2_2, HIGH);
  digitalWrite(BARR2_4,HIGH);
  delay(5000);
  estadoInicial_2();

  }

 void estadoInicial_1(){
  digitalWrite(BARR1_1, LOW);
  digitalWrite(BARR1_2,LOW);
  digitalWrite(BARR1_4,LOW);
  }

  void estadoInicial_2(){
  digitalWrite(BARR2_1, LOW);
  digitalWrite(BARR2_2,LOW);
  digitalWrite(BARR2_4,LOW);
  }

  // conectar bluetooth
bool getConnection()
{
 int state = 0;
 if(Serial1.available() > 0){
  state = Serial1.read();

  if (state == 'A') {
       
           activarBarrera_1();
       }
      
       else if (state == 'C')
       {
           activarBarrera_2();
       }

       return true;
     
}

      return false; 

       
      
       
}
