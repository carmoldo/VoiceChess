void setup() {
 //seteo los pines de output
 //STEP
 pinMode(4, OUTPUT);
 //DIR
 pinMode(5, OUTPUT);
}

void loop() {
  //gira para la derecha
 digitalWrite(5, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < 201; i++){
    digitalWrite(4, HIGH);
    Serial.println( i);
    delay(20);
    digitalWrite(4, LOW);
    delay(20);
  }

  //gira para la izquierda
  digitalWrite(5, LOW);
  for(int i = 0; i < 201; i++){
    digitalWrite(4, HIGH);
    Serial.println( i);
    delay(20);
    digitalWrite(4, LOW);
    delay(20);
  }
}
