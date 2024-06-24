#include <WiFi.h>
#include <FirebaseESP32.h>  // Librería para Firebase en ESP32

// Variables de configuración de Firebase
#define FIREBASE_HOST "tu-proyecto.firebaseio.com"
#define FIREBASE_AUTH "token-de-autenticacion"

// Variables de red WiFi
const char* ssid = "nombre-de-tu-red-wifi";
const char* password = "contraseña-de-tu-red-wifi";

// Pin donde está conectado el sensor MQ-2 (A0 en este ejemplo)
const int mq2Pin = A0;

// Objeto de configuración de Firebase
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Conexión a WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi!");

  // Inicialización de Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Lectura del sensor MQ-2
  int mq2Value = analogRead(mq2Pin);

  // Envío de datos a Firebase
  if (Firebase.setInt(firebaseData, "/sensor/mq2", mq2Value)) {
    Serial.print("Valor de MQ-2 enviado a Firebase: ");
    Serial.println(mq2Value);
  } else {
    Serial.println("Error al enviar el valor a Firebase");
    Serial.println(firebaseData.errorReason());
  }

  delay(10000);  // Espera 10 segundos antes de la siguiente lectura y envío
}
