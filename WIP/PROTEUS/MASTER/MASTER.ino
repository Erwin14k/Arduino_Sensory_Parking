#define ALARM_CHECK 13
#define LED_CHECK 12


bool ldr_data_ready = false;
String ldr_data = "";

bool led_test = false;

char estado = '0';	

// buzzer

// BARRERAS

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


void setup(){

    // empezar puerto serial 0 => PC
    Serial.begin(9600);
    Serial.println("MASTER READY");

    // empezar puerto serial 1 => ARDUINO LDR
    // empezar puerto serial 2 => ARDUINO MASTER
    
    Serial1.begin(9600);
    Serial2.begin(9600);

    pinMode(ALARM_CHECK, INPUT);

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

void loop(){

    checkForIncomingPetitions();

}

// LED;<num_parqueo>;<estado>
    // estado: reservado = 1, no reservado = 0; 2 = alarma desactivada
void enviarReservacion(int parqueo){
    digitalWrite(LED_CHECK, HIGH);    
    Serial1.print("LED;4;1");
    Serial2.print("Reservacion enviada");
    Serial.print("LED;4;1");
    delay(1000);
    digitalWrite(LED_CHECK, LOW);

}

void desactivarAlarma(){
    digitalWrite(LED_CHECK, HIGH);
    Serial1.print("LED;4;2");
    delay(1000);
    digitalWrite(LED_CHECK, LOW);
}

void sonarAlarma(){

}

void checkForIncomingPetitions(){
    char estado = '0';
    // Serial1 es bluetooth
    if (Serial1.available() > 0){
        estado = Serial1.read();


        // switch de estados

        // estados para bluetooth | A = abrir entrada ; C = abrir salida ; D = desactivar alarma ; R = reservar parqueo

        if(estado == 'A'){
            // funcion para abrir barrera de entrada
            activarBarrera_1();
        }

        if(estado == 'C' && digitalRead(ALARM_CHECK) == LOW){
            // funcion para abrir barrera de salida
            activarBarrera_2();
        }




    }
}



//FUNCIONES DE BARRERA
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
    delay(3000); //Tiempo que podemos cambiar, representa lo que tarda el carro en pasar la barrera
    estadoInicial_1();

}

void desactivarBarrera_2(){
    digitalWrite(BARR2_2, HIGH);
    digitalWrite(BARR2_4,HIGH);
    delay(3000);
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




