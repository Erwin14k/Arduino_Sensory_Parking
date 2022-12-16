

// define pin for buzzer
#define BUZZER A0

bool sonar_alarma = false;

// define pins for leds
int parking_place_pin[4][3] = {
	// park# = {green, yellow, red}
	{2, 3, 4},
	{5, 6, 7},
	{8, 9, 10},
	{11, 12, 13}

};


void setup(){
	pinMode(BUZZER, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	if(digitalRead(13) == HIGH){
		sonar_alarma = !sonar_alarma;
	}
	
	if(sonar_alarma == true){
		Serial.println("esperando");
		delay(1000);
		if(Serial.available() > 0){
			int data = Serial.read();
			if(data != 0){
				alarm(data);
				
			}else{
				sonar_alarma = false;
			}
		}
	}
	
}

// alarm trough buzzer
void alarm(int park_number)
{
	int* leds = get_park_leds(park_number);
	// police alarm through buzzer with frecuencies
	for (int i = 500; i < 700; i++){ // for police siren
		
		// delay(15);

		// led flashing
		if(i%2 == 0){
			tone(BUZZER, i);
			for (int j = 0; j < 3; j++){
				digitalWrite(leds[j], HIGH);
				
				delay(5);
				
			}
		}

		else{
			tone(BUZZER, i);
			for (int j = 0; j < 3; j++){
				digitalWrite(leds[j], LOW);
				
				delay(5);
				
			}
			
		}
	}
	for (int i = 700; i > 500; i--){
		if(i%2 == 0){
			tone(BUZZER, i);
			for (int j = 0; j < 3; j++){
				digitalWrite(leds[j], HIGH);
				
				delay(5);
				
			}
		}

		else{
			tone(BUZZER, i);
			for (int j = 0; j < 3; j++)
			{
				digitalWrite(leds[j], LOW);
				
				delay(5);
				
			}
			
		}
	}
	noTone(BUZZER);

}

int* get_park_leds(int park_number){
	
	if (park_number == 0){
		return parking_place_pin[0];
	}
	else{
		return parking_place_pin[park_number - 1];
	}
	
}