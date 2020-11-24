//Proyek #36: Kunci Elektronik dengan Password
#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h>

Password password = Password( "123456" );

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
int x = 0; 
int a = 0;
int led = 13;

const byte JmlBaris = 4;
const byte JmlKolom = 3;

char keys[JmlBaris][ JmlKolom] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };//matriks 4x3 menunjukkan keypad mana yang ditekan

  byte PinBaris [JmlBaris] = { 3, 2, 1, 0};

  byte PinKolom[JmlKolom] = { 4, 5, 6 };

Keypad syahwil = Keypad( makeKeymap(keys), PinBaris,   PinKolom, JmlBaris, JmlKolom ); 
void setup() { 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Power On...");
  lcd.setCursor(0,1);
  lcd.print("...by TT3ABCD...");
  delay(500);
  lcd.clear();
  syahwil.addEventListener(keypadEvent);
}
void loop() {
  pinMode(led, OUTPUT);
   if (a==0) {
     lcd.setCursor(0, 0);
     lcd.print("Pintu Elektronik!");
     lcd.setCursor(0, 1);
     lcd.print("Masukan Kode....");
     lcd.noDisplay();
     delay(250);
     lcd.display();
     delay(250);
}
  syahwil.getKey();
}
void keypadEvent(KeypadEvent eKey){ 
  switch (syahwil.getState()){
    case PRESSED:
      if (a == 0){ 
         lcd.clear();
         a = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("Kode :          ");
      lcd.setCursor(x, 1);
switch (eKey){
case '*': 
  checkPassword();
  password.reset(); 
  break;
case '#': 
  password.reset(); 
  lcd.setCursor(0, 0); 
  lcd.clear();
  x=0; 
  a=0;
  break;
default:
  password.append(eKey);
  lcd.print("*");
  x++;}
}
}
void checkPassword(){
if (password.evaluate()){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" KODE DITERIMA");
  lcd.setCursor(0, 1);
  lcd.print(" Silahkan Masuk!");
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  x = 0;
  a = 0; 
 } else {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  KODE DITOLAK ");
     lcd.setCursor(0, 1);
     lcd.print("================");

 for(int i=0; i < 5; i++) { 
    lcd.noDisplay();
    delay(250);
    lcd.display();
    delay(250);
    x=0;
    a=0;
}
}
}
