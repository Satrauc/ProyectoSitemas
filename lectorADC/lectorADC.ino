const int maxSamples = 500;
int buffer[maxSamples];


void setup() {
  Serial.begin(115200);
  while (!Serial);
}

void loop() {
  if (Serial.available() >= 5) {
    // Leer parámetros (N, dt, pin)
    int N = Serial.read() << 8 | Serial.read();
    int dt = Serial.read() << 8 | Serial.read();
    int pin = Serial.read();  // 0 = A0, 1 = A1, etc.

    int analogPin = A0 + pin;
    int totalSent = 0;
    

    while (totalSent < N) {
      int currentBlock = min(maxSamples, N - totalSent);

      for (int i = 0; i < currentBlock; i++) {
          buffer[i] = analogRead(analogPin)*5/1023;
          delay(dt);
      }
      // Enviar datos en binario (2 bytes por valor)
      for (int i = 0; i < currentBlock; i++) {
        Serial.write(buffer[i] >> 8);     // Byte alto
        Serial.write(buffer[i] & 0xFF);   // Byte bajo
      }

      totalSent += currentBlock;
    }
  }
}

