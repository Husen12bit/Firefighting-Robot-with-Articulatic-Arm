#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// --- KONFIGURASI WiFi & SERVER ---
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWD_WIFI";
const char* serverUrl = "http://IP_LAPTOP/robot/update-status.php";

// --- VARIABEL GLOBAL SERVO (Agar bisa dikirim ke database) ---
int baseAngle = 90;
int shoulderAngle = 100;
int elbowAngle = 0;
int wristAngle = 0;

int ambangBatasDekat = 350;
int batasBawah = 150;

const int pinSensorApi = A0;
const int pinRelay = D5; 
const int pinSensorKiri = D6; 
const int pinSensorKanan = D7;

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoWrist;

// --- VARIABEL IOT ---
unsigned long lastDataSend = 0;
const unsigned long dataSendInterval = 2000;

void setup() {
  Serial.begin(115200);
  Serial.println("Prototipe Robot Pemadam Api Siap!");

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung! IP: " + WiFi.localIP().toString());

  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW); 

  pinMode(pinSensorKiri, INPUT);  
  pinMode(pinSensorKanan, INPUT); 

  servoBase.attach(D1);
  servoShoulder.attach(D2);
  servoElbow.attach(D8);
  servoWrist.attach(D4);

  posisiSiaga(90);
  Serial.println("Lengan robot di posisi siaga.");
}


void loop() {
  // 1. BACA SEMUA SENSOR
  int nilaiSensorAnalog = analogRead(pinSensorApi);
  int statusKiri = digitalRead(pinSensorKiri);
  int statusKanan = digitalRead(pinSensorKanan);

  // default
  String statusSekarang = "SIAGA";
  String arahSekarang = "TIDAK ADA";
  String pompaStatus = "OFF";
  int sudutBaseSaatIni = 90;
  
  // SENSOR TENGAH (A0) AKTIF
  if (nilaiSensorAnalog > batasBawah) {
    if (nilaiSensorAnalog < ambangBatasDekat) { 
        Serial.println("STATUS: Api di TENGAH & SANGAT DEKAT! Mengaktifkan pemadam...");
        posisiDekat(90);
        statusSekarang = "PADAMKAN (DEKAT)";
    } else { 
        Serial.println("STATUS: Api di TENGAH & jarak sedang. Mengaktifkan pemadam...");
        posisiSedang(90);
        statusSekarang = "PADAMKAN (SEDANG)";
    }
    digitalWrite(pinRelay, HIGH);
    pompaStatus = "ON";
    arahSekarang = "TENGAH";
    sudutBaseSaatIni = 90;
  } 
  // SENSOR KIRI (D6) AKTIF
  else if (statusKiri == HIGH) {
    Serial.println("STATUS: Api di KIRI! Menoleh ke kiri...");
    posisiSiaga(115);
    digitalWrite(pinRelay, LOW);
    statusSekarang = "MENCARI";
    arahSekarang = "KIRI";
    pompaStatus = "OFF";
    sudutBaseSaatIni = 115;
  }
  // SENSOR KANAN (D7) AKTIF
  else if (statusKanan == HIGH) {
    Serial.println("STATUS: Api di KANAN! Menoleh ke kanan...");
    posisiSiaga(65);
    digitalWrite(pinRelay, LOW);
    statusSekarang = "MENCARI";
    arahSekarang = "KANAN";
    pompaStatus = "OFF";
    sudutBaseSaatIni = 65;
  }
  // SEMUA SENSOR AMAN
  else {
    Serial.println("STATUS: Aman. Tidak ada api terdeteksi.");
    posisiSiaga(90);
    digitalWrite(pinRelay, LOW);
    statusSekarang = "SIAGA";
    arahSekarang = "TIDAK ADA";
    pompaStatus = "OFF";
    sudutBaseSaatIni = 90;
  }

  // --- BAGIAN IOT: KIRIM DATA KE DATABASE ---
  if (millis() - lastDataSend > dataSendInterval) {
    kirimDataKeServer(statusSekarang, arahSekarang, nilaiSensorAnalog, pompaStatus, sudutBaseSaatIni);
    lastDataSend = millis();
  }

  delay(500);
}


// --- FUNGSI POSISI LENGAN ROBOT ---

void posisiSiaga(int sudutBase) {
  baseAngle = sudutBase;
  shoulderAngle = 100;
  elbowAngle = 0;
  wristAngle = 0;
  
  servoBase.write(baseAngle);
  servoShoulder.write(shoulderAngle);
  servoElbow.write(elbowAngle);
  servoWrist.write(wristAngle);
}

void posisiSedang(int sudutBase) {
  baseAngle = sudutBase; 
  shoulderAngle = 180; 
  elbowAngle = 180; 
  wristAngle = 90;
  
  servoBase.write(baseAngle);
  servoShoulder.write(shoulderAngle);
  servoElbow.write(elbowAngle);
  servoWrist.write(wristAngle);
}

void posisiDekat(int sudutBase) {
  baseAngle = sudutBase; 
  shoulderAngle = 90; 
  elbowAngle = 90; 
  wristAngle = 100;
  
  servoBase.write(baseAngle);
  servoShoulder.write(shoulderAngle);
  servoElbow.write(elbowAngle);
  servoWrist.write(wristAngle);
}

// KIRIM KE DATABASE

void kirimDataKeServer(String mode, String arah, int intensitas, String pompa, int sudut) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "modeOperasi=" + mode +
                      "&arahApi=" + arah +
                      "&pompaStatus=" + pompa +
                      "&baseAngle=" + String(sudut) +
                      "&shoulderAngle=" + String(shoulderAngle) +
                      "&elbowAngle=" + String(elbowAngle) +
                      "&wristAngle=" + String(wristAngle) +
                      "&sensorKiri=" + String(digitalRead(pinSensorKiri)) + 
                      "&sensorKanan=" + String(digitalRead(pinSensorKanan)) +
                      "&sensorTengahAnalog=" + String(intensitas);
    
    
    int httpCode = http.POST(postData);
    
    if (httpCode > 0) {
      // Data berhasil terkirim (HTTP 200)
      // Serial.println("Sukses kirim data."); 
    } else {
      // Tampilkan error HANYA jika gagal
      Serial.print("Error kirim data HTTP: ");
      Serial.println(httpCode);
    }
    
    http.end();
  } else {
    Serial.println("WiFi terputus!");
  }
}