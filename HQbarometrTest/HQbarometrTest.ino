    #include <Wire.h>
    #include <MS5611.h>
    #include "FiltrKalmana.h"
     
    MS5611 baro;
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
      while(!baro.begin(MS5611_HIGH_RES))
      {
        Serial.println("Nie mozna znalezc czujnika MS5611, sprawdz polaczenie!");
        delay(500);
      }

     delay(300);
      // Pobieramy poczatkowe cisnienie do okreslenia wysokosci
      referencePressure = baro.readPressure();
     
      // Sprawdzamy ustawienia
      checkSettings();
    }
     
    void checkSettings()
    {
      Serial.print("Oversampling: ");
      Serial.println(baro.getOversampling());
    }
     
    void loop()
    {
      // Odczyt przekonwertowanych wartosci
      long realPressure = baro.readPressure(true);
     
      // Obliczanie wysokosci
      float absoluteAltitude = baro.getAltitude(realPressure);
      uint16_t pofiltrze = (uint16_t)(filtrk.update(absoluteAltitude, 0)*100);
      
      //Serial.print(" m\t");
      Serial.println(pofiltrze);
    }

