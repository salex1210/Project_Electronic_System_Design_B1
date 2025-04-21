// Pin PWM para Timer1
const int pwmPin = 9;  // OCR1A en Arduino Uno

// Parámetros de la LSV
const uint16_t NSAMPLES      = 300;          // 300 escalones
const uint32_t RAMP_TIME_US  = 12500000UL;   // 12,500,000 μs = 12,5 s
const uint32_t STEP_US       = RAMP_TIME_US / NSAMPLES; // ≈ 41 666 μs
const uint16_t MAX_DUTY      = 1023;         // 10 bits (0–1023)

void setup() {
  // Configurar Timer1: Fast PWM 10 bits en OCR1A (pin 9)
  TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(CS10);  // Sin prescaler → fPWM ≈ 16MHz/1024 ≈ 15,6 kHz
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // Iniciar tiempo base
  uint32_t nextMicros = micros();

  // Barrido de subida: 0 → FULL SCALE en 300 pasos
  for (uint16_t i = 0; i < NSAMPLES; i++) {
    // Calcular ciclo de trabajo [0..1023]
    OCR1A = (uint32_t)i * MAX_DUTY / (NSAMPLES - 1);

    // Esperar hasta el siguiente instante programado
    nextMicros += STEP_US;
    while ((int32_t)(micros() - nextMicros) < 0) {
      // busy‑wait para precisión al microsegundo
    }
  }

  // Mantener el último valor de la rampa
  //while (1) {
    // nada más
  //}
}

