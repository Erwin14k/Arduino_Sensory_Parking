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

void setup() {
  //Iniciar el tamaño del LCD
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  ocupaciones(16,8,8);
  delay(3000);
  parqueosdisponibles(8);
  delay(3000);
  nohayparqueos();
  delay(3000);
}

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
  delay(100);
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
  delay(100);
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
