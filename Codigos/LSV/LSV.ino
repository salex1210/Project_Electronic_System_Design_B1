// Pin PWM para Timer1
const int pwmPin = 9;  // OCR1A en Arduino Uno

// Parámetros de la LSV triangular
const uint16_t NSAMPLES      = 300;            // Número de escalones
const uint32_t RAMP_TIME_US  = 12500000UL;     // Tiempo de subida/bajada: 12,5 s = 12.500.000 µs
const uint32_t STEP_US       = RAMP_TIME_US / NSAMPLES;  // ≈ 41.6 ms por escalón
const uint16_t MAX_DUTY      = 1023;           // PWM de 10 bits

void setup() {
  // Configurar Timer1 en Fast PWM de 10 bits
  TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(CS10);  // Sin preescaler → fPWM ≈ 15.6 kHz
  pinMode(pwmPin, OUTPUT);
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

