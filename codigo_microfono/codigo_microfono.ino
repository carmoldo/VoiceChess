//este codigo devuelve los valores numericos que recibe el microfono
void setup() {
 pinMode(35,INPUT);
 Serial.begin(115200);
}

void loop() {
  int voice = analogRead(35);
  Serial.println(voice);
}
