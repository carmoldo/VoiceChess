#define stepTWO 27
#define outputTWO 14
#define pasos 201
#define dly 10

void setup() {
  pinMode(stepTWO, OUTPUT);
 pinMode(outputTWO, OUTPUT);
}

void loop() {
    //gira para la derecha 
 digitalWrite(outputTWO, HIGH);
  //da una vuelta entera usando 200
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepTWO, HIGH);
    delay(dly);
    digitalWrite(stepTWO, LOW);
    delay(dly);
  }
  //gira para la izquierda 
  digitalWrite(outputTWO, LOW);
  for(int i = 0; i < pasos; i++){
    digitalWrite(stepTWO, HIGH);
    delay(dly);
    digitalWrite(stepTWO, LOW);
    delay(dly);
  }
}
