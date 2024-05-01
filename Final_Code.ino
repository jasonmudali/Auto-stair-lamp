#define TRIGGER_PIN_TOP 8   // Pin trigger sensor ultrasonik atas
#define ECHO_PIN_TOP 9      // Pin echo sensor ultrasonik atas
#define TRIGGER_PIN_BOTTOM 11  // Pin trigger sensor ultrasonik bawah
#define ECHO_PIN_BOTTOM 12     // Pin echo sensor ultrasonik bawah
#define NUM_STEPS 14         // Jumlah anak tangga
#define LIGHT_ON_DELAY 15000 // Delay dalam milidetik sebelum mematikan lampu (30 detik)
#define LIGHT_DELAY 500      // Delay antara setiap lampu dalam milidetik (0.5 detik)

#define ledPin1 A0
#define ledPin2 A1
#define ledPin3 A2
#define ledPin4 3
#define ledPin5 4
#define ledPin6 5
#define ledPin7 6

int ledPins[] = {ledPin1, ledPin2, ledPin3, ledPin4, ledPin5, ledPin6, ledPin7};
unsigned long lastMotionTime = 0; // Waktu deteksi gerakan terakhir
// currentStep = 0;              // Langkah anak tangga saat ini
bool lightsOn = false;           // Status lampu

void setup() {
  pinMode(TRIGGER_PIN_TOP, OUTPUT);
  pinMode(ECHO_PIN_TOP, INPUT);
  pinMode(TRIGGER_PIN_BOTTOM, OUTPUT);
  pinMode(ECHO_PIN_BOTTOM, INPUT);
  for (int i = 0; i <= 6; i++) {
    pinMode(ledPins[i], OUTPUT); // Mengatur pin 6-12 sebagai output untuk lampu
  }
  Serial.begin(9600);
}

void loop() {
  bool motionDetectedBottom = motionDetected(TRIGGER_PIN_BOTTOM, ECHO_PIN_BOTTOM);
  bool motionDetectedTop = motionDetected(TRIGGER_PIN_TOP, ECHO_PIN_TOP);

  if (motionDetectedBottom == true) {
    // Ada gerakan terdeteksi
    lastMotionTime = millis();
    Serial.print("Detik sekarang: ");
    Serial.println(millis()/1000);

    turnOnLightsUpward();

  } else if (motionDetectedTop == true) {
    // Ada gerakan terdeteksi
    lastMotionTime = millis();
    Serial.print("Detik sekarang: ");
    Serial.println(millis()/1000);

    turnOnLightsDownward();
    // if (lightsOn = false) {
    //   turnOnLights();
    // }
  } else {
    // Tidak ada gerakan terdeteksi
    if (lightsOn && millis() - lastMotionTime >= LIGHT_ON_DELAY) {
      turnOffLights();
    }
  }
  
  // Membaca dan menampilkan jarak dari kedua sensor ultrasonik pada Serial Monitor
  long distanceBottom = getDistance(TRIGGER_PIN_BOTTOM, ECHO_PIN_BOTTOM);
  long distanceTop = getDistance(TRIGGER_PIN_TOP, ECHO_PIN_TOP);
  Serial.print("Distance Bottom: ");
  Serial.print(distanceBottom);
  Serial.print(" cm, Distance Top: ");
  Serial.print(distanceTop);
  Serial.println(" cm");
  delay(500); // Tunggu 1 detik sebelum membaca lagi
}

bool motionDetected(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1; // Menghitung jarak dalam cm
  return (distance < 50); // Ubah angka ini sesuai dengan jarak yang ingin Anda deteksi
}

long getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1; // Menghitung jarak dalam cm
  return distance;
}

void turnOnLightsUpward() {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(1000); // 
  }
  lightsOn = true;
  // currentStep = 6; // Setel langkah saat ini ke 6 (lampu pertama)
}

void turnOnLightsDownward() {
  for (int i = 6; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(1000); // 
  }
  lightsOn = true;
  // currentStep = 6; // Setel langkah saat ini ke 6 (lampu pertama)
}

void turnOffLights() {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(ledPins[i], LOW); // Matikan semua lampu
  }
  lightsOn = false;
}