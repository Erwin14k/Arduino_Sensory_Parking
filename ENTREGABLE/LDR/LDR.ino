
int LDR_values[32] = {0};
bool ldr_readed = false;
bool ldr_printed = false;
bool data_requested = false;
int last_millis = -1;

#define LDR_CHECK 13
void setup(){
    // es el serial 0 por que se comunicarara por el puerto Serial0 al puerto Serial1 de la placa de arduino
    Serial.begin(9600);
    // Serial.println("LDR READY");
    for(int i = 0; i< 32; i++){
        pinMode(i+22, INPUT);
    }

    pinMode(LDR_CHECK, INPUT);

    Serial.println("LDR READY");

}

void loop(){
    // waitForSignal();
    // if (data_requested == true){
    //     getLDR();
    //     ldr_readed = true;
    // }

    // print each 5 seconds
    printToSerial();
    delay(2000);


}

void waitForSignal(){
    
    

    if(digitalRead(LDR_CHECK) == HIGH && (millis() - last_millis) > 1000 || last_millis == -1){
        data_requested = true;
    }

    if(ldr_readed == true && data_requested == true){
        
        ldr_readed = false;
        data_requested = false;
        last_millis = millis();
        
    }
    
}

void getLDR(){
    for(int i = 0; i< 32; i++){
        LDR_values[i] = digitalRead(i+22);
    }
}

void printToSerial(){
    getLDR();
    String response = "LDR;";
        //send as string to serial monitor all the values
    for(int i = 0; i< 32; i++){
        response += LDR_values[i];
        
    }

    Serial.println(response);
}