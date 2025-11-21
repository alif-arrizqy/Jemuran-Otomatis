# Troubleshooting Sensor Hujan

## Masalah: Sensor Tidak Mendeteksi Air

### Gejala
- Ketika air disemprotkan ke pad sensor, status "hujan" tidak muncul
- Servo tidak bergerak meskipun ada air di sensor
- Serial Monitor hanya menampilkan "Clear" terus menerus

---

## Langkah-langkah Pengecekan

### 1. **Cek Koneksi Hardware**

#### Koneksi Modul Sensor Hujan ke Arduino:
```
Modul Sensor Hujan    →    Arduino
─────────────────────────────────
VCC                   →    5V
GND                   →    GND
DO (Digital Output)   →    Pin 8
```

#### Pastikan:
- ✅ Semua kabel terpasang dengan benar
- ✅ Tidak ada kabel yang longgar
- ✅ Pin tidak bengkok atau rusak
- ✅ Arduino mendapat power yang cukup (USB atau adapter)

---

### 2. **Cek Modul Sensor Hujan**

#### A. LED Indikator
Modul sensor hujan biasanya memiliki 2 LED:
- **LED Power (merah)**: Menyala ketika modul mendapat power
- **LED Status (hijau/biru)**: Berkedip/berubah ketika mendeteksi air

#### B. Potensiometer (Variable Resistor)
- Modul sensor hujan memiliki potensiometer untuk **mengatur sensitivitas**
- Putar searah jarum jam = sensitivitas TURUN (butuh lebih banyak air)
- Putar berlawanan jarum jam = sensitivitas NAIK (lebih sensitif)

**SOLUSI**: Coba putar potensiometer ke kiri (berlawanan jarum jam) untuk meningkatkan sensitivitas!

---

### 3. **Testing dengan Code Debug**

#### Langkah 1: Upload Code Test Sensor
```bash
# Gunakan file test_sensor_hujan.cpp
1. Buka file: test/test_sensor_hujan.cpp
2. Upload ke Arduino
3. Buka Serial Monitor (9600 baud)
4. Semprotkan air ke pad sensor
5. Perhatikan apakah nilai berubah dari 1 ke 0
```

#### Langkah 2: Amati Output
**Normal (Tanpa Air):**
```
Waktu: 5s | Sensor: 1 | Status: CERAH (Tidak ada air)
```

**Ketika Ada Air:**
```
Waktu: 6s | Sensor: 0 | Status: HUJAN TERDETEKSI! ☔
```

Jika nilai sensor **TIDAK berubah** dari 1 ke 0 saat ada air:
- Sensor mungkin rusak
- Sensitivitas terlalu rendah (putar potensiometer)
- Koneksi DO ke pin 8 bermasalah

---

### 4. **Periksa Konfigurasi Pin**

Pastikan kode Anda sudah memiliki baris ini di `setup()`:

```cpp
pinMode(PIN_SENSOR_INPUT, INPUT);  // Set pin input sensor
```

❌ **SALAH** (akan menyebabkan sensor tidak terbaca):
```cpp
// Tidak ada pinMode untuk PIN_SENSOR_INPUT
```

✅ **BENAR**:
```cpp
pinMode(PIN_SENSOR_POWER, OUTPUT);
pinMode(PIN_SENSOR_INPUT, INPUT);  // WAJIB ada!
```

---

### 5. **Cek Logika Sensor**

Sensor hujan digital memiliki output:
- **HIGH (1)** = Tidak ada air / CERAH
- **LOW (0)** = Ada air / HUJAN

Pastikan logika di kode Anda sesuai:

```cpp
if (sensorHujan == 0) {
    // HUJAN → Jemuran MASUK
    posisiBaru = JEMURAN_MASUK;
} else {
    // CERAH → Jemuran KELUAR
    posisiBaru = JEMURAN_KELUAR;
}
```

---

### 6. **Alternatif: Bypass Pin Power Control**

Beberapa modul sensor hujan tidak memerlukan pin power control terpisah. Coba modifikasi koneksi:

#### Opsi A: Koneksi Langsung (Tanpa Power Control)
```
Modul Sensor    →    Arduino
──────────────────────────────
VCC             →    5V (langsung)
GND             →    GND
DO              →    Pin 8
```

#### Opsi B: Update Code
Ubah fungsi `bacaSensorHujan()` menjadi:

```cpp
int bacaSensorHujan() {
  // Sensor selalu ON (tidak perlu power control)
  int nilaiSensor = digitalRead(PIN_SENSOR_INPUT);
  
  Serial.print("[DEBUG] Nilai RAW Sensor: ");
  Serial.println(nilaiSensor);
  
  return nilaiSensor;
}
```

Dan di `setup()`:
```cpp
// Koneksi VCC sensor langsung ke 5V Arduino
// Tidak perlu PIN_SENSOR_POWER
pinMode(PIN_SENSOR_INPUT, INPUT);
```

---

## Checklist Troubleshooting

Gunakan checklist ini untuk memastikan semua sudah benar:

- [ ] Koneksi VCC, GND, DO sudah benar
- [ ] LED power sensor menyala
- [ ] Pin 8 Arduino terhubung ke DO sensor
- [ ] Code sudah ada `pinMode(PIN_SENSOR_INPUT, INPUT)`
- [ ] Upload code test sensor dan cek nilai raw
- [ ] Putar potensiometer untuk atur sensitivitas
- [ ] Test dengan air yang cukup (bukan hanya tetes kecil)
- [ ] Gunakan pad sensor yang besar (bukan modul kontrol)

---

## Kemungkinan Masalah Umum

### 1. **Salah Pad/Modul**
Sensor hujan terdiri dari 2 bagian:
- **Pad Sensor (board besar)**: Tempat menempelkan air
- **Modul Control (board kecil)**: Yang dihubungkan ke Arduino

Pastikan air disemprotkan ke **PAD SENSOR**, bukan modul control!

### 2. **Air Terlalu Sedikit**
- Gunakan air yang cukup, bukan hanya tetesan kecil
- Semprotkan air merata ke pad sensor

### 3. **Sensor Kotor/Berkarat**
- Bersihkan pad sensor dengan tisu
- Jangan biarkan air mengering di pad (bisa menyebabkan korosi)

### 4. **Sensor Rusak**
Jika semua sudah dicek dan sensor tetap tidak merespons:
- Coba sensor di pin lain (misalnya pin 9 atau 10)
- Test dengan multimeter (cek apakah DO berubah dari 5V ke 0V saat ada air)
- Ganti sensor baru jika memang rusak

---

## Hubungi Bantuan

Jika masih belum teratasi, catat informasi berikut:
1. Output Serial Monitor (copy paste)
2. Foto koneksi hardware
3. Tipe modul sensor yang digunakan
4. Apakah LED di modul sensor menyala?
5. Apakah servo bisa bergerak saat test manual?

