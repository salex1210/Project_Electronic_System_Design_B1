// Configuración de PWM para ESP32
const int pwmPin = 25;        // Pin PWM (GPIO25)
const int ledcChannel = 0;     // Canal LEDC (0-15)
const int ledcResolution = 12; // Resolución de 12 bits (0-4095)

// Parámetros de voltamperometría DPV
const int V_start = 0;         // Valor inicial PWM (0V)
const int V_end = 4095;        // Valor final PWM (3.3V) - 12 bits
const int num_steps = 30;      // Número de escalones
const int pulse_amp = 200;     // Amplitud del pulso (ajustada a 12 bits)
const int t_pulse = 200;       // Duración del pulso (ms)
const int t_step = 200;        // Duración de paso (ms)

void setup() {
  // Configurar PWM
  ledcSetup(ledcChannel, 5000, ledcResolution); // Frecuencia 5 kHz
  ledcAttachPin(pwmPin, ledcChannel);
  ledcWrite(ledcChannel, V_start); // Iniciar en 0V
}

void loop() {
  // Rampa de subida escalonada con pulsos diferenciales
  for (int i = 0; i <= num_steps; i++) {
    int pwm_value = map(i, 0, num_steps, V_start, V_end);
    ledcWrite(ledcChannel, pwm_value);
    delay(t_step);

    // Aplicar pulso diferencial
    int pulse_val = constrain(pwm_value + pulse_amp, V_start, V_end);
    ledcWrite(ledcChannel, pulse_val);
    delay(t_pulse);

    // Volver al valor base
    ledcWrite(ledcChannel, pwm_value);
  }

  // Rampa de bajada escalonada con pulsos diferenciales
  for (int i = num_steps; i >= 0; i--) {
    int pwm_value = map(i, 0, num_steps, V_start, V_end);
    ledcWrite(ledcChannel, pwm_value);
    delay(t_step);

    // Aplicar pulso diferencial
    int pulse_val = constrain(pwm_value + pulse_amp, V_start, V_end);
    ledcWrite(ledcChannel, pulse_val);
    delay(t_pulse);

    // Volver al valor base
    ledcWrite(ledcChannel, pwm_value);
  }
}