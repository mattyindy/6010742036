#include <LiquidCrystal.h>

/*
 * 
 * 
 */
#include <stdio.h>
#define N 23
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);          //Wybór linii, do ktorych podłączony jest wyświetlacz
char linia1[16], linia2[16];
unsigned char bufor [N];
int PM25 = 20, PM10 = 20;
int wartoscPM25(unsigned char *thebuf);
int wartoscPM10(unsigned char *thebuf);
char sprawdzLancuch(unsigned char *thebuf, char leng);

void setup(){
   Serial.begin(9600);
   lcd.begin(16,2);          
   lcd.setCursor(0,0);      
}
 
void loop(){
  if(Serial.find(0x42))    
    Serial.readBytes(bufor,N);

     if(bufor[0] == 0x4d){
      if(sprawdzLancuch(bufor,N)){  
        PM25=wartoscPM25(bufor);
        PM10=wartoscPM10(bufor);  
     }
    }
   lcd.clear();
   lcd.setCursor(0,0); 
   sprintf(linia1,"PM2.5=%d ug/m3",PM25);
   lcd.print(linia1);
   lcd.setCursor(0,1);
   sprintf(linia2,"PM10=%d ug/m3",PM10);
   lcd.print(linia2);
}

int wartoscPM25(unsigned char *buf) // generacja wartosci PM2,5
{
  int PM25v;
  PM25v=((buf[11]<<8) + buf[12]);  
  return PM25v;
}

int wartoscPM10(unsigned char *buf) // generacja wartosci PM10
{
  int PM10v;
  PM10v=((buf[13]<<8) + buf[14]); 
  return PM10v;
}

bool sprawdzLancuch(unsigned char *buf, int dlugosc) // sprawdzenie poprawności lancucha
{  
  bool flaga=0;
  int suma=0;

  for(int i=0; i<(dlugosc-2); i++){
  suma+=buf[i];
  }
 suma=suma + 0x42;
 
  if(suma == ((buf[dlugosc-2]<<8)+buf[dlugosc-1]))  
  {
    suma = 0;
    flaga = 1;
  }
  return flaga;
}
