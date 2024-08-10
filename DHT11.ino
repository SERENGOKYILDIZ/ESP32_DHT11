#include <SimpleTimer.h>

//Sıcaklık sensörü için
#include <DHT.h>
#define DHTTYPE DHT11      // Sensör tipi (DHT11)
#define temp_pin 33

float sicaklik;

SimpleTimer timer_temp;
DHT dht(temp_pin, DHTTYPE); // DHT kütüphanesini sensör tipi ve veri pini ile başlat
//////////////////////////////////////////////////

void Reading_Temp()
{
  // Nem ve sıcaklık değerlerini oku
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Okuma hatalarını kontrol et
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT sensöründen veri okunamadı!");
    return;
  }

  sicaklik = t;

  // Seri port üzerinden sıcaklık ve nem değerlerini yazdır
  Serial.print("Nem: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Sıcaklık: ");
  Serial.print(t);
  Serial.println(" C");
}

void setup() {
  Serial.begin(115200);  // Seri haberleşme başlat

  //Sıcaklık için tanımlamalar
  dht.begin();           // DHT sensörünü başlat
  timer_temp.setInterval(2000, Reading_Temp);
}

void loop() {
  timer_temp.run();
  delay(2);
}
