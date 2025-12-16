# 🔥 IoT Smart Firefighting-Robot-with-Articulatic-Arm

Projek ini adalah sistem robot pemadam api otomatis berbasis IoT yang menggunakan **NodeMCU ESP8266**. Robot ini memiliki lengan robotik (4 DOF) untuk mengarahkan selang air dan memadamkan api berdasarkan prioritas sensor.

Data status robot, posisi lengan, dan pembacaan sensor dikirim secara real-time ke server lokal dan ditampilkan pada **Web Dashboard**.

![prototype 5](https://github.com/user-attachments/assets/a310b10e-cf78-4fda-ae91-9679c9dcaa38)

## 🌟 Fitur Utama
* **Deteksi Api Cerdas:** Menggunakan 3 sensor (Kiri, Tengah, Kanan) dengan logika prioritas.
* **Lengan Robotik 4-DOF:** Bergerak otomatis mengarahkan nozzle air ke titik api.
* **Real-time Monitoring:** Dashboard Web menampilkan grafik intensitas api dan animasi posisi lengan.
* **Logging Database:** Menyimpan riwayat aktivitas dan status sensor ke MySQL.

## 🛠️ Tech Stack & Hardware

### Software
* **Firmware:** Arduino IDE (C++)
* **Backend:** PHP (Native)
* **Database:** MySQL
* **Frontend:** HTML5, CSS3, JavaScript

### Hardware
* **Microcontroller:** NodeMCU ESP8266
* **Actuators:** 4x Servo Motor (SG90/MG90s), 1x Mini Water Pump
* **Sensors:** 1x Flame Sensor 5 channel (analog & digital)
* **Power:** Baterai 18650, Modul Step-down XL4015 (5A), Relay 1 Channel

## 🔌 Wiring Diagram (Pinout)

**Konfigurasi Pin NodeMCU:**
| Komponen | Pin NodeMCU | GPIO |
| :--- | :--- | :--- |
| Servo Base | D1 | GPIO 5 |
| Servo Shoulder | D2 | GPIO 4 |
| Servo Elbow | D8 | GPIO 15 |
| Servo Wrist | D4 | GPIO 2 |
| Sensor Api (Tengah) | A0 | ADC 0 |
| Sensor Kiri | D6 | GPIO 12 |
| Sensor Kanan | D7 | GPIO 13 |
| Relay Pompa | D5 | GPIO 14 |

> **Catatan Power:** Daya untuk Pompa diambil langsung dari baterai melalui Step-down XL4015 (diset ke 6V), bukan dari pin NodeMCU, untuk mencegah brownout (kekurangan arus). Ground (GND) baterai dan NodeMCU disatukan (Common Ground). Dan apabila nodeMCU tidak mengambil daya dari usb laptop, maka daya dapat diambil melalui stepdown dan dihubungkan ke pin VIN pada nodeMCU.

<img width="1935" height="1059" alt="firefighting arm robot prototype version_schem" src="https://github.com/user-attachments/assets/06d67c7d-6aa0-4bb8-8893-ca94eb9af416" />


## 🚀 Cara Instalasi

### 1. Setup Database & Server
1.  Pastikan **XAMPP** terinstal dan jalankan Apache & MySQL.
2.  Buka `phpMyAdmin`, buat database baru bernama `db_robot`.
3.  Import file `database/db_robot.sql` ke dalam database tersebut.
4.  Salin folder `server/` ke dalam `htdocs` (misal: `C:\xampp\htdocs\robot\`).

### 2. Konfigurasi Arduino
1.  Buka `arduino/RobotArm_NodeMCU.ino`.
2.  Install library yang dibutuhkan: `Servo`, `ESP8266WiFi`, `ESP8266HTTPClient`.
3.  Ubah konfigurasi berikut sesuai jaringan kamu:
    ```cpp
    const char* ssid = "NAMA_WIFI_KAMU";
    const char* password = "PASSWORD_WIFI";
    const char* serverUrl = "http://IP_LAPTOP_KAMU/robot/update-status.php";
    ```
4.  Upload kode ke NodeMCU.

### 3. Jalankan Dashboard
Buka browser dan akses alamat server lokal kamu, misalnya:
`http://localhost/robot/web/dashboard.html`

## 📊 Tampilan Dashboard

Dashboard ini memungkinkan monitoring jarak jauh dan analisis performa sistem robot pemadam api secara real-time melalui antarmuka web yang modern dan responsif.

![Dasboard IOT robot pemadam api](https://github.com/user-attachments/assets/30daaa6d-a88f-4dd8-b56f-ae9b5d620e15)
![Dasboard IOT robot pemadam api 2](https://github.com/user-attachments/assets/d8b9ab1d-1c3b-47db-bdea-568fd8eeaea7)


## 🤝 Kontribusi
Projek ini dikembangkan untuk tujuan pembelajaran dan tugas IoT.

---
*Dibuat oleh **Muhammad Abdullah Husaini**.*
