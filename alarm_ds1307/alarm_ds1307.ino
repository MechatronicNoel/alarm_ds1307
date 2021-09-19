/**
 * @copyright (c) 2021 Noel Dom https://www.youtube.com/channel/UCINCDcQylATh2wS5BAYIBPg.
 *
 * @brief  Alarma basica para ds1307
 * @file    Alarm_ds1307.h
 * @version 0.1.0
 * @date  2018
 * @author  Noel Dominguez.
 */

#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal.h>

#define salida  3
RTC_DS1307 RTC;
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
int hora=0;
int minutos=0;
int segundos=0;

void setup () {
  //Inicializamos el puerto serie, wire y el modulo RTC
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    //Si quitamos el comentario de la linea siguiente, se ajusta la hora y la fecha con la del ordenador
    RTC.adjust(DateTime(__DATE__, __TIME__));    
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.write("Control Caldera Noel & Erick");
    lcd.setCursor(0,1);
    lcd.write(" Por Noel & Erick");
    delay(10000);
    lcd.clear();
    pinMode(salida,OUTPUT);
  }
  
void loop () {

    DateTime now = RTC.now();
    hora=(now.hour(),DEC);
    minutos=(now.minute(),DEC);
    segundos=(now.second(),DEC);
    //Imprimimos el dia
    Serial.print(now.day(), DEC);
    Serial.print('/');
    //Imprimimos el mes
    Serial.print(now.month(), DEC);
    Serial.print('/');
    //Imprimimos el año
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    //Imprimimos la hora
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    //Imprimimos los minutos
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    //Imprimimos los segundos
    Serial.print(now.second(), DEC);
    Serial.println();
    lcd.clear();   
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.setCursor(2,1);
    lcd.print(":");
    lcd.setCursor(3,1);
    lcd.print(now.minute(), DEC);
    lcd.setCursor(5,1);
    lcd.print(":");
    lcd.setCursor(6,1);
    lcd.print(now.second(), DEC);
    lcd.setCursor(5,0);
    lcd.print(now.day(), DEC);
    lcd.setCursor(7,0);
    lcd.print("/");
    lcd.setCursor(8,0);
    lcd.print(now.month(), DEC);
    lcd.setCursor(10,0);
    lcd.print("/");
    lcd.setCursor(11,0);
    lcd.print(now.year(), DEC);
  
    if (now.hour()== 23 && now.minute() ==10)
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Encendido");
      digitalWrite(salida,HIGH);
    }
   if (now.hour()== 23 && now.minute() ==12)
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Apagado");
      digitalWrite(salida,LOW);
     }
   delay(1000);
  //Comprobamos la hora y la enviamos por el puerto serie cada 1s
}
