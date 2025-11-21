/*
 * Jemuran Otomatis
 * Sistem jemuran otomatis yang menggunakan sensor hujan untuk mendeteksi cuaca
 * dan servo motor untuk menggerakkan jemuran masuk/keluar secara otomatis
 * 
 * Komponen:
 * - Sensor hujan digital
 * - Servo motor SG90
 * - Arduino Uno
 */

#include <Arduino.h>
#include <Servo.h>

// Definisi pin dan konstanta
#define PIN_SENSOR_POWER  7      // Pin power untuk sensor hujan
#define PIN_SENSOR_INPUT  8      // Pin input data sensor hujan
#define PIN_SERVO         9      // Pin servo motor
#define JEMURAN_MASUK     0      // Posisi servo saat jemuran masuk (0 derajat)
#define JEMURAN_KELUAR    90     // Posisi servo saat jemuran keluar (90 derajat)

// Inisialisasi objek
Servo servoJemuran;

// Variabel global untuk tracking posisi
int posisiSebelumnya = -1;  // Tracking posisi servo sebelumnya

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  Serial.println("=== Jemuran Otomatis ===");
  
  // Inisialisasi servo motor
  servoJemuran.attach(PIN_SERVO);
  servoJemuran.write(JEMURAN_MASUK);  // Posisi awal: jemuran di dalam (0 derajat)
  posisiSebelumnya = JEMURAN_MASUK;   // Set posisi awal
  
  // Konfigurasi pin sensor hujan
  pinMode(PIN_SENSOR_POWER, OUTPUT);
  // Tambahan kode ini
  pinMode(PIN_SENSOR_INPUT, INPUT);  // PENTING: Set pin input sensor
  digitalWrite(PIN_SENSOR_POWER, LOW);  // Matikan sensor di awal
  
  Serial.println("Sistem siap beroperasi...");
  Serial.println("Posisi awal: Jemuran MASUK (0 derajat)");
  delay(2000); // Tunggu sistem stabil
}

/*
 * Fungsi untuk membaca sensor hujan
 * Return: 1 jika cerah, 0 jika hujan
 */
int bacaSensorHujan() {
  // Nyalakan sensor
  digitalWrite(PIN_SENSOR_POWER, HIGH);
  
  // Delay pengecekan sensor 2 detik
  delay(2000);
  
  // Baca nilai sensor
  int nilaiSensor = digitalRead(PIN_SENSOR_INPUT);
  
  // Matikan sensor untuk menghemat daya
  digitalWrite(PIN_SENSOR_POWER, LOW);
  
  return nilaiSensor;
}

void loop() {
  // Baca sensor hujan
  int sensorHujan = bacaSensorHujan();
  
  // Tampilkan output sensor seperti format yang diminta
  Serial.print("Digital Output: ");
  Serial.println(sensorHujan);
  
  Serial.print("Status: ");
  if (sensorHujan == 1) {
    Serial.println("Clear");
  } else {
    Serial.println("It's raining");
  }
  
  // Tentukan posisi servo berdasarkan sensor
  int posisiBaru;
  if (sensorHujan == 0) {
    // Jika sensor = 0 (hujan), jemuran masuk (servo ke 0 derajat)
    posisiBaru = JEMURAN_MASUK;
  } else {
    // Jika sensor = 1 (cerah), jemuran keluar (servo ke 90 derajat)
    posisiBaru = JEMURAN_KELUAR;
  }
  
  // Tampilkan status posisi jemuran hanya jika ada perubahan
  if (posisiBaru != posisiSebelumnya) {
    // Gerakkan servo ke posisi baru
    servoJemuran.write(posisiBaru);
    
    // Tampilkan status perubahan
    Serial.print(">>> Posisi Jemuran: ");
    if (posisiBaru == JEMURAN_MASUK) {
      Serial.println("MASUK (0 derajat)");
    } else {
      Serial.println("KELUAR (90 derajat)");
    }
    
    // Update posisi sebelumnya
    posisiSebelumnya = posisiBaru;
    
    delay(1000); // Beri waktu servo bergerak
  }
  
  Serial.println("---");
  
  // Ulangi proses setiap 5 detik
  delay(5000);
}
