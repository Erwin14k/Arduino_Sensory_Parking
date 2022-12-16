int LED_values[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int last_millis = -1;

bool led_data_ready = false;
String led_data = "";

#define LED_CHECK  13


#define BUZZER A0


void setup(){
    // SOLO RECIBIRA INFORMACION
    Serial.begin(9600);
    for(int i = 0; i<32; i++){
        pinMode(i+22, OUTPUT);
        digitalWrite(i+22, LOW);
    }

    pinMode(LED_CHECK, INPUT);

}

void loop(){
    waitForSignal();
    

    

}

void waitForSignal(){
    // leer puerto serial
    String message = "";
    while(Serial.available()> 0){
        message += (char)Serial.read();
        delay(10);
    }
    if(message != ""){
        Serial.println("Recibido: ");
        Serial.println(message);    
        interpretarLED(message);
        message = "";
    }

    encenderLED();

    
    
    
}

void askLED(){
    // read Serial info
    String response = "";
    while(Serial.available() > 0){
        response += (char)Serial.read();
    }
    Serial.println("Recibido: ");
    Serial.println(response);

    led_data = "";
    led_data = response;



}

void interpretarLED(String message){
    // convertir mensaje a arreglo de caracteres
    Serial.println("Interpretando");
    Serial.println(message);
    char message_array[message.length()];
    message.toCharArray(message_array, message.length());

    //  los primeros 4 elementos son "LED;" el resto son 32 numeros equivalentes a los pines que hay que encender en amarillo
    if(message_array[0] == '0' && message_array[1] ==';'){
        String espacio = "";
        for(int i = 2; i<message.length(); i++){
            espacio += message_array[i];
        }

        if(espacio.toInt() != 0){
            sonarAlarma(espacio.toInt());
        }
        
    }

    if(message_array[0] == 'L' && message_array[1] == 'E' && message_array[2] == 'D' && message_array[3] == ';'){
        
    
        for(int i = 4; i<message.length(); i++){
                if(message_array[i] == '1'){
                    LED_values[i-4] = 1;
                }

                if(message_array[i] == '0'){
                    LED_values[i-4] = 0;
                }
                
        }
    }

}

void sonarAlarma(int espacio){
    for(int i = 600; i<700; i++){
        tone(BUZZER, i);
        digitalWrite(espacio+21, HIGH);
        delay(10);
        digitalWrite(espacio+21, LOW);
        delay(10);

    }
    noTone(BUZZER);

}

void encenderLED(){
    // encender los pines
        for(int i = 0; i<32; i++){
            
            if(LED_values[i] == 1){
                digitalWrite(i+22, HIGH);
            }else{
                digitalWrite(i+22, LOW);
            }
        }
}

