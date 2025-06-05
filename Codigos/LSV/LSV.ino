// Pin PWM para Timer1
const int pwmPin = 9;  // OCR1A en Arduino Uno

// Parámetros de la LSV triangular
const uint16_t NSAMPLES     = 300;                 // Escalones por rampa
const uint32_t RAMP_TIME_US = 12500000UL;          // 12.5 s por subida o bajada
const uint32_t STEP_US      = RAMP_TIME_US / NSAMPLES;
const uint16_t MAX_DUTY     = 4095;                // PWM de 12 bits

void setup() {
  pinMode(pwmPin, OUTPUT);

  // Configurar Timer1 en Fast PWM, modo 14: WGM13:0 = 1110 (TOP = ICR1)
  TCCR1A = _BV(COM1A1) | _BV(WGM11);               // COM1A1 para salida no inversa
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);    // prescaler = 1
  ICR1 = MAX_DUTY;                                 // TOP = 4095 → 12 bits
}

void loop() {
  uint32_t nextMicros = micros();

  // --- Rampa ascendente ---
  for (uint16_t i = 0; i < NSAMPLES; i++) {
    OCR1A = (uint32_t)i * MAX_DUTY / (NSAMPLES - 1);

    nextMicros += STEP_US;
    while ((int32_t)(micros() - nextMicros) < 0) {
      // espera activa
    }
  }

  // --- Rampa descendente ---
  for (int16_t i = NSAMPLES - 1; i >= 0; i--) {
    OCR1A = (uint32_t)i * MAX_DUTY / (NSAMPLES - 1);

    nextMicros += STEP_US;
    while ((int32_t)(micros() - nextMicros) < 0) {
      // espera activa
    }
  }

  // Repetir indefinidamente
}



