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

// PANTALLA
#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

byte b1[] = {
  B10000,
  B00001,
  B10010,
  B11010,
  B11001,
  B11100,
  B11111,
};

byte b2[] = {
  B00011,
  B10000,
  B01000,
  B01011,
  B10011,
  B00111,
  B11111
};

byte b3[] = {
  B01100,
  B00001,
  B00010,
  B11010,
  B11001,
  B11100,
  B11111,
  B11111
};


byte b4[] = {
  B00001,
  B10000,
  B01001,
  B01011,
  B10011,
  B00111,
  B11111
};

byte b6[] = {
  B00001,
  B00000,
  B00000,
  B00001,
  B01111,
  B01111,
  B11111,
};

byte a1[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B10000,
};

byte a2[] = {
  B11111,
  B11111,
  B11100,
  B11001,
  B10011,
  B00111,
  B00000,
};

byte a3[] = {
  B11111,
  B11111,
  B00000,
  B11110,
  B11111,
  B11111,
  B00000,
};

byte a4[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B00111,
  B10011,
  B00001,
};

byte a6[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
};


//CARRITO CON LA EQUIS

byte b1_2[] = {
  B10000,
  B00001,
  B10010,
  B11000,
  B11001,
  B10100,
  B01111,
};

byte b2_2[] = {
  B00011,
  B10000,
  B01000,
  B01011,
  B10011,
  B00111,
  B11111
};

byte b3_2[] = {
  B01100,
  B00001,
  B00010,
  B11010,
  B11001,
  B11100,
  B11111,
  B11111
};


byte b4_2[] = {
  B00001,
  B10000,
  B01001,
  B00011,
  B10011,
  B00101,
  B11110
};

byte a1_2[] = {
  B01111,
  B10111,
  B11011,
  B11101,
  B11110,
  B11110,
  B10000,
};

byte a2_2[] = {
  B11111,
  B11111,
  B11100,
  B11001,
  B10011,
  B00111,
  B00000,
};

byte a3_2[] = {
  B11111,
  B11111,
  B00000,
  B11110,
  B11111,
  B11111,
  B00000,
};

byte a4_2[] = {
  B11110,
  B11101,
  B11011,
  B10111,
  B00111,
  B10011,
  B00001,
};

//RESERVADO
byte reserved[] = {
  B11111,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B11111
};

//DISPONIBLE

byte check[] = {
  B11111,
  B11111,
  B11110,
  B11101,
  B01011,
  B10111,
  B11111,
  B11111
};

byte check2[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};

//OCUPADO
byte equis[] = {
  B11111,
  B01110,
  B10101,
  B11011,
  B10101,
  B01110,
  B11111,
  B11111
};

byte equis2[] = {
  B00000,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B00000,
  B00000
};

byte flechaIzquierda[] = {
  B00000,
  B00100,
  B01100,
  B11111,
  B11111,
  B01100,
  B00100,
  B00000
};

//total
byte parqueo[] = {
  B11111,
  B10001,
  B10101,
  B10001,
  B10111,
  B10111,
  B11111
};

int x1 = 16;
int x2 = 17;
int x3 = 18;
int x4 = 19;
int x5 = 21;




int parqueos_disponibles = 0;
int parqueos_ocupados = 0;
int parqueos_reservados = 0;

void setup() {

  // empezar puerto serial 0 => PC
  Serial.begin(9600);
  Serial.println("MASTER READY");

  // empezar puerto serial 1 => ARDUINO LDR
  // empezar puerto serial 2 => ARDUINO MASTER

  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial2.println("MASTER READY");

  pinMode(ALARM_CHECK, INPUT);

  pinMode(BARR1_1, OUTPUT);
  pinMode(BARR1_2, OUTPUT);
  pinMode(BARR1_3, OUTPUT);
  pinMode(BARR1_4, OUTPUT);

  pinMode(BARR2_1, OUTPUT);
  pinMode(BARR2_2, OUTPUT);
  pinMode(BARR2_3, OUTPUT);
  pinMode(BARR2_4, OUTPUT);

  //AL INICIO COLOCAR LOS MOTORES EN SU ESTADO INICIAL
  estadoInicial_1();
  estadoInicial_2();

    //PANTALLA
    lcd.begin(16, 2);

}

void loop() {
    delay(1000);
    checkForIncomingPetitions();
    
    if(parqueos_disponibles == 0){
        nohayparqueos();
        delay(1000);
    }else{
        ocupaciones(parqueos_disponibles, parqueos_ocupados, parqueos_reservados);
        delay(1000);
        parqueosdisponibles(parqueos_disponibles);
        delay(1000);
    }
    
    
    
    

}

// LED;<num_parqueo>;<estado>
// estado: reservado = 1, no reservado = 0; 2 = alarma desactivada
void enviarReservacion(int parqueo) {
  digitalWrite(LED_CHECK, HIGH);
  Serial1.print("LED;4;1");
  Serial2.print("Reservacion enviada");
  Serial.print("LED;4;1");
  delay(1000);
  digitalWrite(LED_CHECK, LOW);

}

void desactivarAlarma() {
  digitalWrite(LED_CHECK, HIGH);
  Serial1.print("LED;4;2");
  delay(1000);
  digitalWrite(LED_CHECK, LOW);
}

void sonarAlarma() {

}

void checkForIncomingPetitions() {
    char estado = '0';
    // Serial1 es bluetooth
    if (Serial1.available() > 0) {
        estado = Serial1.read();


        // switch de estados

        // estados para bluetooth | A = abrir entrada ; C = abrir salida ; D = desactivar alarma ; R = reservar parqueo

        if (estado == 'A') {
        // funcion para abrir barrera de entrada
            activarBarrera_1();
        }

        if (estado == 'C' && digitalRead(ALARM_CHECK) == LOW) {
        // funcion para abrir barrera de salida
            activarBarrera_2();
        }
        }
    String mensaje = "";
    while(Serial.available()> 0){
        mensaje += (char)Serial.read();
        delay(10);
    }

    if(mensaje != ""){
        Serial2.println("Recibido");
        Serial2.println(mensaje);
        interpretarMensaje(mensaje);
    }
    

    
}

void interpretarMensaje(String msg){
    // parse msg to array
    String mensaje = msg;
    // convertir a arreglo
    char mensaje_array[mensaje.length()];
    mensaje.toCharArray(mensaje_array, mensaje.length());
    int longitud = mensaje.length();

    String disponibles="";	
    String reservados="";
    String ocupados="";

    // P;<disponibles>;<reservados>;<ocupados>
    if(mensaje_array[0]  == 'P' && mensaje_array[1] == ';'){
        for(int i=2; i<longitud; i++){
            if(mensaje_array[i] == ';'){
                for(int j=i+1; j<longitud; j++){
                    if(mensaje_array[j] == ';'){
                        for(int k=j+1; k<longitud ; k++){
                            ocupados += mensaje_array[k];
                        }
                        break;
                    }
                    reservados += mensaje_array[j];
                }
                break;
            }
            disponibles += mensaje_array[i];
        }
    }

    parqueos_disponibles = disponibles.toInt();
    parqueos_reservados = reservados.toInt();
    parqueos_ocupados = ocupados.toInt();

    
    


}



//FUNCIONES DE BARRERA
void activarBarrera_1() {
  //Primero giro 90 grados en sentido antihorario
  digitalWrite(BARR1_4, LOW);
  digitalWrite(BARR1_2, LOW);

  digitalWrite(BARR1_1, HIGH);
  delay(3000);
  desactivarBarrera_1();
}

void activarBarrera_2() {
  //Primero giro 90 grados en sentido antihorario
  digitalWrite(BARR2_4, LOW);
  digitalWrite(BARR2_2, LOW);

  digitalWrite(BARR2_1, HIGH);
  delay(3000);
  desactivarBarrera_2();
}

void desactivarBarrera_1() {
  digitalWrite(BARR1_2, HIGH);
  digitalWrite(BARR1_4, HIGH);
  delay(3000); //Tiempo que podemos cambiar, representa lo que tarda el carro en pasar la barrera
  estadoInicial_1();

}

void desactivarBarrera_2() {
  digitalWrite(BARR2_2, HIGH);
  digitalWrite(BARR2_4, HIGH);
  delay(3000);
  estadoInicial_2();

}

void estadoInicial_1() {
  digitalWrite(BARR1_1, LOW);
  digitalWrite(BARR1_2, LOW);
  digitalWrite(BARR1_4, LOW);
}

void estadoInicial_2() {
  digitalWrite(BARR2_1, LOW);
  digitalWrite(BARR2_2, LOW);
  digitalWrite(BARR2_4, LOW);
}

// funciones de pantalla
void parqueosdisponibles(int disp) {
  while (x1 >= -16) {
    carritoDisp(disp);
  }
  x1 = 16;
  x2 = 17;
  x3 = 18;
  x4 = 19;
  x5 = 21;
}

void nohayparqueos() {
  while (x1 >= -14) {
    carritoOcup();
  }
  x1 = 16;
  x2 = 17;
  x3 = 18;
  x4 = 19;
  x5 = 21;
}

//SE MUESTRA CUANDO EL PARQUEO ESTÁ VACÍO
void carritoDisp(int disp) {
  lcd.begin(16, 2);
  lcd.createChar(1, a1);
  lcd.createChar(2, a2);
  lcd.createChar(3, b1);
  lcd.createChar(4, b2);
  lcd.setCursor(x1, 0); lcd.write(1);
  lcd.setCursor(x2, 0); lcd.write(2);
  lcd.setCursor(x1, 1); lcd.write(3);
  lcd.setCursor(x2, 1); lcd.write(4);

  lcd.createChar(5, a3);
  lcd.createChar(6, a4);
  lcd.createChar(7, b3);
  lcd.createChar(8, b4);
  lcd.setCursor(x3, 0); lcd.write(5);
  lcd.setCursor(x4, 0); lcd.write(6);
  lcd.setCursor(x3, 1); lcd.write(7);
  lcd.setCursor(x4, 1); lcd.write(8);

  lcd.setCursor(x5, 0);
  lcd.print(disp);

  lcd.setCursor(x5, 1);
  lcd.print("disponibles");

  x1--;
  x2--;
  x3--;
  x4--;
  x5--;
  delay(50);
  checkForIncomingPetitions();
  lcd.clear();
}

//SE MUESTRA CUANDO EL PARQUEO YA ESTÁ LLENO
void carritoOcup() {
  lcd.begin(16, 2);
  lcd.createChar(1, a1_2);
  lcd.createChar(2, a2_2);
  lcd.createChar(3, b1_2);
  lcd.createChar(4, b2_2);
  lcd.setCursor(x1, 0); lcd.write(1);
  lcd.setCursor(x2, 0); lcd.write(2);
  lcd.setCursor(x1, 1); lcd.write(3);
  lcd.setCursor(x2, 1); lcd.write(4);

  lcd.createChar(5, a3_2);
  lcd.createChar(6, a4_2);
  lcd.createChar(7, b3_2);
  lcd.createChar(8, b4_2);
  lcd.setCursor(x3, 0); lcd.write(5);
  lcd.setCursor(x4, 0); lcd.write(6);
  lcd.setCursor(x3, 1); lcd.write(7);
  lcd.setCursor(x4, 1); lcd.write(8);

  lcd.setCursor(x5, 0);
  lcd.print(" Parqueo ");

  lcd.setCursor(x5, 1);
  lcd.print("x Lleno x");

  x1--;
  x2--;
  x3--;
  x4--;
  x5--;
  delay(50);
  checkForIncomingPetitions();
  lcd.clear();
}

//Para mostrar la ocupación -> Total de parqueos, disponibles, reservados y ocupados
void ocupaciones(int disponible, int ocupado, int reservado) {
  lcd.createChar(1, parqueo);
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(1, 0);
  lcd.print("32");

  lcd.createChar(4, reserved);
  lcd.setCursor(0, 1);
  lcd.write(4);
  lcd.setCursor(1, 1);
  lcd.print(reservado);

  lcd.createChar(2, check);
  lcd.setCursor(7, 0);
  lcd.write(2);
  lcd.setCursor(8, 0);
  lcd.print(disponible);

  lcd.createChar(3, equis);
  lcd.setCursor(7, 1);
  lcd.write(3);
  lcd.setCursor(8, 1);
  lcd.print(ocupado);

}