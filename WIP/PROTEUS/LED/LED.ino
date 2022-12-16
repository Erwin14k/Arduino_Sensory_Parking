int LED_values[32] = {};
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
    for(int i = 4; i<message.length(); i++){
        if(message_array[i] == '1'){
            LED_values[i-4] = 1;
        }else{
            LED_values[i-4] = 0;
        }
        
    }

    // encender los pines
    for(int i = 0; i<32; i++){
        if(LED_values[i] == 1){
            digitalWrite(i+22, HIGH);
        }else{
            digitalWrite(i+22, LOW);
        }
    }

    

}

void sonarAlarma(){
    int led_pins[32] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};
    for(int i = 500; i<700; i++){
        tone(BUZZER, i);
        delay(10);

        // led animations
        for(int j = 0; j<32; j++){
            digitalWrite(led_pins[j], HIGH);
            delay(10);
            digitalWrite(led_pins[j], LOW);
        }

    }

    for(int i = 700; i>500; i--){
        tone(BUZZER, i);
        delay(10);
    }
    
}