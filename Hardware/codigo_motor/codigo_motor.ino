void setup() {
 //seteo los pines de output
 //STEP
 pinMode(4, OUTPUT);
 //DIR
 pinMode(5, OUTPUT);
}

void loop() {
  //enciende el motor
  digitalWrite(5, HIGH);
  //para un motor de 0.9° se usasn 200 pasos para girar 180°, para un motor de 1.8° se usan 100
  for(int i = 0; i < 200; i++){
    //gira para un lado
    digitalWrite(4, HIGH);
    delay(10);
    //gira para el otro
    digitalWrite(4, LOW);
    delay(10);
  }
}
