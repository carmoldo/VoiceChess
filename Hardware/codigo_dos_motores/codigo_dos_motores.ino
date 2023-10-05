#define dly 10
#define stepONE 4
#define outputONE 5
#define stepTWO 27
#define outputTWO 14
#define pasos 201

void setup() {
 //PRIMER MOTOR
 pinMode(stepONE, OUTPUT);
 pinMode(outputONE, OUTPUT);

 //SEGUNDO MOTOR
 pinMode(stepTWO, OUTPUT);
 pinMode(outputTWO, OUTPUT);
}

void loop() {
  //gira para la derecha (1)
 digitalWrite(outputONE, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepONE, HIGH);
    delay(dly);
    digitalWrite(stepONE, LOW);
    delay(dly);
  }

  //gira para la izquierda (1)
  digitalWrite(outputONE, LOW);
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepONE, HIGH);
    delay(dly);
    digitalWrite(stepONE, LOW);
    delay(dly);
  }


  //gira para la derecha (2)
 digitalWrite(outputTWO, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepTWO, HIGH);
    delay(dly);
    digitalWrite(stepTWO, LOW);
    delay(dly);
  }
  //gira para la izquierda (2)
  digitalWrite(outputTWO, LOW);
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepTWO, HIGH);
    delay(dly);
    digitalWrite(stepTWO, LOW);
    delay(dly);
  }
}
