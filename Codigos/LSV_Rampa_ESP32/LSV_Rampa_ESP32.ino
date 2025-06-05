// Configuración de PWM para ESP32
const int pwmPin = 25;  // Usa cualquier pin GPIO válido (ej. 2, 4, 12-19, 21-23, 25-27, 32-33)

// Parámetros LSV triangular
const uint16_t NSAMPLES = 300;          // Escalones por rampa
const uint32_t RAMP_TIME_US = 12500000; // 12.5 s por rampa
const uint32_t STEP_US = RAMP_TIME_US / NSAMPLES;
const uint16_t MAX_DUTY = 4095;         // 12 bits (0-4095)

// Configuración LEDC
const int ledcChannel = 0;      // Canal 0-15
const int ledcResolution = 12;  // Resolución de 12 bits
const int ledcFrequency = 5000; // Frecuencia base en Hz

void setup() {
  // Configurar canal LEDC
  ledcSetup(ledcChannel, ledcFrequency, ledcResolution);
  ledcAttachPin(pwmPin, ledcChannel);
}

void loop() {
  uint32_t nextMicros = micros();

  // Rampa ascendente
  for (uint16_t i = 0; i < NSAMPLES; i++) {
    uint32_t duty = (uint32_t)i * MAX_DUTY / (NSAMPLES - 1);
    ledcWrite(ledcChannel, duty);
    
    nextMicros += STEP_US;
    while (micros() < nextMicros);  // Espera precisa
  }

  // Rampa descendente
  for (uint16_t i = NSAMPLES; i-- > 0; ) {
    uint32_t duty = (uint32_t)i * MAX_DUTY / (NSAMPLES - 1);
    ledcWrite(ledcChannel, duty);
    
    nextMicros += STEP_US;
    while (micros() < nextMicros);  // Espera precisa
  }
}