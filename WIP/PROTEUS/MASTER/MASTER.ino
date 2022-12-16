#define LDR_CHECK 13
#define LED_CHECK 12


bool ldr_data_ready = false;
String ldr_data = "";

bool led_test = false;

char estado = '0';	

// buzzer


void setup(){

    // empezar puerto serial 0 => PC
    Serial.begin(9600);
    Serial.println("MASTER READY");

    // empezar puerto serial 1 => ARDUINO LDR
    // empezar puerto serial 2 => ARDUINO MASTER
    
    Serial1.begin(9600);
    Serial2.begin(9600);

    pinMode(LDR_CHECK, OUTPUT);
    pinMode(LED_CHECK, OUTPUT);

}

void loop(){

    // check if serial
    if(Serial.available() > 0){

    }
    
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

    if (Serial.available() > 0){
        estado = Serial.read();


        // switch de estados

        // estados para bluetooth | A = abrir entrada ; C = abrir salida ; D = desactivar alarma ; R = reservar parqueo

        if(estado == 'A'){
            // funcion para abrir barrera de entrada
        }

        if(estado == 'C'){
            // funcion para abrir barrera de salida
        }

        if(estado == 'D'){
            // funcion para desactivar alarma
            desactivarAlarma();
        }



    }
}


