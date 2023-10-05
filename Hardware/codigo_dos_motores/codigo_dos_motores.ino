#define dly 10

void setup() {
 //seteo los pines de output
 //STEP 1
 pinMode(4, OUTPUT);
 //DIR 1
 pinMode(5, OUTPUT);

 //STEP 2
 pinMode(27, OUTPUT);
 //DIR 2
 pinMode(14, OUTPUT);
}

void loop() {
  //gira para la derecha (1)
 digitalWrite(5, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < 201; i++){
    digitalWrite(4, HIGH);
    delay(dly);
    digitalWrite(4, LOW);
    delay(dly);
  }

  //gira para la izquierda (1)
  digitalWrite(5, LOW);
  for(int i = 0; i < 201; i++){
    digitalWrite(4, HIGH);
    delay(dly);
    digitalWrite(4, LOW);
    delay(dly);
  }


  //gira para la derecha (2)
 digitalWrite(14, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < 201; i++){
    digitalWrite(27, HIGH);
    delay(dly);
    digitalWrite(27, LOW);
    delay(dly);
  }

  //gira para la izquierda (2)
  digitalWrite(14, LOW);
  for(int i = 0; i < 201; i++){
    digitalWrite(27, HIGH);
    delay(dly);
    digitalWrite(27, LOW);
    delay(dly);
  }
}
