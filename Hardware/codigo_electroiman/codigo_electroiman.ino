// Define el pin del Arduino que se conecta al electroimán
#define ELECTROIMAN 13

void setup() {
  // Inicializa el pin del electroimán como salida
  pinMode(ELECTROIMAN, OUTPUT);
}

void loop() {
  // Enciende el electroimán
  digitalWrite(ELECTROIMAN, HIGH);
  // Espera un segundo
  delay(1000);
  // Apaga el electroimán
  digitalWrite(ELECTROIMAN, LOW);
  // Espera un segundo
  delay(1000);
}
