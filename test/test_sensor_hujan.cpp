/*
 * Test Sensor Hujan - Debugging Script
 * File ini untuk testing sensor hujan secara terpisah
 * 
 * Cara pakai:
 * 1. Upload code ini ke Arduino
 * 2. Buka Serial Monitor (9600 baud)
 * 3. Semprotkan air ke pad sensor
 * 4. Perhatikan perubahan nilai sensor
 */

#include <Arduino.h>

// Definisi pin
#define PIN_SENSOR_POWER  7      // Pin power untuk sensor hujan
#define PIN_SENSOR_INPUT  8      // Pin input data sensor hujan

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("  TEST SENSOR HUJAN - DEBUG MODE");
  Serial.println("=================================");
  Serial.println();
  
  // Konfigurasi pin
  pinMode(PIN_SENSOR_POWER, OUTPUT);
  pinMode(PIN_SENSOR_INPUT, INPUT);

  // Inisialisasi pin sensor power LOW
  pinMode(PIN_SENSOR_POWER, LOW);
  
  Serial.println("Konfigurasi Pin:");
  Serial.print("  - Sensor Power: Pin ");
  Serial.println(PIN_SENSOR_POWER);
  Serial.print("  - Sensor Input: Pin ");
  Serial.println(PIN_SENSOR_INPUT);
  Serial.println();
  
  Serial.println("Instruksi:");
  Serial.println("  1. Pastikan sensor terpasang dengan benar");
  Serial.println("  2. Semprotkan air ke pad sensor");
  Serial.println("  3. Nilai sensor akan berubah dari 1 ke 0");
  Serial.println();
  Serial.println("Membaca sensor setiap 1 detik...");
  Serial.println("---------------------------------");
  
  delay(2000);
}

void loop() {
  // Test 1: Tanpa power control (sensor selalu ON)
  digitalWrite(PIN_SENSOR_POWER, HIGH);
  delay(200); // Beri waktu sensor stabil
  
  int nilaiSensor = digitalRead(PIN_SENSOR_INPUT);
  
  // Tampilkan hasil
  Serial.print("Waktu: ");
  Serial.print(millis() / 1000);
  Serial.print("s | Sensor: ");
  Serial.print(nilaiSensor);
  Serial.print(" | Status: ");
  
  if (nilaiSensor == 0) {
    Serial.println("HUJAN TERDETEKSI! ☔");
  } else {
    Serial.println("CERAH (Tidak ada air)");
  }
  
  delay(1000); // Baca setiap 1 detik
}

