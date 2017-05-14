    #include <Wire.h>
    #include <MS5611.h>
    #include "FiltrKalmana.h"
     
    MS5611 ms5611;
    FiltrKalmanaClass filtrk;
     
    double referencePressure;
     
    void setup()
    {
      Serial.begin(115200);
      filtrk.init();
     
      // Inicjalizacja MS5611
      Serial.println("Inicjalizacja MS5611 Sensor");
     
      // Ultra high resolution: MS5611_ULTRA_HIGH_RES
      // (default) High resolution: MS5611_HIGH_RES
      // Standard: MS5611_STANDARD
      // Low power: MS5611_LOW_POWER
      // Ultra low power: MS5611_ULTRA_LOW_POWER
      while(!ms5611.begin(MS5611_HIGH_RES))
      {
        Serial.println("Nie mozna znalezc czujnika MS5611, sprawdz polaczenie!");
        delay(500);
      }

     delay(300);
      // Pobieramy poczatkowe cisnienie do okreslenia wysokosci
      referencePressure = ms5611.readPressure();
     
      // Sprawdzamy ustawienia
      checkSettings();
    }
     
    void checkSettings()
    {
      Serial.print("Oversampling: ");
      Serial.println(ms5611.getOversampling());
    }
     
    void loop()
    {
      // Odczyt przekonwertowanych wartosci
      long realPressure = ms5611.readPressure();
     
      // Obliczanie wysokosci
      float absoluteAltitude = ms5611.getAltitude(realPressure);
      float relativeAltitude = ms5611.getAltitude(realPressure, referencePressure);
      float pofiltrze = filtrk.update(absoluteAltitude, 0);
     
      Serial.print(" absoluteAltitude = ");
      Serial.print(absoluteAltitude);
      Serial.print(" m\t relativeAltitude = ");
      Serial.print(relativeAltitude);    
      Serial.print(" m\t");
      Serial.println(pofiltrze*10);
    }

